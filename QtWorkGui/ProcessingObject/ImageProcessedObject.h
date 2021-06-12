#pragma once
#include "ProcessedObject.h"
#include "QtProcessedArea.h"

class ImageProcessedObject :
    public ProcessedObject
{
protected:

public:
    ImageProcessedObject();
    ImageProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, QString programName, bool imegeIsNull = false);
    ImageProcessedObject(const ImageProcessedObject& dep);
    void setFlagImageIsCorrected(bool imageIsCorrected);
    QString getProgramName();
    void setProgramName(QString newProgramName);
    ImageProcessedObject& operator=(const ImageProcessedObject& drop);
};