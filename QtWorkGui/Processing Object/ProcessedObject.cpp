#include "ProcessedObject.h"

ProcessedObject::ProcessedObject():
	fileName_(""),
	dirName_(""),
	originalPixmap_(QPixmap()),
	originalMat_(cv::Mat()),
	correctPixmap_(QPixmap()),
	correctMat_(cv::Mat())
{
}

ProcessedObject::ProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap) :
	fileName_(inputFileName),
	dirName_(inputDirName),
	originalPixmap_(inputPixmap),
	originalMat_(inputMat),
	correctPixmap_(QPixmap()),
	correctMat_(cv::Mat())
{
}

QString ProcessedObject::getFileName()
{
	return fileName_;
}

void ProcessedObject::setFileName(QString newFileName)
{
	fileName_ = newFileName;
}

QString ProcessedObject::getDirName()
{
	return dirName_;
}

void ProcessedObject::setDirName(QString newDirName)
{
	dirName_ = newDirName;
}

QPixmap ProcessedObject::getOriginalPixmap()
{
	return originalPixmap_;
}

cv::Mat ProcessedObject::getOriginalMat()
{
	return originalMat_;
}

QPixmap ProcessedObject::getCorrectPixmap()
{
	return correctPixmap_;
}

cv::Mat ProcessedObject::getCorrectMat()
{
	return correctMat_;
}
