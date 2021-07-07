#pragma once
#include "IProcessing.h"
class ProcessingCountours : public IProcessing
{
	cv::Mat resultImage_;
	//std::vector<std::vector<cv::Point>> masterContours_;
	//std::vector<cv::Vec4i> masterHiararchy_;
	int threshold_;
public:
	ProcessingCountours();
	ProcessingCountours(const ProcessingCountours& drop);
	ProcessingCountours(ProcessingCountours&& drop);
	void performProcessing(cv::Mat const* inputImage) override;
	void drawProcessing(cv::Mat& inOutPutImage) override;
	void setThreshold(std::vector<int> newThreshold) override;
	void drawCountours(cv::Mat const* inputImage, std::vector<std::vector<cv::Point>> &contours);
};

