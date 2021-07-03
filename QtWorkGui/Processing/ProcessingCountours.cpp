#include "ProcessingCountours.h"

ProcessingCountours::ProcessingCountours() :
	masterContours_{ },
	masterHiararchy_{ },
	threshold_{ 20 }
{
}

ProcessingCountours::ProcessingCountours(const ProcessingCountours& drop):
    masterContours_{ },
    masterHiararchy_{ },
    threshold_{drop.threshold_}
{
    masterContours_.assign(drop.masterContours_.begin(), drop.masterContours_.end());
    masterHiararchy_.assign(drop.masterHiararchy_.begin(), drop.masterHiararchy_.end());
}

void ProcessingCountours::performProcessing(cv::Mat const* inputImage)
{
    cv::Mat cannyOut;
    //cv::blur(*inputImage, cannyOut, cv::Size(4, 4));
    //cv::medianBlur(cannyOut, cannyOut, 3);
    //cv::Mat coreMorfologis(cv::Size(5, 5), CV_8U);
    //cv::morphologyEx(cannyOut, cannyOut, cv::MORPH_ERODE, coreMorfologis);
    cv::Canny(cannyOut, cannyOut, threshold_, threshold_ * 2, 3, false);
    cv::findContours(cannyOut, masterContours_, masterHiararchy_, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    //drawContours(inputImg, cv::Scalar(0, 255, 0));
}

void ProcessingCountours::drawProcessing(cv::Mat& inOutPutImage)
{
    cv::cvtColor(inOutPutImage, inOutPutImage, CV_RGB2GRAY);
    cv::cvtColor(inOutPutImage, inOutPutImage, CV_GRAY2RGB);
    for (size_t i{ 0 }; i < masterContours_.size(); ++i)
    {
        cv::drawContours(inOutPutImage, masterContours_, int(i),cv::Scalar(0,1,0) , 2);
    }
}
