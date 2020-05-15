#include "opencv2/opencv.hpp"
#include <stdint.h>
#include <iostream>
#include "AccessPixels.h"

void accessPixels()
{
    std::string originalName = "Original";
    std::string modifiedName = "Modified";
    cv::Mat original = cv::imread("MyPic.jpg", cv::IMREAD_COLOR);
    cv::Mat copied(original.size(), original.type());
    original.copyTo(copied);

    for (int row = 0; row < copied.rows; row++)
    {
        for (int col = 0; col < copied.cols; col++) {
            //copied.at<uint8_t>(row, col) = copied.at<uint8_t>(row, col) * 0.9f;
            copied.at<cv::Vec3b>(row, col)[0] = copied.at<cv::Vec3b>(row, col)[0] * 0;
        }
    }

    cv::namedWindow(originalName, cv::WINDOW_FREERATIO);
    cv::namedWindow(modifiedName, cv::WINDOW_FREERATIO);

    cv::resizeWindow(originalName, original.rows / 2, original.cols / 2);
    cv::resizeWindow(modifiedName, copied.rows / 2, copied.cols / 2);

    cv::imshow(originalName, original);
    cv::imshow(modifiedName, copied);

    cv::waitKey();
}
