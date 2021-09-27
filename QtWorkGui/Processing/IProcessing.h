#pragma once
#include <iostream>
#include <cmath>
#include "Loger/simplLoger.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "ProcessingObject/QtRotateRect.h"

class IProcessing
{
public:
	virtual void performProcessing(cv::Mat const* inputImage) = 0;
	virtual void drawResultImage(cv::Mat& inOutPutImage) = 0;
	virtual void setThreshold(std::vector<int> newThreshold) = 0;
	virtual void getThreshold(std::vector<int>& outThreshold) = 0;
	virtual float computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages, QtRotateRect roi) = 0;
	virtual cv::Mat* getProcessingImage() = 0;
	virtual ~IProcessing() {};
};

