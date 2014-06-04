balls_tracker
=============

Tracking multiple tennis balls using openCV

In this file two function have been implemented.
Below is pseudocode for them :

   
   main()
1  initialization for all hardware and data structure needed
2  while no key pressed
3  	fetch the current frame from stream
4  	convert the raw frame to hsv color space
5	threshold using green, blue and red value ranges
6	blur all three thresheld image
7	perform Hough transform, storing results containers
8	draw circles by calling draw function

	
   draw(mat, container) 
1  if the current container is not empty
2	for i = 0 to container.size - 1
3		if the circle is not too big nor too small
4			draw on mat using cv::circle
 
by Yue Wang 12027710
 
