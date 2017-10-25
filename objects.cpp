/*
 * objects.cpp
 * Description: Program to draw a square, a rectangle, and a circle randomly on a plane of 640 x 480.
 * These objects are then shaded by adjusting the grayscale values using euclidian distance.
 *  Created on: Sep 19, 2016
 *      Author: Jason Klamert
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <ctime>
#include <cmath>
#include <iostream>

int getRandomX();
int getRandomY();
float getDistance(int, int, int, int);

int main( int argc, char** argv )
{
  srand(time(NULL));
  cv::Mat image(cv::Size(640,480), CV_8U, cv::Scalar::all(0));
  cv::Mat grayscale(image.size(), CV_MAKETYPE(image.depth(),1));
  IplImage img = grayscale;

  int x = getRandomX();
  int y = getRandomY();
  int x2 = x + 100;
  int y2 = y + 100;

  if(x2 > 640){
	  x2 = 639;
	  std::cout << "X2: " << x2 << std::endl;
  }
  if(y2 > 480){
	  y2 = 480;
	  std::cout << "Y2: " << y2 << std::endl;
  }

  int rx = getRandomX();
  int ry = getRandomY();
  int rx2 = rx + 200;
  int ry2 = ry + 160;

  if(rx2 > 640){
	rx2 = 639;
	std::cout << "RX2: " << rx2 << std::endl;
  }
  if(ry2 > 480){
	ry2 = 480;
	std::cout << "RY2: " << ry2 << std::endl;
  }

  int cx = getRandomX();
  int cy = getRandomY();

  std::cout << "CX: " << cx << std::endl;
  std::cout << "CY: " << cy << std::endl;

  int cKernelStartX = cx - 35;
  int cKernelStartY = cy - 35;

  std::cout << "cKernelStartX: " << cKernelStartX << std::endl;
  std::cout << "cKernelStartY: " << cKernelStartY << std::endl;

  if(cKernelStartX < 0)
  	cKernelStartX = 0;
  if(cKernelStartY < 0)
  	cKernelStartY = 0;

  int cKernelEndX = cKernelStartX + 70;
  int cKernelEndY = cKernelStartY + 70;

  std::cout << "cKernelEndX: " << cKernelEndX << std::endl;
  std::cout << "cKernelEndY: " << cKernelEndY << std::endl;


  if(cKernelEndX > 640){
  		cKernelEndX = 639;
		std::cout << "cKernelEndX: 640" << std::endl;	
	}
  if(cKernelEndY > 480){
		cKernelEndY = 480;
		std::cout << "cKernelEndY: 480" << std::endl;
  	}

  //Draw the Square and loop through the pixels to perform intensity changes.
  cvRectangle(&img,cvPoint(x,y),cvPoint(x2,y2), cv::Scalar(255),1);

  for(int rowNum = x; rowNum <= x2; rowNum++ ){
	  for(int colNum = y;colNum <= y2; colNum++){
		  if(rowNum == ((x + x2)/2) && colNum == ((y + y2)/2))
			  grayscale.at<uchar>(colNum, rowNum) = 255;
		  else
			  grayscale.at<uchar>(colNum, rowNum) = (0XFF - getDistance(rowNum,((x+x2)/2),colNum,((y+y2)/2)));
	  }
  }

  //Draw the Rectangle and loop through the pixels to perform intensity/grayscale changes based on distance from
  cvRectangle(&img,cvPoint(rx,ry),cvPoint( rx + 200 , ry + 160), cv::Scalar(255),1);

    for(int rowNum = rx; rowNum <= rx2; rowNum++ ){
          for(int colNum = ry; colNum <= ry2; colNum++){
                  if(rowNum == ((rx + rx2)/2) && colNum == ((ry + ry2)/2))
                          grayscale.at<uchar>(colNum, rowNum) = 255;
                  else
                          grayscale.at<uchar>(colNum, rowNum) = (0XFF - getDistance(rowNum,((rx+rx2)/2),colNum,((ry+ry2)/2)));
          }
  }

  //Draw the circle and process a region of interest (ROI) for adjusting the grayscale values, aka intensity. 
  cvCircle(&img,cvPoint(cx,cy), 35,cv::Scalar(255), -1);

  for(int rowNum = cKernelStartX; rowNum <= cKernelEndX; rowNum++ ){
          for(int colNum = cKernelStartY; colNum <= cKernelEndY; colNum++){
                  if(grayscale.at<uchar>(colNum,rowNum) == 255){
                         grayscale.at<uchar>(colNum, rowNum) = (0XFF - getDistance(rowNum,cx,colNum,cy));
                         }
                  else if(rowNum == cx && colNum == cy)
                          grayscale.at<uchar>(colNum, rowNum) = 255;
          }
  }
  
  //Display the newly generated image until the user exits out of the window.
  cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Display Image", grayscale );

  cv::waitKey(0);

  return 0;
}

/**
 * Author: Jason Klamert
 * Date: Sept 19th 2016
 * Get a random x value that is mod image width to assure the point is on the plane.
 **/
int getRandomX(){
	int z = (rand() % 640) +1;
	std::cout << "RandomX: " << z << std::endl;
	return z;
}

/**
 * Author: Jason Klamert
 * Date: Sept 19th 2016
 * Get a random y value that is mod image height to assure the point is on the plane.    
 **/
int getRandomY(){
	int y = (rand() % 480) + 1;
	std::cout << "RandomY: " << y << std::endl;
	return y;
}

/**
 * Author: Jason Klamert
 * Date: Sept 19th 2016
 * Get Euclidian distance from two points and return it.
 **/
float getDistance(int x1, int x2, int y1, int y2){

	float sumX = x1 - x2;
	float sumY = y1 - y2;
	float squareX = sumX * sumX;
	float squareY = sumY * sumY;
	float distance = sqrt(squareX + squareY);

	return distance;
}

