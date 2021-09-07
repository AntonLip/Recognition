#pragma once
#include "IProcessing.h"
#include "ProcessingCountours.h"
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>

class ProcessingPositionAdjustment :
    public IProcessing
{
    cv::Mat comparrisImage_{};
    cv::Mat masterImage_{};
    cv::Mat originalImage_{};
    cv::Mat procesingImage_{};

    ProcessingCountours *countorsProcessing_{nullptr};
    std::vector<std::vector<cv::DMatch>> mathes;
    //cv::Mat descriptMaster, descriptTest;
    std::vector<cv::KeyPoint> keyPointMasterImage, keyPointTestImage;
    int deltaAngel_{0};
    int deltsX_{0};
    int deltaY_{0};
    cv::Rect findLimitRectangel(cv::Mat* const masterImage, QtRotateRect const roi);
    void findKeyPoints(cv::Mat* const masterImage, std::vector<cv::Point2f> &keyPoints);
public:
    ProcessingPositionAdjustment();
    ProcessingPositionAdjustment(const ProcessingPositionAdjustment& drop);
    void performProcessing(cv::Mat const* inputImage) override;
    void performProcessing(cv::Mat const* inputImage, cv::Rect const *roi);
    void drawResultImage(cv::Mat& inOutPutImage) override;
    void setThreshold(std::vector<int> newThreshold) override;
    void getThreshold(std::vector<int>& outThreshold) override;
    int computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages, QtRotateRect roi) override;
    cv::Mat* getProcessingImage() override;
};

