#pragma once
#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class IProcessing
{
public:
	virtual void performProcessing(cv::Mat const* inputImage) = 0;
	virtual void drawResultImage(cv::Mat& inOutPutImage) = 0;
	virtual void setThreshold(std::vector<int> newThreshold) = 0;
	virtual void getThreshold(std::vector<int>& outThreshold) = 0;
	virtual int computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages) = 0;
	virtual cv::Mat* getProcessingImage() = 0;
	virtual ~IProcessing() {};
};

