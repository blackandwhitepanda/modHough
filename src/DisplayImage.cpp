#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

using namespace cv;
using namespace std;

Mat loadAsGray( char* filename ) {
	Mat src, gray;
	src = imread( filename );
	if( !src.data )
	{ return gray; }

	// Convert it to gray
	cvtColor( src, gray, CV_RGB2GRAY );

	return gray;
}

/** @function main */
int main( int argc, char** argv )
{

  Mat src, src_gray;
  Mat grad, thresh_grad;
  char* window_name = "Sobel";
  char* window_name2 = "Threshold";
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;
  int thresh = 150;
  size_t L = 1;

  // Load an image
  //char* filename = argc >= 2 ? argv[1] : "./aquarium.png";
  //src = imread( filename );
  //if( !src.data )
  //{ return -1; }

  //GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

  // Convert it to gray
  //cvtColor( src, src_gray, CV_RGB2GRAY );

  src_gray = loadAsGray( argv[1] );

  // Sobel Filter
  /// Generate grad_x and grad_y
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;
  /// Gradient X
  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_x, abs_grad_x );
  /// Gradient Y
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_y, abs_grad_y );
  /// Total Gradient (approximate)
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

  // threshold
  threshold( grad, thresh_grad, thresh, 255, 3);


  // create accumulator array
  //int w = thresh_grad.cols;
  //int h = thresh_grad.rows;
  //double hough_h = ((sqrt(2.0) * (double)(h>w?h:w) / 2.0 ));
  //double accu_h = hough_h * 2.0;
  //double accu_w = 180;

  vector<Vec4i> accu;

   // for each pixel
  for( size_t y = 0; y < thresh_grad.rows - 1; y++ ) {
	  for( size_t x = 0; x < thresh_grad.cols - 1; x++ ) {

		  if(thresh_grad.at<uint>(x,y) > 0) {

		  	  // for each theta
		  	  for( size_t t = 0; t < 180 - 1; t++ ) {
				  //foreach(point on Gerade(x,y,t) {
		  		  	  //if (Bedingungen == TRUE) {
		  		  	  	  //accumulate(accu,x,y,t,L);
		  		  	  //}
		  	  	  //}
		  	  }

		  }

	    }
  }

  /// Create window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );
  namedWindow( window_name2, CV_WINDOW_AUTOSIZE );
  // Show images
  imshow( window_name, grad );
  imshow( window_name2, thresh_grad );

  waitKey(0);

  return 0;
}
