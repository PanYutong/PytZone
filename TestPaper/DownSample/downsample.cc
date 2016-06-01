#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <stack>

using namespace cv;
using namespace std;
int main(int argc, char * argv[]) {
  string file_name;

  string f_ds =
      "/home/panyutong/PytZone/TestPaper/DownSample/imagelist.txt";
  ifstream ifile(f_ds.c_str(), ios::in);

  while (getline(ifile, file_name)) {
    Mat source_image, ds_image;

    source_image = imread(file_name.c_str(), 1);
    if (!source_image.data) {
      printf("No image data.\n");
      return -1;
    }
    resize(source_image, ds_image, Size(), 0.5, 0.5, INTER_AREA);

    string write_file_name = "/home/panyutong/PytZone/TestPaper/Data_Quater/";
    int file_length = file_name.size();
    stack <char> name_bucket;
    for (int key = file_length - 1; file_name[key] != '/'; --key)
      name_bucket.push(file_name[key]);
    while(!name_bucket.empty()) {
      write_file_name += name_bucket.top();
      name_bucket.pop();
    }
    imwrite(write_file_name, ds_image);
  }

  return 0;
}
