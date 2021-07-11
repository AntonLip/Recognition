#pragma once
#include "IProcessing.h"

#include "opencv2\opencv.hpp"

#include <stdio.h>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>

class ProcessingCountours : public IProcessing
{
	cv::Mat comparrisImage_;
	cv::Mat masterImage_;
	cv::Mat processingImage_;
	//std::vector<std::vector<cv::Point>> masterContours_;
	//std::vector<cv::Vec4i> masterHiararchy_;
	int threshold_;
public:
	ProcessingCountours();
	ProcessingCountours(const ProcessingCountours& drop);
	ProcessingCountours(ProcessingCountours&& drop);
	void performProcessing(cv::Mat const* inputImage) override;
	void drawResultImage(cv::Mat& inOutPutImage) override;
	void setThreshold(std::vector<int> newThreshold) override;
	void getThreshold(std::vector<int>& outThreshold) override;
	int computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages) override;
	cv::Mat* getProcessingImage() override;
	void drawCountours(cv::Mat const* inputImage, std::vector<std::vector<cv::Point>> &contours);
};

