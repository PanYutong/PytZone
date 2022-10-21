# -*- coding:utf-8 -*-
#import algo

import os
import time

import cv2
import yaml
import torch
import torchvision
import logging
from model import get_detect_model
from val_transform import ValTransform
from collections import defaultdict
import base64
import numpy as np
import tensorrt as trt

trt_logger = trt.Logger(trt.Logger.WARNING)

try:
    from algo import ret_on_error
    from algo import log, metric, proto
except ImportError:
    from algo_test import ret_on_error
    from algo_test import log, metric, proto


def postprocess(prediction, num_classes, nms_thre=0.45, class_agnostic=False):
    """检测后处理."""
    box_corner = prediction.new(prediction.shape)
    box_corner[:, :, 0] = prediction[:, :, 0] - prediction[:, :, 2] / 2
        
    box_corner[:, :, 1] = prediction[:, :, 1] - prediction[:, :, 3] / 2
    box_corner[:, :, 2] = prediction[:, :, 0] + prediction[:, :, 2] / 2
    box_corner[:, :, 3] = prediction[:, :, 1] + prediction[:, :, 3] / 2
    prediction[:, :, :4] = box_corner[:, :, :4]

    output = [None for _ in range(len(prediction))]
    for i, image_pred in enumerate(prediction):
        # If none are remaining => process next image
        if not image_pred.size(0):
            continue
        # Get score and class with highest confidence
        class_conf, class_pred = torch.max(image_pred[:, 5: 5 + num_classes], 1, keepdim=True)

        conf_mask = (image_pred[:, 4] * class_conf.squeeze() >= 0.4).squeeze()  # hardcode 0.5不影响review block阈值
        # Detections ordered as (x1, y1, x2, y2, obj_conf, class_conf, class_pred)
        detections = torch.cat((image_pred[:, :5], class_conf, class_pred.float()), 1)
        detections = detections[conf_mask]
        if not detections.size(0):
            continue

        if class_agnostic:
            nms_out_index = torchvision.ops.nms(detections[:, :4], detections[:, 4] * detections[:, 5], nms_thre)
        else:
            nms_out_index = torchvision.ops.batched_nms(detections[:, :4], detections[:, 4] * detections[:, 5],
                                                        detections[:, 6],
                                                        nms_thre,
                                                        )

        detections = detections[nms_out_index]
        if output[i] is None:
            output[i] = detections
        else:
            output[i] = torch.cat((output[i], detections))

    return output


class AlgoPreProcess(object):
    def __init__(self):
        #raise Exception("test")
        self.preproc = ValTransform(legacy=False)
        pass
    def handle(self, context, input_dict, output_dict):
        '''
        scene 1: 直接透传输入数据至下一阶段 ->
        calling "proto.copy_proto(input_dict, output_dict)"

        scene 2: 遇到无法继续的错误 ->
        ret_on_error()
        calling "ret_on_error(401, 1, 'decode_error')"

        scene 3: 正常业务逻辑处理 =>
        test_dict = {'iTest':1}
cust
        output_dict['Test'] = test_dict

        '''
        #log.info('AlgoPreProcess running...')
        #metric.req_moni_add("preprocess_num", 1)

        chunk_preprocessed_img = []
        img = str.encode(input_dict['imgData'])
        nparr = np.fromstring(base64.b64decode(img), np.uint8)
        img_data = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
        # img_data = cv2.imread(str(img))
        height, width = img_data.shape[:2]
        test_size = [640, 640]  # hard code

        img_data = self.preproc(img_data, test_size)
        chunk_preprocessed_img.append(torch.tensor(img_data))

        chunk_tensor = torch.stack(chunk_preprocessed_img)
        chunk_tensor = chunk_tensor.float()
        chunk_tensor = chunk_tensor.cuda()
        output_dict['data'] = chunk_tensor
        # proto.copy_proto(input_dict, output_dict)

class AlgoInference(object):
    def __init__(self):
        pass
    def initialize(self, context):
        '''
        初始化接口
        '''
        with open(os.path.join(os.getcwd(), "detect_model_conf.yaml"), 'r') as fin:
            self.params = yaml.load(fin.read(), yaml.Loader)['detect']


        #self.model_path = os.path.join(os.getcwd(), "../model/detect.pth")
        self.conf_dict = self.params['confidence']
        #self.model = get_detect_model(self.params['depth'], self.params['width'], len(self.conf_dict), self.params['activation'])
        
        os.environ["CUDA_VISIBLE_DEVICES"] = "3"
        #self.model.cuda()
        #self.model.eval()

        #ckpt = torch.load(self.model_path, map_location="cpu")
        #self.model.load_state_dict(ckpt["model"])
        #logging.info("Start detecting...")
        #logging.info("load checkpoint done.")

        #self.model_path = os.path.join(os.getcwd(), "../model/ad_det_fp16.pth")
        self.leaves_label = list(self.conf_dict.keys())
        self.num_classes = len(self.conf_dict.keys())
        self.leaves_label_to_id = {item: idx for idx, item in enumerate(self.leaves_label)}
        trt_rt = trt.Runtime(trt_logger)
        with open("../model/detect_fp16_b64_b1.trt", "rb") as f, trt.Runtime(trt_logger) as trt_rt:
            self.trt_engine = trt_rt.deserialize_cuda_engine(f.read())
        self.in_bind_index = self.trt_engine.get_binding_index("images") 
        self.out_bind_index = self.trt_engine.get_binding_index("output") 
        self.trt_ctx = self.trt_engine.create_execution_context()
        self.in_dtype = self.torch_dtype_from_trt(self.trt_engine.get_binding_dtype(self.in_bind_index))
        self.out_dtype = self.torch_dtype_from_trt(self.trt_engine.get_binding_dtype(self.out_bind_index))
        print(self.in_dtype)
        print(self.out_dtype)
        self.stream = torch.cuda.current_stream()

    def torch_dtype_from_trt(self, dtype):
        if dtype == trt.int8:
            return torch.int8
        elif dtype == trt.float16:
            return trt.float16
        elif dtype == trt.float32:
            return torch.float32
        else:
            raise TypeError("%s not support type" % dtype)

    def trt_inference(self, input_dict_list, output_dict_list, batch_size = 1):
        chunk_preprocessed_img = []
        for i in range(0, len(input_dict_list)):
            chunk_preprocessed_img.append(input_dict_list[i]['data'])
        chunk_tensor = torch.cat(chunk_preprocessed_img, 0)
        #chunk_tensor = input_dict_list[0]['data']
        self.trt_ctx.set_binding_shape(self.in_bind_index, chunk_tensor.shape)
        o_shape = self.trt_ctx.get_binding_shape(self.out_bind_index);
        output = torch.empty(tuple(o_shape), dtype=self.out_dtype, device=torch.device('cuda'))
        mem_bindings = [chunk_tensor.data_ptr(), output.data_ptr()]
        inf_time_start = time.time()
        self.trt_ctx.execute_async_v2(bindings=mem_bindings, stream_handle=self.stream.cuda_stream)
        self.stream.synchronize()
        inf_time_end = time.time()
        print("[YUTONG DEBUG] Inference time cost per 64 batch: ", (inf_time_end - inf_time_start) * 1000)
        output_dict_list[0]['prediction'] = torch.unsqueeze(output[0,:,:], 0)

    def predict_batch_size(self, context, input_dict):
        '''
        预测批量大小接口,默认返回1
        '''
        return 1
    def handle(self, context, input_dict_list, output_dict_list):
        '''
        批量语义的推理接口
        '''
        #log.info('input dict:{}'.format(input_dict_list[0]))
        #log.info('inference.....')
        self.trt_inference(input_dict_list, output_dict_list)
        #chunk_tensor = input_dict_list[0]['data']
        #with torch.no_grad():
        #    t0 = time.time()
        #    outputs = self.model(chunk_tensor)
        #    process_dur = time.time() - t0
        #output_dict_list[0]['prediction'] = outputs
        output_dict_list[0]['num_classes'] = self.num_classes
        output_dict_list[0]['nmsthre'] = self.params['nmsthre']
        output_dict_list[0]['leaves_label'] = self.leaves_label
        output_dict_list[0]['conf_dict'] = self.conf_dict

class AlgoPostProcess(object):
    def __init__(self):
        pass
    def handle(self, context, input_dict, output_dict):
        #log.info('AlgoPostProcess running...')
        #metric.req_moni_add("postprocess_num", 1)
        """检测后处理."""
        outputs = input_dict['prediction']
        num_classes = input_dict['num_classes']
        nmsthre = input_dict['nmsthre']
        leaves_label = input_dict['leaves_label']
        conf_dict = input_dict['conf_dict']
        return
        outputs = postprocess(outputs, num_classes, nmsthre, class_agnostic=True)
        batch_size = len(outputs)
        #assert(batch_size == 1)
        output = outputs[0]
        if output is None:
            output_dict["strLabels"] = ""
            output_dict["strProbs"] = ""
        else:
            cls_list = output[:, 6]
            scores = output[:, 4] * output[:, 5]

            # 记�~U�~O类�~D�~K�~[��| ~G�~Z~D�~\~@大置信度
            cls_to_max_score = defaultdict(float)
            for hyp_kind, hyp_score in zip(cls_list, scores):
                kind = leaves_label[int(hyp_kind)]
                cls_to_max_score[kind] = max(cls_to_max_score[kind], float(hyp_score))

            hyp_leaves_labels = []
            probs = []
            for hyp_leaf_label, hyp_max_score in cls_to_max_score.items():
                # �~R~L�~L~G�~Zblock�~X~H�~@��~T�~C
                if hyp_max_score < conf_dict[hyp_leaf_label]:
                    continue

                hyp_leaves_labels.append(hyp_leaf_label)
                probs.append(str(hyp_max_score))

            output_dict["strLabels"] = "|".join(hyp_leaves_labels)
            output_dict["strProbs"] = "|".join(probs)

if __name__ == '__main__':
    preprocess_handler = AlgoPreProcess()
    inference_handler = AlgoInference()
    postprocess_handler = AlgoPostProcess()

    context = {}
    inference_handler.initialize(context)

    # input_dict = {'strContent': 'abc'}
    img_path = '/data2/guozelin/test_data/image/speechoceanimg00085525.jpg' #'/data/guozelin/test_data/image/online01600602.jpg'
    dir_name = "/data2/guozelin/test_data/image/"
    #import time
    input_dict_list = [] 
    st = time.time()
    for f in os.listdir(dir_name):
        img_path = dir_name + f
        import base64
        import numpy as np
        encoded = base64.b64encode(open(img_path, "rb").read()).decode("utf-8")
        input_dict = {'imgData': encoded}
        output_dict = {}
        preprocess_handler.handle(context, input_dict, output_dict)
        input_dict_list.append(output_dict)
        if len(input_dict_list) == 64:
            output_dict_list = [{}]
            # AlgoInference_time_start = time.time()
            inference_handler.handle(context, input_dict_list, output_dict_list)
            # AlgoInference_time_end = time.time()
            # print("[YUTONG DEBUG] Inference time cost per 64 batch: ", (AlgoInference_time_end - AlgoInference_time_start) * 1000)
            #print('Inference output: ', output_dict_list)
            input_dict = output_dict_list[0]
            output_dict = {}
            postprocess_handler.handle(context, input_dict, output_dict)
            #print('PostProcess[Res] output: ', output_dict)
            input_dict_list.clear()
    et = time.time()
    print((et - st) * 1000)
            
    #print('PreProcess output: ', output_dict)

    #input_dict_list = [output_dict]
    #output_dict_list = [{}]
    #inference_handler.handle(context, input_dict_list, output_dict_list)
    #print('Inference output: ', output_dict_list)

    #input_dict = output_dict_list[0]
    #output_dict = {}
    #postprocess_handler.handle(context, input_dict, output_dict)
    #print('PostProcess[Res] output: ', output_dict)

