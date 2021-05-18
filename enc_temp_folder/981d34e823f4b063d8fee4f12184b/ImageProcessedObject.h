#pragma once
#include "ProcessedObject.h"
#include "QtProcessedArea.h"

class ImageProcessedObject :
    public ProcessedObject
{
protected:
    bool imageIsNull_;
    bool imageCorrected_;
    
    QString programName_;
public:
    ImageProcessedObject();
    ImageProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, bool imegeIsLoad, QString programName);
    ImageProcessedObject(const ImageProcessedObject& dep);
    bool imageIsNull();
    void setFlagImageIsNull(bool imageIsNull);
    bool imageCorrected();
    void setFlagImageIsCorrected(bool imageIsCorrected);
    QString getProgramName();
    void setProgramName(QString newProgramName);
    virtual void updateMat(cv::Mat newMat, QPixmap newPixmap) override;
    virtual ImageProcessedObject* getThis() override;
};

