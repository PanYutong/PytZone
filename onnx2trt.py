import tensorrt as trt
import logging
import argparse

parser = argparse.ArgumentParser(description="onnx to tensorrt")               
parser.add_argument("--input", required=True, help="source input file")        
parser.add_argument("--output", required=True, help="ouput file")              
parser.add_argument("--precision", required=True, help="fp32 or fp16")              
parser.add_argument("--shape", required=False, help="example, 1x3x64x64")
args = parser.parse_args()                                                     
                                     
logging.basicConfig(level=logging.INFO)
logging.getLogger("EngineBuilder").setLevel(logging.INFO)    
log = logging.getLogger("EngineBuilder")    
             
TRT_LOGGER = trt.Logger(trt.Logger.INFO) 
trt_version = [int(n) for n in trt.__version__.split('.')]    
                          
def build_engine(onnx_path, engine_path):    
    builder = trt.Builder(TRT_LOGGER)    
    network = builder.create_network(    
        1 << (int)(trt.NetworkDefinitionCreationFlag.EXPLICIT_BATCH)    
    )                     
                     
    config = builder.create_builder_config()    
    config.set_tactic_sources(1 << int(trt.TacticSource.CUBLAS))    
    config.max_workspace_size = 6 * 1 << 30
    config.set_flag(trt.BuilderFlag.FP16)    
    config.set_flag(trt.BuilderFlag.STRICT_TYPES)
    config.set_flag(trt.BuilderFlag.SPARSE_WEIGHTS)
    # config.flags = (1 << int(trt.BuilderFlag.FP16) | 1 << int(trt.BuilderFlag.STRICT_TYPES))
    print('config.flags: ', config.flags)
    
    profile = builder.create_optimization_profile()                            

    profile.set_shape('images', min=(1, 3, 640, 640), opt=(128, 3, 640, 640), max=(128, 3, 640, 640))
    config.add_optimization_profile(profile)

    parser = trt.OnnxParser(network, TRT_LOGGER)
    # parse ONNX
    with open(onnx_path, 'rb') as model:
        if not parser.parse(model.read()):
            print('ERROR: Failed to parse the ONNX file.')
            for error in range(parser.num_errors):
                print(parser.get_error(error))
            return None

    engine = builder.build_engine(network, config)
    print(engine)
    engine_path = "/data2/guozelin/imagead/service/imagead/sdk/model/detect_fp16_b128_b1.trt"
    with open(engine_path, "wb") as f:
        log.info("Serializing engine to file: {:}".format(engine_path))
        f.write(engine.serialize())


if __name__ == '__main__':
    build_engine(args.input, args.output)
