#include "ProcessingCountours.h"

ProcessingCountours::ProcessingCountours() :
	masterContours_{ },
	masterHiararchy_{ },
	threshold_{ 20 }
{
}

ProcessingCountours::ProcessingCountours(const ProcessingCountours& drop, bool copyCounter):
    masterContours_{ },
    masterHiararchy_{ },
    threshold_{drop.threshold_}
{
    if (copyCounter)
    {
        masterContours_.assign(drop.masterContours_.begin(), drop.masterContours_.end());
        masterHiararchy_.assign(drop.masterHiararchy_.begin(), drop.masterHiararchy_.end());
    }
    //masterContours_ = drop.masterContours_;
    //masterHiararchy_ = drop.masterHiararchy_;
    int a;
    a = 12;
}

ProcessingCountours::ProcessingCountours(ProcessingCountours&& drop, bool copyCounter):
    masterContours_ {  },
    masterHiararchy_{  },
    threshold_{ drop.threshold_ }
{
    if (copyCounter)
    {
        masterContours_.assign(drop.masterContours_.begin(), drop.masterContours_.end());
        masterHiararchy_.assign(drop.masterHiararchy_.begin(), drop.masterHiararchy_.end());
    }
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
    cv::findContours(cannyOut, masterContours_, masterHiararchy_, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    int a;
    a = 14;

    //drawContours(inputImg, cv::Scalar(0, 255, 0));
}

void ProcessingCountours::drawProcessing(cv::Mat& inOutPutImage)
{
    cv::cvtColor(inOutPutImage, inOutPutImage, CV_RGB2GRAY);
    cv::cvtColor(inOutPutImage, inOutPutImage, CV_GRAY2RGB);
    for (size_t i{ 0 }; i < masterContours_.size(); ++i)
    {
        cv::drawContours(inOutPutImage, masterContours_, int(i),cv::Scalar(0,255,0) , 2);
    }
}
