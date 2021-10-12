#include "ProcessingPositionAdjustment.h"

cv::Rect ProcessingPositionAdjustment::findLimitRectangel(cv::Mat* const masterImage, QtRotateRect roi)
{

	std::vector<cv::DMatch> match;
	findKeyPoints(masterImage, match);
	
	cv::Point2i upLeftToFindBestArea{ keyPointTestImage[match[0].trainIdx].pt }, downRigthToFindBestArea{ keyPointTestImage[match[0].trainIdx].pt };
	for (size_t i{ 1 }; i < match.size() ; ++i)
	{
		if (upLeftToFindBestArea.x > keyPointTestImage[match[i].trainIdx].pt.x)
			upLeftToFindBestArea.x = keyPointTestImage[match[i].trainIdx].pt.x;
		if (upLeftToFindBestArea.y > keyPointTestImage[match[i].trainIdx].pt.y)
			upLeftToFindBestArea.y = keyPointTestImage[match[i].trainIdx].pt.y;
		if (downRigthToFindBestArea.x < keyPointTestImage[match[i].trainIdx].pt.x)
			downRigthToFindBestArea.x = keyPointTestImage[match[i].trainIdx].pt.x;
		if (downRigthToFindBestArea.y < keyPointTestImage[match[i].trainIdx].pt.y)
			downRigthToFindBestArea.y = keyPointTestImage[match[i].trainIdx].pt.y;
	}
	upLeftToFindBestArea.x -= masterImage->cols / 2;
	upLeftToFindBestArea.y -= masterImage->rows / 2;
	downRigthToFindBestArea.x += masterImage->cols / 2;
	downRigthToFindBestArea.y += masterImage->rows / 2;

	size_t bestQuantityPointInRoi{0};
	cv::Point upLeftBestArea{ }, downRigthBestArea{ };
	cv::Rect limitRect{ cv::Point2i(upLeftToFindBestArea), cv::Size2i(masterImage->cols,masterImage->rows) };
	for (int i{ upLeftToFindBestArea.y }; i + limitRect.height <= downRigthToFindBestArea.y; ++i)
	{
		limitRect.y = i;
		for (int j{ upLeftToFindBestArea.x }; j + limitRect.width <= downRigthToFindBestArea.x; ++j)
		{
			limitRect.x = j;
			size_t quantityPointInRoi{0};
			for (size_t p{ 0 }; p < match.size(); ++p)
			{
				if (limitRect.contains(keyPointTestImage[match[p].trainIdx].pt))
					++quantityPointInRoi;
			}
			if (quantityPointInRoi > bestQuantityPointInRoi)
			{
				bestQuantityPointInRoi = quantityPointInRoi;
				upLeftBestArea = cv::Point(j, i);
				downRigthBestArea = cv::Point(j + limitRect.width, i + limitRect.height);
			}
			else if (quantityPointInRoi == bestQuantityPointInRoi)
			{
				if (upLeftBestArea.x > j)
					upLeftBestArea.x =j;
				if (upLeftBestArea.y > i)
					upLeftBestArea.y = i;
				if (downRigthBestArea.x < j + limitRect.width)
					downRigthBestArea.x = j + limitRect.width;
				if (downRigthBestArea.y < i + limitRect.height)
					downRigthBestArea.y = i + limitRect.height;
			}
		}
	}
	std::vector<int> numberPointsContainsInBestArea{};
	for (int p{ 0 }; p < match.size(); ++p)
	{
		if (cv::Rect(upLeftBestArea, downRigthBestArea).contains(keyPointTestImage[match[p].trainIdx].pt))
			numberPointsContainsInBestArea.push_back(p);
	}
	cv::Point upLeftBaisRect{ keyPointMasterImage[match[numberPointsContainsInBestArea[0]].queryIdx].pt }, downRigthBaisRect{ keyPointMasterImage[match[numberPointsContainsInBestArea[0]].queryIdx].pt };
	cv::Point upLeftSearchRect{ keyPointTestImage[match[numberPointsContainsInBestArea[0]].trainIdx].pt }, downRigthSearchRect{ keyPointTestImage[match[numberPointsContainsInBestArea[0]].trainIdx].pt };
	for (size_t i{ 1 }; i < numberPointsContainsInBestArea.size(); ++i)
	{
		if (upLeftBaisRect.x > keyPointMasterImage[match[numberPointsContainsInBestArea[i]].queryIdx].pt.x)
			upLeftBaisRect.x = keyPointMasterImage[match[numberPointsContainsInBestArea[i]].queryIdx].pt.x;
		if (upLeftBaisRect.y > keyPointMasterImage[match[numberPointsContainsInBestArea[i]].queryIdx].pt.y)
			upLeftBaisRect.y = keyPointMasterImage[match[numberPointsContainsInBestArea[i]].queryIdx].pt.y;
		if (downRigthBaisRect.x < keyPointMasterImage[match[numberPointsContainsInBestArea[i]].queryIdx].pt.x)
			downRigthBaisRect.x = keyPointMasterImage[match[numberPointsContainsInBestArea[i]].queryIdx].pt.x;
		if (downRigthBaisRect.y < keyPointMasterImage[match[numberPointsContainsInBestArea[i]].queryIdx].pt.y)
			downRigthBaisRect.y = keyPointMasterImage[match[numberPointsContainsInBestArea[i]].queryIdx].pt.y;

		if (upLeftSearchRect.x > keyPointTestImage[match[numberPointsContainsInBestArea[i]].trainIdx].pt.x)
			upLeftSearchRect.x = keyPointTestImage[match[numberPointsContainsInBestArea[i]].trainIdx].pt.x;
		if (upLeftSearchRect.y > keyPointTestImage[match[numberPointsContainsInBestArea[i]].trainIdx].pt.y)
			upLeftSearchRect.y = keyPointTestImage[match[numberPointsContainsInBestArea[i]].trainIdx].pt.y;
		if (downRigthSearchRect.x < keyPointTestImage[match[numberPointsContainsInBestArea[i]].trainIdx].pt.x)
			downRigthSearchRect.x = keyPointTestImage[match[numberPointsContainsInBestArea[i]].trainIdx].pt.x;
		if (downRigthSearchRect.y < keyPointTestImage[match[numberPointsContainsInBestArea[i]].trainIdx].pt.y)
			downRigthSearchRect.y = keyPointTestImage[match[numberPointsContainsInBestArea[i]].trainIdx].pt.y;
	}
	cv::Point bais{};
	bais.x = static_cast<int>(masterImage->cols / 2 - (upLeftBaisRect.x + (downRigthBaisRect.x - upLeftBaisRect.x) / 2));
	bais.y = static_cast<int>(masterImage->rows / 2 - (upLeftBaisRect.y + (downRigthBaisRect.y - upLeftBaisRect.y) / 2));
	
	if (upLeftBestArea.y < 0)
		upLeftBestArea.y = 0;
	if (upLeftBestArea.x < 0)
		upLeftBestArea.x = 0;

	/*upLeftBestArea.x += bais.x;
	upLeftBestArea.y += bais.y;
	downRigthBestArea.x += bais.x;
	downRigthBestArea.y += bais.y;*/

	int limitSide{ masterImage->cols };
	if (masterImage->cols < masterImage->rows)
		limitSide = masterImage->rows;
	upLeftSearchRect.x = upLeftSearchRect.x + (downRigthSearchRect.x - upLeftSearchRect.x) / 2 - limitSide/8;
	upLeftSearchRect.y = upLeftSearchRect.y + (downRigthSearchRect.y - upLeftSearchRect.y) / 2 - limitSide/8;
	return cv::Rect(upLeftSearchRect.x , upLeftSearchRect.y , limitSide/4, limitSide/4);
}

void ProcessingPositionAdjustment::findKeyPoints(cv::Mat* const masterImage, std::vector<cv::DMatch>& mathesOut)
{
	cv::SIFT orb;
	orb.detect(*masterImage, keyPointMasterImage);
	orb.detect(originalImage_, keyPointTestImage);
	cv::Mat descriptMaster, descriptTest;
	orb.compute(*masterImage, keyPointMasterImage, descriptMaster);
	orb.compute(originalImage_, keyPointTestImage, descriptTest);
	
	cv::FlannBasedMatcher flan;
	cv::BFMatcher bf(cv::NORM_HAMMING, true);
	flan.knnMatch(descriptMaster, descriptTest, mathes, 2);
	//std::vector<cv::DMatch> mathesOut;
	for (size_t i{ 0 }; i < mathes.size(); ++i)
	{
		if (mathes[i][0].distance < 0.75 * mathes[i][1].distance)
			mathesOut.push_back(mathes[i][0]);
	}

	for (size_t i{ 0 }; i < mathesOut.size() ; ++i)
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


	cv::Mat img3;//delet!!
	cv::drawMatches(*masterImage, keyPointMasterImage, originalImage_, keyPointTestImage, mathesOut, img3);//delet!!!!!
}

void ProcessingPositionAdjustment::findNewCenterPointAndRotateAngel(QtRotateRect roi, cv::Mat* masterImage, cv::Mat &testImage, cv::Rect limitRect)
{
	float best{ 0.0 };
	for (int i{ -20 }; i < 20; i += 2)
	{
		if (i > 0)
			roi.setRotateAngel(360.0 - i);
		else
			roi.setRotateAngel(-i);

		cv::Rect searchRoi{ 0, 0, roi.getMax_X() - roi.getMin_X(), roi.getMax_Y() - roi.getMin_Y() };
		cv::Mat rotateImage{ *masterImage };
		cv::Mat mask{ cv::Size(masterImage->cols, masterImage->rows), CV_8UC1, cv::Scalar{255} };
		int topAndBottonBorder{ 0 };
		if (searchRoi.height > roi.height())
			topAndBottonBorder = static_cast<int>(searchRoi.height - roi.height()) / 2;
		int leftAndRigthBorder{ 0 };
		if (searchRoi.width > roi.width())
			leftAndRigthBorder = static_cast<int>(searchRoi.width - roi.width()) / 2;

		cv::copyMakeBorder(rotateImage, rotateImage, topAndBottonBorder, topAndBottonBorder, leftAndRigthBorder, leftAndRigthBorder, cv::BORDER_CONSTANT, cv::Scalar(0));
		cv::copyMakeBorder(mask, mask, topAndBottonBorder, topAndBottonBorder, leftAndRigthBorder, leftAndRigthBorder, cv::BORDER_CONSTANT, cv::Scalar(0));
		cv::Mat rotateMatrix{ cv::getRotationMatrix2D(cv::Point2f(rotateImage.cols / 2.0, rotateImage.rows / 2.0), i, 1.0) };
		cv::warpAffine(rotateImage, rotateImage, rotateMatrix, rotateImage.size());
		cv::warpAffine(mask, mask, rotateMatrix, rotateImage.size());
		int topAndBottonRetreat{ 0 };
		if (topAndBottonBorder == 0)
			topAndBottonRetreat = (rotateImage.rows - (roi.getMax_Y() - roi.getMin_Y())) / 2;
		int leftAndRigthRetreat{ 0 };
		if (leftAndRigthBorder == 0)
			leftAndRigthRetreat = (rotateImage.cols - (roi.getMax_X() - roi.getMin_X())) / 2;
		rotateImage = rotateImage(cv::Rect(leftAndRigthRetreat, topAndBottonRetreat, rotateImage.cols - leftAndRigthRetreat * 2, rotateImage.rows - topAndBottonRetreat * 2));
		mask = mask(cv::Rect(leftAndRigthRetreat, topAndBottonRetreat, mask.cols - leftAndRigthRetreat * 2, mask.rows - topAndBottonRetreat * 2));
		if (rotateImage.cols == 0)
		{
			int sdf;
			sdf = 0;
		}
		countorsProcessing_->performProcessing(&rotateImage);
		rotateImage = *countorsProcessing_->getProcessingImage();
		cv::bitwise_and(rotateImage, mask, rotateImage);
		cv::threshold(rotateImage, rotateImage, 254, 255, cv::THRESH_BINARY);


		for (int r{ limitRect.y }; r + searchRoi.height * 0.5 < testImage.rows && r < limitRect.y + limitRect.height; r += 1)
		{
			searchRoi.height = rotateImage.rows;
			searchRoi.y = r - searchRoi.height / 2;
			if (searchRoi.y < 0)
			{
				searchRoi.y = 0;
				if (searchRoi.height > testImage.rows)
					break;
				//searchRoi.height = originalImage_.rows;
			}
			for (int c{ limitRect.x }; c + searchRoi.width * 0.5 < testImage.cols && c < limitRect.x + limitRect.width; c += 1)
			{
				searchRoi.width = rotateImage.cols;
				searchRoi.x = c - searchRoi.width / 2;
				if (searchRoi.x < 0)
				{
					searchRoi.x = 0;
					if (searchRoi.width > testImage.cols)
						break;
					//searchRoi.width = originalImage_.cols;
				}
				if (searchRoi.width == 0)
				{
					int sdf;
					sdf = 0;
				}
				countorsProcessing_->performProcessing(&testImage(searchRoi));
				//cv::Mat qwe{ testImage(searchRoi) };//del!!!!!!
				std::vector<int> q{};
				float bufBest{ countorsProcessing_->computeComparsion(true, q, &rotateImage, roi) };
				if (bufBest > best)
				{
					//X = searchRoi.x * scaled;
					//Y = searchRoi.y * scaled;
					newCenter_.x = searchRoi.x + (searchRoi.width / 2);
					newCenter_.y = searchRoi.y + (searchRoi.height / 2);
					newRotateAngel_ = roi.getRotateAngel();
					best = bufBest;
				}
			}
		}
	}
}

ProcessingPositionAdjustment::ProcessingPositionAdjustment()
{
	countorsProcessing_ = new ProcessingCountours();
}

ProcessingPositionAdjustment::ProcessingPositionAdjustment(const ProcessingPositionAdjustment& drop):
	newCenter_{drop.newCenter_},
	newRotateAngel_{ drop.newRotateAngel_ }
{
	drop.comparrisImage_.copyTo(comparrisImage_);
	drop.masterImage_.copyTo(masterImage_);
	drop.originalImage_.copyTo(originalImage_);
	drop.procesingImage_.copyTo(procesingImage_);
	if (drop.countorsProcessing_ != nullptr)
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

float ProcessingPositionAdjustment::computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages, QtRotateRect roi)
{
	
	cv::Rect limitRect{ findLimitRectangel(masterImages, roi) };
	float scaled{1.0};
	if (limitRect.width > 20)
	{
		scaled = limitRect.width / 20;
	}

	limitRect.x /= scaled;
	limitRect.y /= scaled;
	limitRect.width /= scaled;
	limitRect.height /= scaled;
	QtRotateRect roiScaled{roi};
	roiScaled.setWidth(roi.width() / scaled);
	roiScaled.setHeight(roi.height() / scaled);
	cv::Mat scaledImage{};
	//cv::medianBlur(*masterImages, scaledImage, 3);
	cv::resize(*masterImages, scaledImage, cv::Size(masterImages->size().width / scaled, masterImages->size().height / scaled));
	cv::Mat testImage{};
	//cv::medianBlur(originalImage_, testImage, 3);
	cv::resize(originalImage_, testImage, cv::Size(originalImage_.size().width / scaled, originalImage_.size().height / scaled));

	findNewCenterPointAndRotateAngel(roiScaled, &scaledImage, testImage, limitRect);

	/*limitRect.width = 30;
	limitRect.height = 30;
	limitRect.x = newCenter_.x * (scaled / 2) - 15;
	limitRect.y = newCenter_.y * (scaled / 2) - 15;*/
	
	
	/*roiScaled = roi;
	roiScaled.setWidth(roi.width() / (scaled / 2));
	roiScaled.setHeight(roi.height() / (scaled / 2));
	cv::resize(*masterImages, scaledImage, cv::Size(masterImages->size().width / (scaled / 2), masterImages->size().height / (scaled / 2)));
	cv::resize(originalImage_, testImage, cv::Size(originalImage_.size().width / (scaled / 2), originalImage_.size().height / (scaled / 2)));

	findNewCenterPointAndRotateAngel(roiScaled, &scaledImage, testImage, limitRect);*/


	limitRect.x = newCenter_.x * (scaled ) - 2;
	limitRect.y = newCenter_.y * (scaled ) - 2;
	limitRect.width = 4;
	limitRect.height = 4;

	findNewCenterPointAndRotateAngel(roi, masterImages, originalImage_, limitRect);

	return 0;
}

cv::Mat* ProcessingPositionAdjustment::getProcessingImage()
{
	return &procesingImage_;
}

cv::Point ProcessingPositionAdjustment::getNewCenter() const
{
	return newCenter_;
}

float ProcessingPositionAdjustment::getNewRotateAngel() const
{
	return newRotateAngel_;
}


