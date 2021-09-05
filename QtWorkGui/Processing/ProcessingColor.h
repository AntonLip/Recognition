#pragma once
#include "IProcessing.h"
class ProcessingColor : public IProcessing
{
	cv::Mat comparrisImage_;
	cv::Mat masterImage_;
	cv::Mat processingImage_;
	std::vector<int> h_threshelds_;
	std::vector<int> s_threshelds_;
	std::vector<int> v_threshelds_;
public:
	ProcessingColor();
	ProcessingColor(const ProcessingColor& drop);
	void performProcessing(cv::Mat const* inputImage) override;
	void drawResultImage(cv::Mat& inOutPutImage) override;
	void setThreshold(std::vector<int> newThreshold) override;
	void getThreshold(std::vector<int>& outThreshold) override;
	int computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages, QtRotateRect roi) override;
	cv::Mat* getProcessingImage() override;
};