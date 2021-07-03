#include "CountoursProcessing.h"

CountoursProcessing::CountoursProcessing() :
    threshold(20),
    originalImgWithCounter(cv::Mat(0, 0, CV_8UC3))
{
    std::cout << "constr"<<std::endl;
}

CountoursProcessing::CountoursProcessing(const CountoursProcessing& drop):
    threshold(drop.threshold),
    originalImgWithCounter(drop.originalImgWithCounter)
{
    master_contours.assign(drop.master_contours.begin(), drop.master_contours.end());
    master_hiararchy.assign(drop.master_hiararchy.begin(), drop.master_hiararchy.end());
}

CountoursProcessing::~CountoursProcessing()
{
    std::cout << "desConter" << std::endl;
}

//CountoursProcessing::CountoursProcessing(const CountoursProcessing& drop):
//    master_contours(drop.master_contours),
//    master_hiararchy(drop.master_hiararchy),
//    threshold(drop.threshold),
//    originalImgWithCounter(drop.originalImgWithCounter)
//{
//    std::cout << "constrCopy" << std::endl;
//}

void CountoursProcessing::setThreshold(int const newThreshold)
{
    threshold = newThreshold;
}

void CountoursProcessing::findContours(cv::Mat const* inputImg, std::vector<std::vector<cv::Point>>& OutContours, std::vector<cv::Vec4i>& OutHiararchy)
{ 
    cv::Mat cannyOut;
    cv::blur(*inputImg, cannyOut, cv::Size(4, 4));
    cv::medianBlur(cannyOut, cannyOut, 3);
    cv::Mat coreMorfologis(cv::Size(5, 5), CV_8U);
    cv::morphologyEx(cannyOut, cannyOut, cv::MORPH_ERODE, coreMorfologis);
    cv::Canny(cannyOut, cannyOut, threshold, threshold*2, 3, false);
    cv::findContours(cannyOut, OutContours, OutHiararchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    drawContours(inputImg, cv::Scalar(0, 255, 0));
}

void CountoursProcessing::findAndSetMasterContours(cv::Mat const* inputImg)
{
    cv::Mat cannyOut;
    cv::blur(*inputImg, cannyOut, cv::Size(4, 4));
    cv::medianBlur(cannyOut, cannyOut, 3);
    cv::Mat coreMorfologis(cv::Size(5, 5), CV_8U);
    cv::morphologyEx(cannyOut, cannyOut, cv::MORPH_ERODE, coreMorfologis);
    cv::Canny(cannyOut, cannyOut, threshold, threshold * 2, 3, false);
    cv::findContours(cannyOut, master_contours, master_hiararchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    drawContours(inputImg, cv::Scalar(0, 255, 0));
}

void CountoursProcessing::setMasterCounter(std::vector<std::vector<cv::Point>> const* inContours, std::vector<cv::Vec4i> const* inHiararchy)
{
    master_contours = *inContours;
    master_hiararchy = *inHiararchy;
}

int CountoursProcessing::setMasterCounter(cv::Rect rectROI)
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

void CountoursProcessing::setMasterCounter(cv::Mat imgROI)
{
    cv::Mat cannyOut;
    cv::blur(imgROI, cannyOut, cv::Size(4, 4));
    cv::medianBlur(cannyOut, cannyOut, 3);
    cv::Mat coreMorfologis(cv::Size(5, 5), CV_8U);
    cv::morphologyEx(cannyOut, cannyOut, cv::MORPH_ERODE, coreMorfologis);
    cv::Canny(cannyOut, cannyOut, threshold, threshold * 2, 3, false);
    cv::findContours(cannyOut, master_contours, master_hiararchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
}

void CountoursProcessing::changeContours(cv::Size const originalImageSize, std::vector<std::vector<cv::Point>>& inOutContours, std::vector<cv::Vec4i>& inOutHiararchy, std::vector<cv::Point> const maskPoint)
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

void CountoursProcessing::getMasterContours(std::vector<std::vector<cv::Point>>& outContours, std::vector<cv::Vec4i>& outHiararchy)
{
    outContours = master_contours;
    outHiararchy = master_hiararchy;
}

void CountoursProcessing::setMasterContours(std::vector<std::vector<cv::Point>> const* inContours, std::vector<cv::Vec4i> const* inHiararchy)
{
    master_contours = *inContours;
    master_hiararchy = *inHiararchy;
}

void CountoursProcessing::drawContours(cv::Mat const *inputImg, cv::Scalar color)
{
    if (inputImg->type() == CV_8U)
        cv::cvtColor(*inputImg, originalImgWithCounter, CV_GRAY2RGB);
    else
    {
        cv::cvtColor(*inputImg, originalImgWithCounter, CV_RGB2GRAY);
        cv::cvtColor(originalImgWithCounter, originalImgWithCounter, CV_GRAY2RGB);
    }
    for (size_t i{ 0 }; i < master_contours.size(); ++i)
    {
        cv::drawContours(originalImgWithCounter, master_contours, int(i), color,2);
    }
}

cv::Mat CountoursProcessing::getDrawContours(cv::Rect ROI)
{
    cv::Mat outImg(originalImgWithCounter,ROI);
    return outImg;
}

void draw(cv::Mat* inOutputImg,std::vector<std::vector<cv::Point>> counters)
{ 
    std::cout << "1:" << std::this_thread::get_id() << std::endl;
    auto start = std::chrono::system_clock::now();
    for (size_t i{ 0 }; i < counters.size(); ++i)
    {
        cv::drawContours(*inOutputImg, counters, int(i), cv::Scalar(0, 255, 0));
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elasped = end - start;
    std::cout << "time draw cont: " << elasped.count() << std::endl;
}
