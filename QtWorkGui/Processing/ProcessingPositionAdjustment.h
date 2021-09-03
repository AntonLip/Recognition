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
};

