#pragma once
#include "Processing Object/ProcessedObject.h"
#include "VimbaCPP.h"
#include <VimbaCPP/Include/IFrameObserver.h>

class ProcessedObjectSensor :
    public ProcessedObject
{
    int frameDelay_;
    AVT::VmbAPI::CameraPtr camera_;
public:
    ProcessedObjectSensor();
    ProcessedObjectSensor(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, bool imageIsNull = false, int frameDelay = 0);
    ProcessedObjectSensor(const ProcessedObjectSensor& dep);
    void setFrameDelay(int newDelay);
    int getFrameDelay() const;
    AVT::VmbAPI::CameraPtr getCameraPtr() const;
    void setCameraPtr(AVT::VmbAPI::CameraPtr newCameraPtr);
    ProcessedObjectSensor& operator=(const ProcessedObjectSensor& drop);
};

