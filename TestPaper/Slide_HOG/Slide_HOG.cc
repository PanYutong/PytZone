#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
#include <stack>
#include <list>

using namespace cv;
using namespace std;

vector<float> tpl_descriptors;

double calHog(Mat img);

double conf_value;

int find_candidate(Mat source, vector<Point> &can);

void find_connection(vector <pair <Point, Point> >::iterator RectOI,
                     stack <pair <Point, Point> > &c_pool);
void merge_connection(Mat &display, stack <pair <Point, Point> > c_pool);

int main(int argc, char * argv[]) {
  time_t start, end;
  start = time(NULL);

  // read paper data
  Mat test_paper;
  test_paper = imread(argv[1], 1);
  if (!test_paper.data) {
    printf("error test paper data.\n");
    return -1;
  }

  resize(test_paper, test_paper, Size(), 0.5, 0.5, INTER_AREA);

  int section = atoi(argv[2]), div_width;
  div_width = test_paper.cols / section;

  // read template descriptors data from config file
  string cfg_file_name =
      "/home/panyutong/PytZone/TestPaper/Config/quarter_normal.cfg";
  conf_value = 700.0;
  ifstream ifile0(cfg_file_name.c_str(), ios::in);
  float temp;
  while (ifile0 >> temp) tpl_descriptors.push_back(temp);

  // copy source paper to image display
  Mat img_s(test_paper);

  vector<Point> candidate;

  // find normal candidates
  find_candidate(test_paper, candidate);

  // find square candidates
  tpl_descriptors.clear();
  cfg_file_name =
      "/home/panyutong/PytZone/TestPaper/Config/quarter_square.cfg";
  conf_value = 780.0;
  ifstream ifile3(cfg_file_name.c_str(), ios::in);
  while (ifile3 >> temp) tpl_descriptors.push_back(temp);
  if (find_candidate(test_paper, candidate) < 1) {
    cout << "Can not figure out!" << endl;
  }

  // draw rectangles
  vector <pair <Point, Point> > region;
  for (int i = 0; i < candidate.size(); ++i) {
    Point top = candidate[i];
    while (candidate[i + 1].y - candidate[i].y < 50 &&
           candidate[i + 1].y - candidate[i].y > 0) ++i;
    Point btm = candidate[i];
    if (section == 2) {
      if (top.x < div_width + div_width / 10) {
        top.x = 10;
        top.y -= 100;
        btm.x = div_width + div_width / 10;
        btm.y += 100;
        region.push_back(make_pair(top, btm));
        rectangle(img_s, top, btm, Scalar(255, 0, 0), 2, 8, 0);
      } else {
        top.x = div_width;
        top.y -= 100;
        btm.x = 2 * div_width - 10;
        btm.y += 100;
        region.push_back(make_pair(top, btm));
        rectangle(img_s, top, btm, Scalar(255, 0, 0), 2, 8, 0);
      }
    } else if (section == 3) {
      if (top.x < div_width + div_width / 10) {
        top.x = 10;
        top.y -= 100;
        btm.x = div_width + div_width / 10;
        btm.y += 100;
        region.push_back(make_pair(top, btm));
        rectangle(img_s, top, btm, Scalar(255, 0, 0), 2, 8, 0);
      } else if (top.x > div_width + div_width / 10
                 && top.x < div_width * 2 + div_width / 10) {
        top.x = div_width;
        top.y -= 100;
        btm.x = 2 * div_width + div_width / 10;
        btm.y += 100;
        region.push_back(make_pair(top, btm));
        rectangle(img_s, top, btm, Scalar(255, 0, 0), 2, 8, 0);
      } else {
        top.x = 2 * div_width;
        top.y -= 100;
        btm.x = 3 * div_width - 10;
        btm.y += 100;
        region.push_back(make_pair(top, btm));
        rectangle(img_s, top, btm, Scalar(255, 0, 0), 2, 8, 0);
      }
    } else if (section == 1) {
      top.x = 10;
      top.y -= 100;
      btm.x = div_width - 10;
      btm.y += 100;
      region.push_back(make_pair(top, btm));
      rectangle(img_s, top, btm, Scalar(255, 0, 0), 2, 8, 0);
    }
  }

  /*
  stack <pair <Point, Point> > connect_pool;
  while (!region.empty()) {
    vector <pair <Point, Point> >::iterator it = region.begin();
    find_connection(it, connect_pool);
    merge_connection(img_s, connect_pool);
    while (!connect_pool.empty()) connect_pool.pop();
  }
  */

  end = time(NULL);
  cout << "Use: " << end - start << 's' << endl;

  // write result according to the input image name
  string write_file_name = "/home/panyutong/PytZone/TestPaper/Result_Quarter/";
  char *res_name = argv[1];
  int file_length = strlen(argv[1]);
  stack <char> name_bucket;
  for (int key = file_length - 1; res_name[key] != '/'; --key)
    name_bucket.push(res_name[key]);
  while(!name_bucket.empty()) {
    write_file_name += name_bucket.top();
    name_bucket.pop();
  }
  resize(img_s, img_s, Size(), 2, 2, CV_INTER_CUBIC);
  imwrite(write_file_name, img_s);

  return 0;
}

double calHog(Mat img) {
  Mat imgHdl;

  resize(img, imgHdl, Size(128, 32));

  HOGDescriptor *hog =
      new HOGDescriptor(cvSize(32, 16), cvSize(16, 16),
                        cvSize(16, 16), cvSize(8, 8), 9);

  vector<float> img_descriptors;

  hog->compute(imgHdl, img_descriptors, Size(2, 2), Size(0, 0));

  double cross = 0;
  for (int i = 0; i < img_descriptors.size(); ++i) {
    cross += img_descriptors[i] * tpl_descriptors[i];
  }
  return cross;
}

int find_candidate(Mat source, vector<Point> &can) {
  for (int rect_width = 56, rect_height = 15; rect_width <= 86;
       rect_width += 15, rect_height += 4) {
    for (int rect_x = 10; rect_x < source.cols - rect_width;
         rect_x +=  50) {
      for (int rect_y = 10; rect_y < source.rows - rect_height;
           rect_y +=  10) {
        Mat ROI(source, Rect(rect_x, rect_y, rect_width, rect_height));
        double score = 0;
        score = calHog(ROI);
        if (score > conf_value) {
          Point topLeft, btmRight;
          topLeft.x = rect_x, topLeft.y = rect_y;
          btmRight.x = rect_x + rect_width, btmRight.y = rect_y + rect_height;
          Point mid;
          mid.x = (topLeft.x + btmRight.x) / 2;
          mid.y = (topLeft.y + btmRight.y) / 2;
          can.push_back(mid);
          //rectangle(img_s, topLeft, btmRight, Scalar(255, 0, 0), 2, 8, 0);
        }
      }
    }
  }
  return can.size();
}

void find_connection(vector <pair <Point, Point> >::iterator it,
                     stack <pair <Point, Point> > &connect_pool) {
}

void merge_connection(Mat &display, stack <pair <Point, Point> > c_pool) {
}
