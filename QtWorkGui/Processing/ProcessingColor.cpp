#include "ProcessingColor.h"

ProcessingColor::ProcessingColor():
	resultImage_{cv::Mat()},
	h_threshelds_{0,0},
	s_threshelds_{0,0},
	v_threshelds_{0,0}
{
}

ProcessingColor::ProcessingColor(const ProcessingColor& drop):
	resultImage_{drop.resultImage_},
	h_threshelds_{drop.h_threshelds_},
	s_threshelds_{drop.s_threshelds_},
	v_threshelds_{drop.v_threshelds_}
{
}

void ProcessingColor::performProcessing(cv::Mat const* inputImage)
{
	cv::cvtColor(*inputImage, resultImage_, CV_BGR2HSV);
	cv::inRange(resultImage_, cv::Scalar(h_threshelds_[0], s_threshelds_[0], v_threshelds_[0]),
				cv::Scalar(h_threshelds_[1], s_threshelds_[1], v_threshelds_[1]), resultImage_);
}

void ProcessingColor::drawResultImage(cv::Mat& inOutPutImage)
{
	cv::cvtColor(inOutPutImage, inOutPutImage, CV_RGB2GRAY);
	cv::cvtColor(inOutPutImage, inOutPutImage, CV_GRAY2RGB);
	cv::Mat objectColor(inOutPutImage.size(), inOutPutImage.type(), cv::Scalar(0, 255, 0));
	cv::Mat bufer(resultImage_);
	cv::cvtColor(bufer, bufer, CV_GRAY2BGR);
	cv::bitwise_and(bufer, objectColor, objectColor);
	cv::bitwise_not(bufer, bufer);
	cv::bitwise_and(inOutPutImage, bufer, inOutPutImage);
	cv::bitwise_or(inOutPutImage, objectColor, inOutPutImage);
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
	return nullptr;
}

int ProcessingColor::computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages)
{
	return 0;
}


