#include "ProcessedObject.h"

ProcessedObject::ProcessedObject():
	fileName_(""),
	dirName_(""),
	originalPixmap_(QPixmap()),
	originalMat_(cv::Mat()),
	correctPixmap_(QPixmap()),
	correctMat_(cv::Mat()),
	processedArears_({ QtProcessedArea(0,0,QtRotateRect(0,0,0,0,0)) }),
	imageCorrected_(false)
{
}

ProcessedObject::ProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap) :
	fileName_(inputFileName),
	dirName_(inputDirName),
	originalPixmap_(inputPixmap),
	originalMat_(inputMat),
	correctPixmap_(QPixmap()),
	correctMat_(cv::Mat()),
	processedArears_({ QtProcessedArea(0,0,QtRotateRect(0,0,0,0,0)) }),
	imageCorrected_(false)
{
}

ProcessedObject::ProcessedObject(const ProcessedObject& dep):
	fileName_(dep.fileName_),
	dirName_(dep.dirName_),
	originalPixmap_(dep.originalPixmap_),
	originalMat_(dep.originalMat_),
	correctPixmap_(dep.correctPixmap_),
	correctMat_(dep.correctMat_),
	processedArears_(dep.processedArears_),
	imageCorrected_(dep.imageCorrected_)
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

void ProcessedObject::setProcessedArears(std::vector<QtProcessedArea> *newProcessedAreas)
{
	processedArears_.assign(newProcessedAreas->begin(), newProcessedAreas->end());
}

std::vector<QtProcessedArea>* ProcessedObject::getProcessedArears()
{
	return &processedArears_;
}

void ProcessedObject::updateMat(cv::Mat newMat, QPixmap newPixmap)
{
	originalMat_ = newMat;
	originalPixmap_ = newPixmap;
}

ProcessedObject& ProcessedObject::operator=(const ProcessedObject& drop)
{
	fileName_ = drop.fileName_;
	dirName_ = drop.dirName_;
	originalPixmap_ = drop.originalPixmap_;
	originalMat_ = drop.originalMat_;
	correctPixmap_ = drop.originalPixmap_;
	correctMat_ = drop.correctMat_;
	processedArears_.assign(drop.processedArears_.begin(), drop.processedArears_.end());
	imageCorrected_ = drop.imageCorrected_;
	return *this;
}

bool ProcessedObject::imageCorrected()
{
	return imageCorrected_;
}
