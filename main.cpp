#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>
#include <cstring>
#include <highgui.h>
#include <math.h>

int main( )
{
     //! test for usb camara
    cv::VideoCapture cap(0);
    if(!cap.isOpened())
    {
        std::cout << "failed to open cam!\n";
        return -1;
    }

    std::vector<cv::Vec3f> circles;

    while(true)
    {
        //! raw image
        cv::Mat raw,gray, hsv, blue,red,green, output;
        cap >> raw;
/*

        cv::cvtColor(raw,hsv,cv::COLOR_BGR2HSV);
        cv::imshow("hsv",hsv);

        //cv::inRange(hsv,cv::Scalar(100,100,100),cv::Scalar(120,255,255), blue);
        //cv::imshow("blue",blue);

        //! red range [150,100,100],[179,255,255];
        cv::inRange(hsv,cv::Scalar(150,100,100),cv::Scalar(179,255,255), red);



        cv::imshow("red", red);
*/
        cv::cvtColor(raw,gray, cv::COLOR_BGR2GRAY);

        cv::GaussianBlur( gray, gray, cv::Size(9, 9), 2, 2 );


        cv::HoughCircles(gray,circles,CV_HOUGH_GRADIENT, 3, 10000,100,20,40);

        if(!circles.empty() && circles[0][2] > 10 && circles[0][2] < 80)
        {
            std::cout << *circles.begin() << std::endl;
            cv::circle(raw,cv::Point(circles[0][0],circles[0][1]), 45, cv::Scalar(0),3);
        }

        //cv::circle(raw,cv::Point(0,0),50,cv::Scalar(0));
        cv::imshow("raw",raw );

        if(cv::waitKey(30) >= 0) break;
    }

  return 0;
}
