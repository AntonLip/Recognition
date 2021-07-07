#include "ProcessingCountours.h"

ProcessingCountours::ProcessingCountours() :
    resultImage_{cv::Mat()},
	threshold_{ 20 }
{
}

ProcessingCountours::ProcessingCountours(const ProcessingCountours& drop):
    resultImage_{drop.resultImage_ },
    threshold_{drop.threshold_}
{

    //masterContours_ = drop.masterContours_;
    //masterHiararchy_ = drop.masterHiararchy_;

}

ProcessingCountours::ProcessingCountours(ProcessingCountours&& drop):
    resultImage_{ drop.resultImage_ },
    threshold_{ drop.threshold_ }
{

}

void ProcessingCountours::performProcessing(cv::Mat const* inputImage)
{
    cv::Mat cannyOut;
    //cv::blur(*inputImage, cannyOut, cv::Size(4, 4));
    //cv::medianBlur(cannyOut, cannyOut, 3);
    //cv::Mat coreMorfologis(cv::Size(5, 5), CV_8U);
    //cv::morphologyEx(cannyOut, cannyOut, cv::MORPH_ERODE, coreMorfologis);
    cv::Canny(*inputImage, cannyOut, threshold_, threshold_ * 2, 3, false);
    //masterContours_.clear();
    //masterContours_.resize(0);
    //masterHiararchy_.clear();
    //masterHiararchy_.resize(0);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hiararchy;
    cv::findContours(cannyOut, contours, hiararchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    drawCountours(inputImage, contours);
    /*for (size_t i{ 0 }; i < contours.size(); ++i)
    {
        cv::drawContours(resultImage_, resultImage_, int(i), cv::Scalar(0, 255, 0), 2);
    }*/
}

void ProcessingCountours::drawProcessing(cv::Mat& inOutPutImage)
{
    inOutPutImage = resultImage_;
}

void ProcessingCountours::setThreshold(std::vector<int> newThreshold)
{
    threshold_ = newThreshold[0];
}

void ProcessingCountours::drawCountours(cv::Mat const* inputImage, std::vector<std::vector<cv::Point>>& contours)
{
    cv::cvtColor(*inputImage, resultImage_, CV_RGB2GRAY);
    cv::cvtColor(resultImage_, resultImage_, CV_GRAY2RGB);
    for (size_t i{ 0 }; i < contours.size(); ++i)
    {
        cv::drawContours(resultImage_, contours, int(i), cv::Scalar(0, 255, 0), 1);
    }
}
