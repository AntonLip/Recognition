#include "ImageProcessedObject.h"

ImageProcessedObject::ImageProcessedObject():
	imageIsNull_(true),
	imageCorrected_(false),
	processAreas_({ QtProcessedArea(0,0,QtRotateRect(0,0,0,0,0)) }),
	programName_("")
{
}

ImageProcessedObject::ImageProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, bool imegeIsLoad, QString programName):
	ProcessedObject(inputFileName,inputDirName,inputMat,inputPixmap),
	imageIsNull_(!imegeIsLoad),
	imageCorrected_(false),
	processAreas_({ QtProcessedArea(0,0,QtRotateRect(0,0,0,0,0)) }),
	programName_(programName)
{
}

ImageProcessedObject::ImageProcessedObject(const ImageProcessedObject& dep):
	imageIsNull_(dep.imageIsNull_),
	imageCorrected_(dep.imageCorrected_),
	processAreas_(dep.processAreas_),
	programName_(dep.programName_)
{
}

bool ImageProcessedObject::imageIsNull()
{
	return imageIsNull_;
}

void ImageProcessedObject::setFlagImageIsNull(bool imageIsNull)
{
	imageIsNull_ = imageIsNull;
}

bool ImageProcessedObject::imageCorrected()
{
	return imageCorrected_;
}

void ImageProcessedObject::setFlagImageIsCorrected(bool imageIsCorrected)
{
	imageCorrected_ = imageIsCorrected;
}

QString ImageProcessedObject::getProgramName()
{
	return programName_;
}

void ImageProcessedObject::setProgramName(QString newProgramName)
{
	programName_ = newProgramName;
}

std::vector<QtProcessedArea>* ImageProcessedObject::getProcesArears()
{
	return &processAreas_;
}

void ImageProcessedObject::updateMat(cv::Mat newMat, QPixmap newPixmap)
{
	originalMat_ = newMat;
	originalPixmap_ = newPixmap;
}
