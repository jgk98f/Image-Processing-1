# Image-Processing-1
Basic of image processing using openCV library.

----------------------------------------------------------------------------
README
----------------------------------------------------------------------------
Author: Jason Klamert
Program: Objects
Date: 9/23/2016
Digital Image Processing
----------------------------------------------------------------------------
Summary:
----------------------------------------------------------------------------

The objects program draws a square, a rectangle, and a circle on a 640 x 480
plane. First I create a cv::Mat object that is one channel with 8 bits to 
represent a gray scale image. Then I proceed to call cvRectangle with a
randomly generated point. Another point is made from the random point to they
are fed into the cvRectangle function to draw the rectange. Then the pixels
are processed one at a time and their intensity is set by using: OXFF - 'd' 
where 'd' is the euclidian distance produced by:
d = sqrt(((x1+x2)^2) - ((y1+y2)^2))

This produces a gradient shading effect on the objects where the middle point
is white and as the distance grows, the pixels become darker, or lose
intensity. Both square objects are produced in the same fashion where two
points are calculated then the center is calculated for the intensity 
calculations. However, I had to switch the method of drawing the circle. 

I had to use the cvRectangle method to draw the circle and fill in the pixels
with a constant intensity of 255. I consider a rectangle around the circle a
region of interest (ROI) and give any pixel of intensity 255 a newly calculated
intensity of OXFF - distance from center. After this the image is displayed
for the user.

----------------------------------------------------------------------------
Directions:
----------------------------------------------------------------------------

Makefile:
	make -f MakeFile

clean:
	make -f MakeFile clean

run:
	objects
