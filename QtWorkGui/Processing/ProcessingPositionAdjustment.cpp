#include "ProcessingPositionAdjustment.h"

ProcessingPositionAdjustment::ProcessingPositionAdjustment()
{
	countorsProcessing_ = new ProcessingCountours();
}

ProcessingPositionAdjustment::ProcessingPositionAdjustment(const ProcessingPositionAdjustment& drop):
	comparrisImage_{drop.comparrisImage_},
	masterImage_{ drop.masterImage_ },
	originalImage_{drop.originalImage_},
	deltaAngel_{drop.deltaAngel_},
	deltsX_{drop.deltsX_},
	deltaY_{drop.deltaY_}
{
	if(drop.countorsProcessing_!=nullptr)
		countorsProcessing_ = new ProcessingCountours(*drop.countorsProcessing_);
}

void ProcessingPositionAdjustment::performProcessing(cv::Mat const* inputImage)
{
	try 
	{
		throw;
	}
	catch (...)
	{
		LOG.logMessege("Exeption in ProcessingPositionAdjustment. Dont call performProcessing(cv::Mat const* inputImage)", LogLevel::_ERROR_);
	}
}

void ProcessingPositionAdjustment::performProcessing(cv::Mat const* inputImage, cv::Rect const* roi)
{
	inputImage->copyTo(originalImage_);
	countorsProcessing_->performProcessing(&(originalImage_(*roi)));
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
	cv::Mat rotateImage{};
	int topAndBottonBorder{ static_cast<int>(roi.getDiagonal() - roi.height()) / 2 };
	int leftAndRigthBorder{ static_cast<int>(roi.getDiagonal() - roi.width()) / 2 };
	cv::copyMakeBorder(*masterImages, rotateImage, topAndBottonBorder, topAndBottonBorder, leftAndRigthBorder, leftAndRigthBorder, cv::BORDER_CONSTANT, cv::Scalar(0));
	roi.setX(roi.x() + leftAndRigthBorder);
	roi.setY(roi.y() + topAndBottonBorder);
	cv::Rect searchRoi{ 0,0,rotateImage.size().width, rotateImage.size().height };
	for (int r{ 0 }; r < originalImage_.rows - rotateImage.cols; r+=5)
	{
		searchRoi.y = r;
		for (int c{ 0 }; c < originalImage_.cols - rotateImage.rows; c+=5)
		{
			searchRoi.x = c;
			for (int i{ 5 }; i < 20;)
			{
				
				cv::Mat rotateMatrix{ cv::getRotationMatrix2D(cv::Point2f(rotateImage.rows / 2.0, rotateImage.rows / 2.0), i, 1.0) };
				cv::warpAffine(rotateImage, rotateImage, rotateMatrix, rotateImage.size());
				cv::threshold(rotateImage, rotateImage, 0, 255, cv::THRESH_OTSU);
				countorsProcessing_->performProcessing(&originalImage_(searchRoi));
				roi.setRotateAngel(360.0 - i);
				countorsProcessing_->computeComparsion(isSingelThresold, comparsionThreshold, &rotateImage, roi);
				i += 5;
			}
		}
	}
	return 0;
}

cv::Mat* ProcessingPositionAdjustment::getProcessingImage()
{
	return countorsProcessing_->getProcessingImage();
}


