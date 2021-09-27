#include "ProcessingColor.h"

ProcessingColor::ProcessingColor():
	comparrisImage_{ cv::Mat() },
	masterImage_{ cv::Mat() },
	processingImage_{ cv::Mat() },
	h_threshelds_{0,0},
	s_threshelds_{0,0},
	v_threshelds_{0,0}
{
}

ProcessingColor::ProcessingColor(const ProcessingColor& drop):
	comparrisImage_{ drop.comparrisImage_ },
	masterImage_{ drop.masterImage_ },
	processingImage_{ drop.processingImage_ },
	h_threshelds_{drop.h_threshelds_},
	s_threshelds_{drop.s_threshelds_},
	v_threshelds_{drop.v_threshelds_}
{
}

void ProcessingColor::performProcessing(cv::Mat const* inputImage)
{
	cv::cvtColor(*inputImage, processingImage_, CV_BGR2HSV);
	cv::inRange(processingImage_, cv::Scalar(h_threshelds_[0], s_threshelds_[0], v_threshelds_[0]),
				cv::Scalar(h_threshelds_[1], s_threshelds_[1], v_threshelds_[1]), processingImage_);
}

void ProcessingColor::drawResultImage(cv::Mat& inOutPutImage)
{
	cv::cvtColor(inOutPutImage, inOutPutImage, CV_RGB2GRAY);
	cv::cvtColor(inOutPutImage, inOutPutImage, CV_GRAY2RGB);
	if (comparrisImage_.size().width == 0)
	{
		cv::Mat objectColor(inOutPutImage.size(), inOutPutImage.type(), cv::Scalar(0, 255, 0));
		cv::Mat bufer(processingImage_);
		cv::cvtColor(bufer, bufer, CV_GRAY2BGR);
		cv::bitwise_and(bufer, objectColor, objectColor);
		cv::bitwise_not(bufer, bufer);
		cv::bitwise_and(inOutPutImage, bufer, inOutPutImage);
		cv::bitwise_or(inOutPutImage, objectColor, inOutPutImage);
	}
	else
	{
		cv::Mat mask(comparrisImage_.size(), CV_8UC1);
		cv::cvtColor(comparrisImage_, mask, CV_BGR2GRAY);
		cv::threshold(mask, mask, 1, 255, CV_THRESH_BINARY);
		cv::bitwise_not(mask, mask);
		cv::cvtColor(mask, mask, CV_GRAY2BGR);
		cv::bitwise_and(inOutPutImage, mask, inOutPutImage);
		cv::bitwise_or(inOutPutImage, comparrisImage_, inOutPutImage);
		cv::Mat bufer(inOutPutImage);
	}
	//cv::bitwise_not(resultImage_, resultImage_);
}

void ProcessingColor::setThreshold(std::vector<int> newThreshold)
{
	h_threshelds_[0] = newThreshold[0];
	h_threshelds_[1] = newThreshold[1];
	s_threshelds_[0] = newThreshold[2];
	s_threshelds_[1] = newThreshold[3];
	v_threshelds_[0] = newThreshold[4];
	v_threshelds_[1] = newThreshold[5];
}

void ProcessingColor::getThreshold(std::vector<int>& outThreshold)
{
	outThreshold.clear();
	outThreshold.push_back(h_threshelds_[0]);
	outThreshold.push_back(h_threshelds_[1]);
	outThreshold.push_back(s_threshelds_[0]);
	outThreshold.push_back(s_threshelds_[1]);
	outThreshold.push_back(v_threshelds_[0]);
	outThreshold.push_back(v_threshelds_[1]);
}

cv::Mat* ProcessingColor::getProcessingImage()
{
	return &processingImage_;
}

float ProcessingColor::computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages, QtRotateRect roi)
{
	cv::Mat matchedPart(masterImages->size(), CV_8UC1);
	cv::bitwise_and(*masterImages, processingImage_, matchedPart);
	cv::Mat bufer_(processingImage_);
	cv::Mat mismatchedPart_1(masterImages->size(), CV_8UC1);
	cv::bitwise_xor(processingImage_, matchedPart, mismatchedPart_1);
	cv::Mat mismatchedPart_2(masterImages->size(), CV_8UC1);
	cv::bitwise_xor(*masterImages, matchedPart, mismatchedPart_2);
	cv::cvtColor(matchedPart, matchedPart, CV_GRAY2BGR);
	cv::bitwise_and(matchedPart, cv::Mat(masterImages->size(), CV_8UC3, cv::Scalar(0, 255, 0)), matchedPart);
	cv::bitwise_or(mismatchedPart_1, mismatchedPart_2, mismatchedPart_2);
	cv::cvtColor(mismatchedPart_2, mismatchedPart_2, CV_GRAY2BGR);
	cv::bitwise_and(mismatchedPart_2, cv::Mat(masterImages->size(), CV_8UC3, cv::Scalar(0, 0, 255)), mismatchedPart_2);
	comparrisImage_ = cv::Mat(cv::Mat(masterImages->size(), CV_8UC3, cv::Scalar(0, 0, 0)));
	cv::bitwise_or(mismatchedPart_2, matchedPart, comparrisImage_);
	cv::Mat bufer(comparrisImage_);
	return 0;
}


