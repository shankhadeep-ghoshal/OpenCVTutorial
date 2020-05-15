#include "opencv2/opencv.hpp"
#include <stdint.h>
#include <iostream>

#include "SplitAndMergeMat.h"


void splitAndMerge()
{
    std::string blue = "Blue";
    std::string green = "Green";
    std::string red = "Red";
    cv::Mat original = cv::imread("MyPic.jpg", cv::IMREAD_COLOR);
    cv::Mat splitChannel[3];

    cv::split(original, splitChannel);

    cv::namedWindow(blue, cv::WINDOW_FREERATIO);
    cv::namedWindow(green, cv::WINDOW_FREERATIO);
    cv::namedWindow(red, cv::WINDOW_FREERATIO);

    cv::resizeWindow(blue, original.rows / 3, original.cols / 3);
    cv::resizeWindow(green, original.rows / 3, original.cols / 3);
    cv::resizeWindow(red, original.rows / 3, original.cols / 3);

    cv::imshow(blue, splitChannel[0]);
    cv::imshow(green, splitChannel[1]);
    cv::imshow(red, splitChannel[2]);

    cv::waitKey();
}