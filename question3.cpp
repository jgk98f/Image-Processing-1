/**
 * Author: Jason Klamert
 * Date: 10/09/2016
 * Description: Program to find image statistics and calculate the histogram. The histogram is displayed at the end
 * of the program and some conclusions are reached based on some basic information found thorughout the program.
 **/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#define DEBUG false

int main( int argc, char** argv )
{
  srand(time(NULL));

  //Usage check!
  if ( argc < 1)
  {
        std::cerr << "usage: " << "Program " << argv[0] << " takes an image as an argument!\n" << std::endl;
        return ( 1 );
  }

  cv::Mat imageOne = cv::imread(argv[1]);
  
  //Empty check!
  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }

  //Initialize and declare vars.
  double min,max = 0;
  int normalizedHistogram[256];
  cv::Mat normalizedImage(cv::Size(256,256), CV_8UC1,cv::Scalar(255));  
  float coefficientOfVariation = 0;
  int const totalBins = 256;
  bool assertion = false;
  int accumulator = 0;
  int sumOfSquares = 0;
  float standardDeviation = 0;
  float variance = 0;
  int meanAccumulator = 0;
  short int mean = 0;
  imageOne.convertTo(imageOne,CV_8UC1);
  int histogram[totalBins];

  //Set all histogram to 0.
  for(int count = 0; count < totalBins; count++){
	histogram[count] = 0;
  }
	  //Count all of the intensity values found at each pixel and place it in histogram. In addition add up all of
	  //the values found so we can take the mean later.
	  for(int rowNum = 0; rowNum < imageOne.rows; rowNum++ ){
	          for(int colNum = 0;colNum < imageOne.cols; colNum++){
	
	              	if(DEBUG == true)
			{
	                	//std::cout << "imageOne " << "row: " << rowNum << " col: " << colNum << " Itensity: " 
				//<<  (int) imageOne.at<uchar>(colNum,rowNum) << std::endl;
	                }
			
			int temp = (int)  imageOne.at<uchar>(colNum,rowNum);
 			meanAccumulator += temp;
	                histogram[temp] = histogram[temp] + 1;
			accumulator = accumulator + 1;
	          }
	  }

  //Find the mean intensity of the image.
  mean = (short int) (meanAccumulator/(imageOne.rows*imageOne.cols));

	 //Calculate variance summation of the image from the mean.
	 for(int rowNum = 0; rowNum < imageOne.rows; rowNum++){
		for(int colNum = 0; colNum < imageOne.cols; colNum++){
		
			int temp = (int) imageOne.at<uchar>(colNum,rowNum);
			int result = temp - mean;
			result = result * result;
			sumOfSquares += result;
		}
	 }

  //Find the max element in the image and use this later.
  max = histogram[0];
  for(int count = 1; count < 256; count++){
	if(max < histogram[count]){
		max = histogram[count];
 	}
  }

  //Create a normalized histogram so we may graph it!
  for(int count = 0; count < 256; count++){
	normalizedHistogram[count] = ((256/max) * histogram[count]);
  }

  //compute the standard deviation and coefficient Of Variation for the data set.
  variance = (sumOfSquares/((imageOne.rows*imageOne.cols) - 1));
  standardDeviation = sqrt(variance);
  coefficientOfVariation = standardDeviation/mean;

  //Graph out wonderful normalized histogram using a binary image.
  for(int rowNum = 0; rowNum < 256; rowNum++){
	int colNum = normalizedHistogram[rowNum];
	while(colNum > 0){
		if(DEBUG == true){
		std::cout << "hist: col: " << colNum << " row: " << rowNum << " inten: " << (int) normalizedImage.at<uchar>(colNum,rowNum) << "\n";
		}

		normalizedImage.at<uchar>(colNum,rowNum) = 0;
		colNum--;
	}
  }

  //Flip our newly drawn image about the x axis for our viewing pleasure.
  flip(normalizedImage, normalizedImage,0);

  //Draw conclusions from our statistical measures.
  if(DEBUG == true){
	for(int count = 0; count < 256; count++){
        	std::cout << "Intensity Level: " << count << " has " << histogram[count] << " pixels.\n";
  	}
        std::cout << "imageOne: Rows: " << imageOne.rows << std::endl;
        std::cout << "imageOne: Cols: " << imageOne.cols << std::endl;
	std::cout << "imageOne: total pixels: " << imageOne.rows * imageOne.cols << std::endl;
	std::cout << "imageOne: pixels processed for histogram: " << accumulator << std::endl;
	std::cout << "imageOne: mean intensity for image: " << mean << std::endl;
	std::cout << "imageOne: standard deviation: " << standardDeviation << std::endl;
	std::cout << "imageOne: variance: " << variance << std::endl;
  }else{
  	std::cout << "imageOne: mean intensity for image: " << mean << std::endl;
        std::cout << "imageOne: standard deviation: " << standardDeviation << std::endl;
        std::cout << "imageOne: variance: " << variance << std::endl;
	
	if(mean > 192)
	std::cout << "Since the image's mean is greater than 192, the image is quite bright." << std::endl;
	else if(mean > 128 && mean < 192)
	std::cout << "Since the image's mean is in between 128 and 192, the image is relatively bright compared to most." << std::endl;
	else if(mean > 64 && mean < 128)
	std::cout << "Since the image's mean is in between 64 and 128, the image is relatively dark compared to the average." << std::endl;	 else if(mean < 64)
	std::cout << "Since the image's mean is less than 64, the image is quite dark." << std::endl;
	
	if(coefficientOfVariation >= 1){
		std::cout << "Using the coefficient of variation, normalized from standard deviation, is greater than 1, the image has"
		<< " a relatively high contrast." << std::endl;
	}else if(coefficientOfVariation < 1){
		std::cout << "Using the coefficient of variation, normalized from standard deviation, is less than 1, the image has"
		<< " a relatively low contrast." << std::endl;
	}
	
	
  }
  
  if(accumulator != (imageOne.rows*imageOne.cols)){
	assertion = false;
 	std::cout << "Error: The number of pixels counted and the number of pixels in the image are not equal!\n";
	return(-1);
  }

  //Finally, display the image.
  cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Display Image", normalizedImage );
  cv::waitKey(0);

  return 0;
}
