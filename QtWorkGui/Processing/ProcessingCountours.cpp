#include "ProcessingCountours.h"

ProcessingCountours::ProcessingCountours() :
    comparrisImage_{cv::Mat()},
    masterImage_{cv::Mat()},
    processingImage_{cv::Mat()},
    masterContours_{},
    masterHiararchy_{},
	threshold_{ 20 }
{
}

ProcessingCountours::ProcessingCountours(const ProcessingCountours& drop):
    comparrisImage_{drop.comparrisImage_ },
    masterImage_{drop.masterImage_ },
    processingImage_{drop.processingImage_ },
    threshold_{drop.threshold_}
{
}

ProcessingCountours::ProcessingCountours(ProcessingCountours&& drop):
    comparrisImage_{ drop.comparrisImage_ },
    masterImage_{ drop.masterImage_ },
    processingImage_{ drop.processingImage_ },
    threshold_{ drop.threshold_ }
{
}

void ProcessingCountours::performProcessing(cv::Mat const* inputImage)
{
    cv::Mat *cannyOut=new cv::Mat();
    inputImage->copyTo(*cannyOut);
    cv::Canny(*cannyOut, *cannyOut, threshold_, threshold_ * 2, 3, false);
    cv::findContours(*cannyOut, masterContours_, masterHiararchy_, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    processingImage_ = cv::Mat(inputImage->size(), CV_8UC1, cv::Scalar(0));
    for (size_t i{ 0 }; i < masterContours_.size(); ++i)
    {
        cv::drawContours(processingImage_, masterContours_, int(i), cv::Scalar(255), 1);
    }
    delete cannyOut;
}

void ProcessingCountours::drawResultImage(cv::Mat& inOutPutImage)
{
    cv::cvtColor(inOutPutImage, inOutPutImage, CV_RGB2GRAY);
    cv::cvtColor(inOutPutImage, inOutPutImage, CV_GRAY2RGB);
    if (comparrisImage_.size().width == 0)
    {
        cv::Mat objectContour(inOutPutImage.size(), inOutPutImage.type(), cv::Scalar(0, 255, 0));
        cv::Mat bufer(processingImage_);
        cv::cvtColor(bufer, bufer, CV_GRAY2BGR);
        cv::bitwise_and(bufer, objectContour, objectContour);
        cv::bitwise_not(bufer, bufer);
        cv::bitwise_and(inOutPutImage, bufer, inOutPutImage);
        cv::bitwise_or(inOutPutImage, objectContour, inOutPutImage);
    }
    else
    {
        cv::Mat mask(comparrisImage_.size(),CV_8UC1);
        cv::cvtColor(comparrisImage_, mask, CV_BGR2GRAY);
        cv::threshold(mask, mask, 1, 255, CV_THRESH_BINARY);
        cv::bitwise_not(mask, mask);
        cv::cvtColor(mask, mask, CV_GRAY2BGR);
        cv::bitwise_and(inOutPutImage, mask, inOutPutImage);
        cv::bitwise_or(inOutPutImage, comparrisImage_, inOutPutImage);
        cv::Mat bufer(inOutPutImage);
    }
}

void ProcessingCountours::setThreshold(std::vector<int> newThreshold)
{
    threshold_ = newThreshold[0];
}

void ProcessingCountours::getThreshold(std::vector<int>& outThreshold)
{
    outThreshold.clear();
    outThreshold.push_back(threshold_);
}

int ProcessingCountours::computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages)
{
    cv::Mat matchedPart(masterImages->size(),CV_8UC1);
    cv::bitwise_and(*masterImages, processingImage_, matchedPart);
    cv::Mat bufer_(processingImage_);
    cv::Mat mismatchedPart_1(masterImages->size(), CV_8UC1);
    cv::bitwise_xor(processingImage_, matchedPart, mismatchedPart_1);
    cv::Mat mismatchedPart_2(masterImages->size(), CV_8UC1);
    cv::bitwise_xor(*masterImages, matchedPart, mismatchedPart_2);
    cv::cvtColor(matchedPart, matchedPart, CV_GRAY2BGR);
    cv::bitwise_and(matchedPart, cv::Mat(masterImages->size(), CV_8UC3, cv::Scalar(0, 255, 0)), matchedPart);
    cv::bitwise_or(mismatchedPart_1, mismatchedPart_2, mismatchedPart_2);
    cv::cvtColor(mismatchedPart_2, mismatchedPart_2, CV_GRAY2BGR);
    cv::bitwise_and(mismatchedPart_2, cv::Mat(masterImages->size(), CV_8UC3, cv::Scalar(0, 0, 255)), mismatchedPart_2);
    comparrisImage_ = cv::Mat(cv::Mat(masterImages->size(), CV_8UC3, cv::Scalar(0, 0, 0)));
    cv::bitwise_or(mismatchedPart_2, matchedPart, comparrisImage_);
    cv::Mat bufer(comparrisImage_);
    return 0;
}

cv::Mat* ProcessingCountours::getProcessingImage()
{
    return &processingImage_;
}

void ProcessingCountours::drawCountours(cv::Mat const* inputImage, std::vector<std::vector<cv::Point>>& contours)
{
    cv::cvtColor(*inputImage, processingImage_, CV_RGB2GRAY);
    cv::cvtColor(processingImage_, processingImage_, CV_GRAY2RGB);
    for (size_t i{ 0 }; i < contours.size(); ++i)
    {
        cv::drawContours(processingImage_, contours, int(i), cv::Scalar(0, 255, 0), 1);
    }
}
