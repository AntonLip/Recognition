#include "ProcessingPositionAdjustment.h"

cv::Rect ProcessingPositionAdjustment::findLimitRectangel(cv::Mat* const masterImage, QtRotateRect roi)
{
	std::vector<cv::Point2f> keyPoints{};
	cv::Point2i bais{};
	findKeyPoints(masterImage, keyPoints,bais);
	int quantityPointInRoi[10]{};
	QtRotateRect searchArears[10]{};
	int numberBestRoi{ 0 };
	for (size_t i{ 0 }; i < keyPoints.size(); ++i)
	{
		searchArears[i]=QtRotateRect(roi.getOriginalRect(), roi.getRotateAngel(), QPoint(keyPoints[i].x, keyPoints[i].y));
		for (size_t j{ 0 }; j < keyPoints.size(); ++j)
		{
			if (searchArears[i].contains(keyPoints[j].x, keyPoints[j].y))
				++quantityPointInRoi[i];
		}
		if (quantityPointInRoi[i] > quantityPointInRoi[numberBestRoi])
			numberBestRoi = i;
	}
	cv::Point upLefet{ searchArears[0].getMin_X(), searchArears[0].getMin_Y() }, downRigth{ searchArears[0].getMax_X(), searchArears[0].getMax_Y() };
	for (size_t i{ 1 }; i < keyPoints.size(); ++i)
	{
		if (static_cast<float>(quantityPointInRoi[i]) / quantityPointInRoi[numberBestRoi] >= 0.75)
		{
			if (upLefet.x > searchArears[i].getMin_X())
				upLefet.x = searchArears[i].getMin_X();
			if (upLefet.y > searchArears[i].getMin_Y())
				upLefet.y = searchArears[i].getMin_Y();
			if (downRigth.x < searchArears[i].getMax_X())
				downRigth.x = searchArears[i].getMax_X();
			if (downRigth.y < searchArears[i].getMax_Y())
				downRigth.y = searchArears[i].getMax_Y();
		}
	}
	/*upLefet.x += bais.x;
	upLefet.y += bais.y;
	downRigth.x += bais.x;
	downRigth.y += bais.y;*/
	return cv::Rect(upLefet,downRigth);
}

void ProcessingPositionAdjustment::findKeyPoints(cv::Mat* const masterImage, std::vector<cv::Point2f>& keyPoints, cv::Point2i& bais)
{
	cv::SURF orb;
	//std::vector<cv::KeyPoint> keyPointMasterImage, keyPointTestImage;
	orb.detect(*masterImage, keyPointMasterImage);
	orb.detect(originalImage_, keyPointTestImage);
	cv::Mat descriptMaster, descriptTest;
	orb.compute(*masterImage, keyPointMasterImage, descriptMaster);
	orb.compute(originalImage_, keyPointTestImage, descriptTest);
	//std::vector<std::vector<cv::DMatch>> mathes;
	
	cv::FlannBasedMatcher flan;
	cv::BFMatcher bf(cv::NORM_HAMMING, true);
	flan.knnMatch(descriptMaster, descriptTest, mathes, 2);
	std::vector<cv::DMatch> mathesOut;
	for (size_t i{ 0 }; i < mathes.size(); ++i)
	{
		if (mathes[i][0].distance < 0.75 * mathes[i][1].distance)
			mathesOut.push_back(mathes[i][0]);
	}

	for (size_t i{ 0 }; i < mathesOut.size() && i < 9; ++i)
	{
		float bestDistance = mathesOut[i].distance;
		int numberBestDistance = i;
		for (size_t j{ i + 1 }; j < mathesOut.size(); ++j)
		{
			if (mathesOut[j].distance < bestDistance)
			{
				bestDistance = mathesOut[j].distance;
				numberBestDistance = j;
			}
		}
		cv::DMatch bufer;
		bufer = mathesOut[numberBestDistance];
		mathesOut[numberBestDistance] = mathesOut[i];
		mathesOut[i] = bufer;
	}

	std::vector<cv::Point2f> obj;
	cv::Point2f upLeft{ keyPointMasterImage[mathesOut[0].queryIdx].pt }, downRigth{ keyPointMasterImage[mathesOut[0].queryIdx].pt };
	for (size_t i{ 0 }; i < mathesOut.size() && i < 9; ++i)
	{
		keyPoints.push_back(keyPointTestImage[mathesOut[i].trainIdx].pt);
		if (upLeft.x > keyPointMasterImage[mathesOut[i].queryIdx].pt.x)
			upLeft.x = keyPointMasterImage[mathesOut[i].queryIdx].pt.x;
		if (upLeft.y > keyPointMasterImage[mathesOut[i].queryIdx].pt.y)
			upLeft.y = keyPointMasterImage[mathesOut[i].queryIdx].pt.y;
		if (downRigth.x < keyPointMasterImage[mathesOut[i].queryIdx].pt.x)
			downRigth.x = keyPointMasterImage[mathesOut[i].queryIdx].pt.x;
		if (downRigth.y < keyPointMasterImage[mathesOut[i].queryIdx].pt.y)
			downRigth.y = keyPointMasterImage[mathesOut[i].queryIdx].pt.y;
	}

	cv::Mat img3;
	cv::drawMatches(*masterImage, keyPointMasterImage, originalImage_, keyPointTestImage, mathesOut, img3);
	int ysdf{ static_cast<int>(masterImage->cols / 2 - (upLeft.x + (downRigth.x - upLeft.x) / 2)) };
	bais.x = static_cast<int>(masterImage->cols / 2 - (upLeft.x + (downRigth.x - upLeft.x) / 2));
	bais.y = static_cast<int>(masterImage->rows / 2 - (upLeft.y + (downRigth.y - upLeft.y) / 2));
}

ProcessingPositionAdjustment::ProcessingPositionAdjustment()
{
	countorsProcessing_ = new ProcessingCountours();
}

ProcessingPositionAdjustment::ProcessingPositionAdjustment(const ProcessingPositionAdjustment& drop):
	deltaAngel_{drop.deltaAngel_},
	deltsX_{drop.deltsX_},
	deltaY_{drop.deltaY_}
{
	drop.comparrisImage_.copyTo(comparrisImage_);
	drop.masterImage_.copyTo(masterImage_);
	drop.originalImage_.copyTo(originalImage_);
	drop.procesingImage_.copyTo(procesingImage_);
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
	(*inputImage)(*roi).copyTo(procesingImage_);
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
	cv::Rect limitRect{ findLimitRectangel(masterImages, roi) };

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
			for (int i{ 5 }; i < 20; i+=5)
			{
				
				cv::Mat rotateMatrix{ cv::getRotationMatrix2D(cv::Point2f(rotateImage.rows / 2.0, rotateImage.rows / 2.0), i, 1.0) };
				cv::warpAffine(rotateImage, rotateImage, rotateMatrix, rotateImage.size());
				cv::threshold(rotateImage, rotateImage, 0, 255, cv::THRESH_OTSU);
				countorsProcessing_->performProcessing(&originalImage_(searchRoi));
				roi.setRotateAngel(360.0 - i);
				countorsProcessing_->computeComparsion(isSingelThresold, comparsionThreshold, &rotateImage, roi);
			}
		}
	}
	return 0;
}

cv::Mat* ProcessingPositionAdjustment::getProcessingImage()
{
	return &procesingImage_;
}


