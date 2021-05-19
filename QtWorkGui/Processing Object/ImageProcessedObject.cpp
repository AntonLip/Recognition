#include "ImageProcessedObject.h"

ImageProcessedObject::ImageProcessedObject():
	imageIsNull_(true),
	programName_("")
{
}

ImageProcessedObject::ImageProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, bool imegeIsLoad, QString programName):
	ProcessedObject(inputFileName,inputDirName,inputMat,inputPixmap),
	imageIsNull_(!imegeIsLoad),
	programName_(programName)
{
}

ImageProcessedObject::ImageProcessedObject(const ImageProcessedObject& dep) :
	imageIsNull_(dep.imageIsNull_),
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
}