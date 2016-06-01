#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;
int main(int argc, char * argv[]) {
  Mat imageMat1, imageHdl1;
  Mat imageMat2, imageHdl2;
  imageMat1 = imread(argv[1], 1);
  if (!imageMat1.data) {
    printf("No image data.\n");
    return -1;
  }
  resize(imageMat1, imageHdl1, Size(128, 32));

  HOGDescriptor *hog =
      new HOGDescriptor(cvSize(32, 16), cvSize(16, 16), 
                        cvSize(16, 16), cvSize(8, 8), 9);
  vector<float> descriptors1;
  hog->compute(imageHdl1, descriptors1, Size(2, 2), Size(0, 0));
  //cout << "descriptors.size = " << descriptors.size() << endl;
  
  /*
  for (int i = 0; i < descriptors1.size(); ++i) {
   cout << descriptors1[i] << ' ';
  }
  */

  imageMat2 = imread(argv[2], 1);
  if (!imageMat2.data) {
    printf("No image data.\n");
    return -1;
  }
  resize(imageMat2, imageHdl2, Size(128, 32));

  vector<float> descriptors2;
  hog->compute(imageHdl2, descriptors2, Size(2, 2), Size(0, 0));
  double cross = 0;
  for (int i = 0; i < descriptors1.size(); ++i) {
    cross += descriptors1[i] * descriptors2[i];
  }

  vector<float> tpl_descriptors;
  string cfg_file_name =
      "/home/panyutong/PytZone/TestPaper/Config/quarter_square.cfg";
  ifstream ifile0(cfg_file_name.c_str(), ios::in);
  float temp;
  while (ifile0 >> temp) tpl_descriptors.push_back(temp);

  double cross_tpl = 0;
  for (int i = 0; i < descriptors1.size(); ++i) {
    cross_tpl += descriptors1[i] * tpl_descriptors[i];
  }

  cout << cross_tpl << endl;

  return 0;
}
