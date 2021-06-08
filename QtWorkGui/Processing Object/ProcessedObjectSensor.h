#pragma once
#include "Processing Object/ProcessedObject.h"
class ProcessedObjectSensor :
    public ProcessedObject
{
    int frameDelay_;
public:
    ProcessedObjectSensor();
    ProcessedObjectSensor(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, bool imageIsNull = false, int frameDelay = 0);
    ProcessedObjectSensor(const ProcessedObjectSensor& dep);
    void setFrameDelay(int newDelay);
    int getFrameDelay() const;
    ProcessedObjectSensor& operator=(const ProcessedObjectSensor& drop);
};

