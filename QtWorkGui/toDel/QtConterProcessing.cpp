#include "QtConterProcessing.h"

QtConterProcessing::QtConterProcessing(QObject *parent)
	: QObject(parent),
    threshold(20),
    originalImgWithCounter(cv::Mat(0, 0, CV_8UC3))
{
}

//QtConterProcessing::QtConterProcessing(const QtConterProcessing& drob) :
//    master_contours(drob.master_contours),
//    master_hiararchy(drob.master_hiararchy),
//    threshold(drob.threshold),
//    originalImgWithCounter(drob.originalImgWithCounter)
//{
//}

//QtConterProcessing& QtConterProcessing::operator=(const QtConterProcessing& drob)
//{
//
//    master_contours=drob.master_contours;
//    master_hiararchy=drob.master_hiararchy;
//    threshold=drob.threshold;
//    originalImgWithCounter = drob.originalImgWithCounter;
//    return *this;
//    // TODO: insert return statement here
//}

QtConterProcessing::~QtConterProcessing()
{
}

void QtConterProcessing::setThreshold(int const newThreshold)
{
    threshold = newThreshold;
}

void QtConterProcessing::findContours(cv::Mat const* inputImg, std::vector<std::vector<cv::Point>>& OutContours, std::vector<cv::Vec4i>& OutHiararchy)
{
    cv::Mat cannyOut;
    cv::blur(*inputImg, cannyOut, cv::Size(4, 4));
    cv::medianBlur(cannyOut, cannyOut, 3);
    cv::Mat coreMorfologis(cv::Size(5, 5), CV_8U);
    cv::morphologyEx(cannyOut, cannyOut, cv::MORPH_ERODE, coreMorfologis);
    cv::Canny(cannyOut, cannyOut, threshold, threshold * 2, 3, false);
    cv::findContours(cannyOut, OutContours, OutHiararchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    drawContours(inputImg, cv::Scalar(0, 255, 0));
}

void QtConterProcessing::findAndSetMasterContours(cv::Mat const* inputImg)
{
    cv::Mat cannyOut;
    cv::blur(*inputImg, cannyOut, cv::Size(4, 4));
    cv::medianBlur(cannyOut, cannyOut, 3);
    cv::Mat coreMorfologis(cv::Size(5, 5), CV_8U);
    cv::morphologyEx(cannyOut, cannyOut, cv::MORPH_ERODE, coreMorfologis);
    cv::Canny(*inputImg, cannyOut, threshold, threshold * 2, 3, false);
    cv::findContours(cannyOut, master_contours, master_hiararchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    drawContours(inputImg, cv::Scalar(0, 255, 0));
}

void QtConterProcessing::setMasterCounter(std::vector<std::vector<cv::Point>> const* inContours, std::vector<cv::Vec4i> const* inHiararchy)
{
    master_contours = *inContours;
    master_hiararchy = *inHiararchy;
}

int QtConterProcessing::setMasterCounter(cv::Rect rectROI)
{
    if ((rectROI.x + rectROI.width) > originalImgWithCounter.cols || (rectROI.y + rectROI.height) > originalImgWithCounter.rows)
    {
        return 0;
    }
    else
    {
        cv::findContours(originalImgWithCounter, master_contours, master_hiararchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    }
    return 0;
}

void QtConterProcessing::setMasterCounter(cv::Mat imgROI)
{
    cv::Mat cannyOut;
    cv::blur(imgROI, cannyOut, cv::Size(4, 4));
    cv::medianBlur(cannyOut, cannyOut, 3);
    cv::Mat coreMorfologis(cv::Size(5, 5), CV_8U);
    cv::morphologyEx(cannyOut, cannyOut, cv::MORPH_ERODE, coreMorfologis);
    cv::Canny(cannyOut, cannyOut, threshold, threshold * 2, 3, false);
    cv::findContours(cannyOut, master_contours, master_hiararchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
}

void QtConterProcessing::changeContours(cv::Size const originalImageSize, std::vector<std::vector<cv::Point>>& inOutContours, std::vector<cv::Vec4i>& inOutHiararchy, std::vector<cv::Point> const maskPoint)
{
    cv::Mat bufer{ cv::Mat::zeros(originalImageSize, CV_8U) };
    for (size_t i{ 0 }; i < inOutContours.size(); ++i)
    {
        cv::drawContours(bufer, inOutContours, int(i), cv::Scalar(255, 255, 255));
    }
    for (size_t i{ 0 }; i < maskPoint.size(); ++i)
    {
        bufer.at<uchar>(cv::Point(maskPoint[int(i)])) = 0;
    }
    cv::findContours(bufer, inOutContours, inOutHiararchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
}

void QtConterProcessing::getMasterContours(std::vector<std::vector<cv::Point>>& outContours, std::vector<cv::Vec4i>& outHiararchy)
{
    outContours = master_contours;
    outHiararchy = master_hiararchy;
}

void QtConterProcessing::setMasterContours(std::vector<std::vector<cv::Point>> const* inContours, std::vector<cv::Vec4i> const* inHiararchy)
{
    master_contours = *inContours;
    master_hiararchy = *inHiararchy;
}

void QtConterProcessing::drawContours(cv::Mat const* inputImg, cv::Scalar color)
{
    //cv::Mat outImg;
    //inputImg->copyTo(outImg);
    cv::cvtColor(*inputImg, originalImgWithCounter, CV_GRAY2RGB);
    //if (mask == nullptr)
   // {
    for (size_t i{ 0 }; i < master_contours.size(); ++i)
    {
        cv::drawContours(originalImgWithCounter, master_contours, int(i), color);
    }
    /* cv::imshow("out", originalImgWithCounter);
     cv::waitKey(0);*/
     // }
      /*else
      {
          std::thread t1(draw,&outImg,master_contours);
          cv::Mat backGround;
          cv::bitwise_and(*inputImg, *mask, backGround);
          cv::bitwise_not(*mask, *mask);
          t1.join();
          cv::bitwise_and(outImg, *mask, outImg);
          cv::bitwise_or(outImg, backGround, outImg);
      }*/
      // return outImg;
}

cv::Mat QtConterProcessing::getDrawContours(cv::Rect ROI)
{
    cv::Mat outImg(originalImgWithCounter, ROI);
    return outImg;
}