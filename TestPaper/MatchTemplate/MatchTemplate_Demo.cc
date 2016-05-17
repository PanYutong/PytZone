#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat img; Mat templ; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result Window";

int match_method = 5;
int max_Trackbar = 5;

Mat img_display;

/// Function Headers
void MatchingMethod( int, void* );

int main( int, char** argv )
{
  /// Load image and template
  img = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  img.copyTo( img_display );
  threshold(img, img, 150, 255, THRESH_BINARY);
  Mat element = getStructuringElement(MORPH_RECT, Size(11, 11), Point(5, 5) );
  morphologyEx(img, img, CV_MOP_OPEN, element);
  imwrite("/home/panyutong/img.png", img);

  templ = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE);
  threshold(templ, templ, 150, 255, THRESH_BINARY);
  morphologyEx(templ, templ, CV_MOP_OPEN, element);
  imwrite("/home/panyutong/templ.png", templ);

  /// Create windows
  namedWindow( image_window, WINDOW_AUTOSIZE );
  namedWindow( result_window, WINDOW_AUTOSIZE );

  /// Create Trackbar
  const char* trackbar_label =
      "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n \
      3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
  createTrackbar(trackbar_label, image_window,&match_method,
                 max_Trackbar, MatchingMethod );

  MatchingMethod( 0, 0 );

  waitKey(0);
  return 0;
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
  /// Source image to display

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_rows, result_cols, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );


  if (match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
  { matchLoc = minLoc; }
  else
  { matchLoc = maxLoc; }

  float MAX = result.at<float>(0, 0);
  float MIN = result.at<float>(0, 0);

  for (int i = 0; i < result.rows; ++i) {
    for (int j = 0; j < result.cols; ++j) {
      if (result.at<float>(i, j) > MAX) MAX = result.at<float>(i, j);
      if (result.at<float>(i, j) < MIN) MIN = result.at<float>(i, j);
      if (result.at<float>(i, j) >= (float)0.78) {
        Point headLeft;
        headLeft.x = j;
        headLeft.y = i;
        rectangle(img_display, headLeft, Point(j + templ.cols, i + templ.rows ),
                  Scalar::all(0), 2, 8, 0 );
        rectangle(result, headLeft, Point(j + templ.cols, i + templ.rows ),
                  Scalar::all(0), 2, 8, 0 );
      }
    }
  }
  Mat RectTest;
  Rect rect;
  rect.x = matchLoc.x;
  rect.y = matchLoc.y;
  rect.width = templ.cols + 100;
  rect.height = templ.rows + 100;
  RectTest = img_display(rect);
  imwrite("/home/panyutong/out.png", img_display);

  return;
}
