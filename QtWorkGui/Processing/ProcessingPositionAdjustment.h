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
    float minRotateAngel_{ 0.0 }, maxRotateAngel_{ 0.0 };
    float newRotateAngel_{ 0.0 };
    cv::Point newCenter_{ 0,0 };
    int rotateRange_{ 0 };
    cv::Rect findLimitRectangel(cv::Mat* const masterImage, QtRotateRect const roi);
    void findKeyPoints(cv::Mat* const masterImage, std::vector<cv::DMatch>& maychOut);
    void findNewCenterPointAndRotateAngel(QtRotateRect roi, cv::Mat* masterImage, cv::Mat &testImage, cv::Rect limitRect);
    void setLimitsRotateAngel(float const rotateAngelOriginalRoi);
    bool limitRectangelIsInverted(std::vector<int> const& pointsContainsInLimitRectangel, std::vector<cv::DMatch>const& matchIn, QPoint const& originalCenter);
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
    void setRotateRange(int const rotateRange = 20);
};

