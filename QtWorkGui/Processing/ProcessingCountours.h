#pragma once
#include "IProcessing.h"
class ProcessingCountours : public IProcessing
{
	std::vector<std::vector<cv::Point>> masterContours_;
	std::vector<cv::Vec4i> masterHiararchy_;
	int threshold_;
public:
	ProcessingCountours();
	ProcessingCountours(const ProcessingCountours& drop);
	virtual void performProcessing(cv::Mat const* inputImage) override;
	virtual void drawProcessing(cv::Mat& inOutPutImage) override;
};

