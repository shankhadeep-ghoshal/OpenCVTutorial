#include "opencv2/opencv.hpp"
#include <iostream>

#include "DFT.h"

void recenterDFT(cv::Mat& src) {
	cv::Mat swapMat;
	int centerX = src.cols / 2;
	int centerY = src.rows / 2;

	cv::Mat q1(src, cv::Rect(0, 0, centerX, centerY));
	cv::Mat q2(src, cv::Rect(centerX, 0, centerX, centerY));
	cv::Mat q3(src, cv::Rect(0, centerY, centerX, centerY));
	cv::Mat q4(src, cv::Rect(centerX, centerY, centerX, centerY));

	q1.copyTo(swapMat);
	q4.copyTo(q1);
	swapMat.copyTo(q4);

	q2.copyTo(swapMat);
	q3.copyTo(q2);
	swapMat.copyTo(q3);
}

void doDft(cv::Mat& src, cv::Mat& dest) {

	cv::Mat originalComplex[2] = { src, cv::Mat::zeros(src.size(), CV_32F) };
	cv::Mat dftMat;
	cv::Mat forDftMat;

	cv::merge(originalComplex, 2, forDftMat);
	cv::dft(forDftMat, dftMat, cv::DFT_COMPLEX_INPUT);

	dest = dftMat;
}

void doInverseDFT(cv::Mat& src, cv::Mat& dest) {
	cv::Mat inverseDft;

	cv::idft(src, inverseDft, cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);

	dest = inverseDft;
}

void visualizeDFT(cv::Mat& src) {
	cv::Mat splitArrays[2] = { cv::Mat::zeros(src.size(), CV_32F), cv::Mat::zeros(src.size(), CV_32F) };

	cv::split(src, splitArrays);

	cv::Mat dftMagnitude;

	cv::magnitude(splitArrays[0], splitArrays[1], dftMagnitude);

	dftMagnitude += cv::Scalar::all(1);

	cv::log(dftMagnitude, dftMagnitude);
	cv::normalize(dftMagnitude, dftMagnitude, 0, 1, cv::NORM_MINMAX);

	recenterDFT(dftMagnitude);

	std::string dftName = "DFT";

	cv::namedWindow(dftName, cv::WINDOW_FREERATIO);
	cv::resizeWindow(dftName, dftMagnitude.rows / 3, dftMagnitude.cols / 3);
	cv::imshow(dftName, dftMagnitude);
	cv::waitKey();
}

void performDFT()
{
	cv::Mat original = cv::imread("MyPic.jpg", cv::IMREAD_GRAYSCALE);
	cv::Mat originalFloat;
	cv::Mat dftFiedMat;
	std::string inverseDtfName = "Inverse DFT";

	original.convertTo(originalFloat, CV_32F, 1.0 / 255.0);
	doDft(originalFloat, dftFiedMat);
	visualizeDFT(dftFiedMat);

	cv::Mat inverseDFT;
	doInverseDFT(dftFiedMat, inverseDFT);

	cv::namedWindow(inverseDtfName, cv::WINDOW_FREERATIO);
	cv::resizeWindow(inverseDtfName, inverseDFT.rows / 3, inverseDFT.cols / 3);
	cv::imshow(inverseDtfName, inverseDFT);
	cv::waitKey();
}
