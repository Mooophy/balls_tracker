#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>



int main( )
{
    /**
     * @brief open default camara
     */
    cv::VideoCapture cap(1);
    if(!cap.isOpened())
    {
        std::cout << "failed to open cam!\n";
        return -1;
    }

    while(true)
    {
        /**
         * @brief fetch the current frame from stream.
         */
        cv::Mat raw,gray;
        cap >> raw;

        cv::cvtColor(raw,gray,cv::COLOR_BGR2GRAY);

        cv::imshow("original", raw);
        cv::imshow("gray", gray);

        /**
         * @brief terminate the program when any key pressed
         */
        if(cv::waitKey(30) >= 0)
            break;
    }

  return 0;
}

