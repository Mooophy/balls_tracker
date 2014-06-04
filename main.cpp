#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>


/**
 * @brief draw
 *
 * draw circles on the mamt using information from the container.
 */
void draw(cv::Mat& mat, const std::vector<cv::Vec3f>& container);

int main( )
{
    using Container = std::vector<cv::Vec3f>;

    /**
     * @brief open default camara
     */
    cv::VideoCapture cap(0);
    if(!cap.isOpened())
    {
        std::cout << "failed to open cam!\n";
        return -1;
    }

    /**
     * @brief build containers for the three colors
     */
    Container red_balls, green_balls, blue_balls;

    while(true)
    {
        /**
         * @brief fetch the current frame from stream.
         */
        cv::Mat raw;
        cap >> raw;

        /**
         * @brief convert raw to hsv.
         */
        cv::Mat hsv;
        cv::cvtColor(raw, hsv, cv::COLOR_BGR2HSV);

        /**
         * @brief thresholding for green, blue and red respectively.
         */
        cv::Mat green, blue, red;
        cv::inRange(hsv, cv::Scalar(40 ,70,130), cv::Scalar(70 ,255,255), green);
        cv::inRange(hsv, cv::Scalar(100,100,100), cv::Scalar(120,255,255), blue );
        cv::inRange(hsv, cv::Scalar(150,100,100), cv::Scalar(179,255,255), red  );

        /**
         * @brief blur each mat.
         */
        cv::GaussianBlur(green,green, cv::Size(9,9), 2, 2);
        cv::GaussianBlur(blue ,blue , cv::Size(9,9), 2, 2);
        cv::GaussianBlur(red  ,red  , cv::Size(9,9), 2, 2);

        /**
         * @brief seach and store results to containers.
         */
        cv::HoughCircles(green, green_balls, CV_HOUGH_GRADIENT, 1, 195, 100, 12 ,40);
        cv::HoughCircles(blue , blue_balls , CV_HOUGH_GRADIENT, 1, 195, 205, 12 ,40);
        cv::HoughCircles(red  , red_balls  , CV_HOUGH_GRADIENT, 2, 800, 560, 12 ,40);

        /**
         * @brief gray images for debugging
         */
//        imshow("green", green);
//        imshow("blue ", blue );
//        imshow("red  ", red  );

        /**
         * @brief print how many balls detected for each color.
         */
        std::cout << "green:  " << green_balls.size() << std::endl;
        std::cout << "blue :  " << blue_balls.size()  << std::endl;
        std::cout << "red  :  " << red_balls.size()   << std::endl;

        /**
         * @brief draw on the original mat
         */
        draw(raw, green_balls);
        draw(raw, blue_balls );
        draw(raw, red_balls  );
        cv::imshow("final", raw);

        /**
         * @brief terminate the program when any key pressed
         */
        if(cv::waitKey(30) >= 0)
            break;
    }
  return 0;
}

/**
 * @brief draw
 * @param mat
 * @param container
 *
 * draw circles on the mat using information from the container.
 */
void draw(cv::Mat& mat, const std::vector<cv::Vec3f>& container)
{
    if(!container.empty())
        for(unsigned i = 0; i != container.size() && i != 4; ++i)
            if(container[i][2] > 5 && container[i][2] < 80)
                cv::circle(mat, cv::Point(container[i][0], container[i][1]), 45, cv::Scalar(0), 3);
}
