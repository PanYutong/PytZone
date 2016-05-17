#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char * argv[]) {
  Mat paper, templ;
  paper = imread(argv[1], 1);
  templ = imread(argv[2], 1);

  Mat img_s(paper);

  if (!paper.data) {
    printf("error paper data.\n");
    return -1;
  }
  if (!templ.data) {
    printf("error template data.\n");
    return -1;
  }

  Point topLeft, btmRight;
  topLeft.x = 1000;
  topLeft.y = 10;
  btmRight.x = 1500;
  btmRight.y = 500;
  rectangle(img_s, topLeft, btmRight, Scalar::all(0), 2, 8, 0);
  cout << img_s.width << endl;
  imwrite("/home/panyutong/out.png", img_s);

  return 0;
}
