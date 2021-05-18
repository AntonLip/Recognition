#include "ImageProcessedObject.h"

ImageProcessedObject::ImageProcessedObject():
	imageIsNull_(true),
	imageCorrected_(false),
	programName_("")
{
}

ImageProcessedObject::ImageProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, bool imegeIsLoad, QString programName):
	ProcessedObject(inputFileName,inputDirName,inputMat,inputPixmap),
	imageIsNull_(!imegeIsLoad),
	imageCorrected_(false),
	programName_(programName)
{
}

ImageProcessedObject::ImageProcessedObject(const ImageProcessedObject& dep):
	imageIsNull_(dep.imageIsNull_),
	imageCorrected_(dep.imageCorrected_),
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

void ImageProcessedObject::updateMat (cv::Mat newMat, QPixmap newPixmap)
{
	originalMat_ = newMat;
	originalPixmap_ = newPixmap;
}

ProcessedObject* ImageProcessedObject::getThis()
{
	return new ImageProcessedObject(*this);
}

void ImageProcessedObject::assign(ProcessedObject& dep)
{
	dep.getThis()->
}
