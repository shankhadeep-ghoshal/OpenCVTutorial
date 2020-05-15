#include "opencv2/opencv.hpp"
#include <stdint.h>

#include "PerformGaussian.h"

void performGaussian(const cv::Size& size, int uX, int uY, float sigmaX, float sigmaY, float amplitude) {
	cv::Mat output = cv::Mat(size, CV_32F);

	for (int row = 0; row < size.height; row++) {
		for (int col = 0; col < size.width; col++) {
			float x = (((float)col - uX) * (col - uX)) / (2.0f * (sigmaX * sigmaX));
			float y = (((float)row - uY) * (row - uY)) / (2.0f * (sigmaY * sigmaY));
			float gaussianValue = amplitude * exp(-(x + y));
			output.at<float>(row, col) = gaussianValue;
		}
	}

	cv::normalize(output, output, 0.0f, 1.0f, cv::NORM_MINMAX);
	cv::imshow("Gaussian", output);
	cv::waitKey();
}
