#include <bits/stdc++.h>
using namespace std;

int main(int argc, char * argv[]) {
  // char* test[] = {"./classification_sample", "-i", "/home/yutongpa/Work_CVSDK/DLSDK/caffe/cat_224x224_googlenet.bmp", "-m", "/opt/intel/deep_learning_sdk_2017.1.0.2481/deployment_tools/model_optimizer/bin/GoogleNet/GoogleNet.xml", "-p", "MKLDNNPlugin", "-l", "/home/yutongpa/Work_CVSDK/DLSDK/caffe/data/ilsvrc12/synset_words.txt"};
  int vars = 9;
  char* test[vars];
  int i = 0;
  while (test[i] != NULL) {
    cout << test[i] << endl;
    ++i;
  }
  return 0;
}
