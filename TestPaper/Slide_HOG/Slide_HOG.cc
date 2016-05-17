#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

vector<float> tpl_descriptors;

double calHog(Mat img);

int main(int argc, char * argv[]) {
  time_t start, end;
  start = time(NULL);
  Mat test_paper;
  test_paper = imread(argv[1], 1);
  if (!test_paper.data) {
    printf("error test paper data.\n");
    return -1;
  }

  string cfg_file_name = "/home/panyutong/PytZone/TestPaper/Config/stathog.cfg";
  ifstream ifile(cfg_file_name.c_str(), ios::in);
  float temp;
  while (ifile >> temp) tpl_descriptors.push_back(temp);

  int rect_x = 0, rect_y = 0;
  int rect_width = 166, rect_height = 28;

  Mat img_s(test_paper);

  vector<Point> candidate;

  for (rect_y = test_paper.rows / 5; rect_y < (4 * test_paper.rows) / 5;
       rect_y += 5) {
    for (rect_x = test_paper.cols / 40; rect_x < (7 * test_paper.cols) / 8;
         rect_x += 32) {
      Mat ROI(test_paper, Rect(rect_x, rect_y, rect_width, rect_height));
      double score = 0;
      score = calHog(ROI);
      if (score > 3000.0) {
        Point topLeft, btmRight;
        topLeft.x = rect_x, topLeft.y = rect_y;
        btmRight.x = rect_x + rect_width, btmRight.y = rect_y + rect_height;
        rectangle(img_s, topLeft, btmRight, Scalar(255, 0, 0), 2, 8, 0);
        break;
      }
    }
  }
  end = time(NULL);
  cout << "Use: " << end - start << 's' << endl;
  string write_file_name = "/home/panyutong/3test_4_real.png";
  imwrite(write_file_name, img_s);

  return 0;
}

double calHog(Mat img) {
  Mat imgHdl;

  resize(img, imgHdl, Size(256, 64));

  HOGDescriptor *hog =
      new HOGDescriptor(cvSize(64, 32), cvSize(32, 32), 
                        cvSize(32, 32), cvSize(32, 32), 9);

  vector<float> img_descriptors;

  hog->compute(imgHdl, img_descriptors, Size(2, 2), Size(0, 0));

  double cross = 0;
  for (int i = 0; i < img_descriptors.size(); ++i) {
    cross += img_descriptors[i] * tpl_descriptors[i];
  }
  return cross;
}
