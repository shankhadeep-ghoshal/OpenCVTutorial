#include "opencv2/opencv.hpp"
#include <opencv2/core/types.hpp>
#include <stdint.h>

#include "AccessPixels.h"
#include "SplitAndMergeMat.h"
#include "DFT.h"
#include "PerformGaussian.h"

int main(int srgv, char** argc)
{
	performGaussian(cv::Size(256,256), 256/2, 256/2, 10, 10);
}