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
    std::vector<std::vector<cv::DMatch>> mathes{};
    std::vector<cv::KeyPoint> keyPointMasterImage{}, keyPointTestImage{};
    float newRotateAngel_{ 0.0 };
    cv::Point newCenter_{ 0,0 };
    cv::Rect findLimitRectangel(cv::Mat* const masterImage, QtRotateRect const roi);
    void findKeyPoints(cv::Mat* const masterImage, std::vector<cv::DMatch>& maychOut, cv::Point2i &bais);
    void findNewCenterPointAndRotateAngel(QtRotateRect roi, cv::Mat* masterImage, cv::Mat &testImage, cv::Rect limitRect);
public:
    ProcessingPositionAdjustment();
    ProcessingPositionAdjustment(const ProcessingPositionAdjustment& drop);
    void performProcessing(cv::Mat const* inputImage) override;
    void performProcessing(cv::Mat const* inputImage, cv::Rect const *roi);
    void drawResultImage(cv::Mat& inOutPutImage) override;
    void setThreshold(std::vector<int> newThreshold) override;
    void getThreshold(std::vector<int>& outThreshold) override;
    float computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages, QtRotateRect roi) override;
    cv::Mat* getProcessingImage() override;
    cv::Point getNewCenter() const;
    float getNewRotateAngel() const;
};

