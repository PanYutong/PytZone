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
  string file_name;
  HOGDescriptor *hog =
      new HOGDescriptor(cvSize(32, 16), cvSize(16, 16),
                        cvSize(16, 16), cvSize(8, 8), 9);

  vector<float> descriptors;

  int num = 0;

  string f_tpl =
      "/home/panyutong/PytZone/TestPaper/StatHOG/quarter_list.txt";
  ifstream ifile(f_tpl.c_str(), ios::in);

  while (getline(ifile, file_name)) {
    Mat imageMat1, imageHdl1;
    ++num;
    imageMat1 = imread(file_name.c_str(), 1);
    if (!imageMat1.data) {
      printf("No image data.\n");
      return -1;
    }
    resize(imageMat1, imageHdl1, Size(128, 32));

    vector<float> descriptors1;
    hog->compute(imageHdl1, descriptors1, Size(2, 2), Size(0, 0));
    if (num == 1) descriptors.resize(descriptors1.size());

    for (int i = 0; i < descriptors1.size(); ++i)
      descriptors[i] += descriptors1[i];
  }

  for (int i = 0; i < descriptors.size(); ++i) {
    descriptors[i] /= num;
  }

  ofstream ofile("/home/panyutong/stathog.cfg", ios::out);
  for (int i = 0; i < descriptors.size(); ++i) {
    ofile << descriptors[i] << ' ';
  }
  cout << descriptors.size() << endl;

  return 0;
}
