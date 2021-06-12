#include "ImageProcessedObject.h"

ImageProcessedObject::ImageProcessedObject()
{
}

ImageProcessedObject::ImageProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, QString programName, bool imageIsNull) :
	ProcessedObject(inputFileName, inputDirName, inputMat, inputPixmap, programName, imageIsNull)
{
}

ImageProcessedObject::ImageProcessedObject(const ImageProcessedObject& dep) 
{
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

ImageProcessedObject& ImageProcessedObject::operator=(const ImageProcessedObject& drop)
{
	fileName_ = drop.fileName_;
	dirName_ = drop.dirName_;
	originalPixmap_ = drop.originalPixmap_;
	originalMat_ = drop.originalMat_;
	correctPixmap_ = drop.originalPixmap_;
	correctMat_ = drop.correctMat_;
	processedArears_.assign(drop.processedArears_.begin(), drop.processedArears_.end());
	imageCorrected_ = drop.imageCorrected_;
	imageIsNull_ = drop.imageIsNull_;
	programName_ = drop.programName_;
	return *this;
}