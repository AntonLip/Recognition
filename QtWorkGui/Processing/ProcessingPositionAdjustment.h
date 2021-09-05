#pragma once
#include "IProcessing.h"
#include "ProcessingCountours.h"

class ProcessingPositionAdjustment :
    public IProcessing
{
    cv::Mat comparrisImage_{};
    cv::Mat masterImage_{};
    cv::Mat processingImage_{};

    ProcessingCountours *countorsProcessing_{nullptr};
    int deltaAngel_{0};
    int deltsX_{0};
    int deltaY_{0};
public:
    ProcessingPositionAdjustment();
    ProcessingPositionAdjustment(const ProcessingPositionAdjustment& drop);
    void performProcessing(cv::Mat const* inputImage) override;
    void drawResultImage(cv::Mat& inOutPutImage) override;
    void setThreshold(std::vector<int> newThreshold) override;
    void getThreshold(std::vector<int>& outThreshold) override;
    int computeComparsion(bool const isSingelThresold, std::vector<int>& const comparsionThreshold, cv::Mat* const masterImages, QtRotateRect roi) override;
    cv::Mat* getProcessingImage() override;
};

