#include "ProcessingPositionAdjustment.h"

ProcessingPositionAdjustment::ProcessingPositionAdjustment()
{
	countorsProcessing_ = new ProcessingCountours();
}

ProcessingPositionAdjustment::ProcessingPositionAdjustment(const ProcessingPositionAdjustment& drop):
	comparrisImage_{drop.comparrisImage_},
	masterImage_{ drop.masterImage_ },
	processingImage_{ drop.processingImage_ },
	deltaAngel_{drop.deltaAngel_},
	deltsX_{drop.deltsX_},
	deltaY_{drop.deltaY_}
{
	if(drop.countorsProcessing_!=nullptr)
		countorsProcessing_ = new ProcessingCountours(*drop.countorsProcessing_);
}

void ProcessingPositionAdjustment::performProcessing(cv::Mat const* inputImage)
{
	countorsProcessing_->performProcessing(inputImage);
}

void ProcessingPositionAdjustment::drawResultImage(cv::Mat& inOutputImage)
{
	countorsProcessing_->drawResultImage(inOutputImage);
}

void ProcessingPositionAdjustment::setThreshold(std::vector<int> newThreshold)
{
	countorsProcessing_->setThreshold(newThreshold);
}

void ProcessingPositionAdjustment::getThreshold(std::vector<int>& outThreshold)
{
	countorsProcessing_->getThreshold(outThreshold);
}

int ProcessingPositionAdjustment::computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages, QtRotateRect roi)
{
	return 0;
}

cv::Mat* ProcessingPositionAdjustment::getProcessingImage()
{
	return &processingImage_;
}


