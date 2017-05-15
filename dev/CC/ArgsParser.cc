#include <bits/stdc++.h>
using namespace std;

int main(int argc, char * argv[]) {
  char* test[] = {"./a.out", "-i", "/home/yutongpa/Work_CVSDK/DLSDK/caffe/cat_224x224_googlenet.bmp", "-m", "/opt/intel/deep_learning_sdk_2017.1.0.2481/deployment_tools/model_optimizer/bin/GoogleNet/GoogleNet.xml", "-p", "MKLDNNPlugin", "-l", "/home/yutongpa/Work_CVSDK/DLSDK/caffe/data/ilsvrc12/synset_words.txt"};
  for (int i = 0; i < argc; ++i) {
    if (strcmp(argv[i],test[i]) == 0) cout << '1' << endl;
  }
  return 0;
}
