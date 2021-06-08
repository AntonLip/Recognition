#include "ProcessedObjectSensor.h"

ProcessedObjectSensor::ProcessedObjectSensor():
	frameDelay_{0}
{
}

ProcessedObjectSensor::ProcessedObjectSensor(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, bool imageIsNull, int frameDelay):
	ProcessedObject{ inputFileName,inputDirName,inputMat,inputPixmap,"sensor",imageIsNull },
	frameDelay_{ frameDelay }
{
}

ProcessedObjectSensor::ProcessedObjectSensor(const ProcessedObjectSensor& dep):
	frameDelay_{dep.frameDelay_}
{
}

void ProcessedObjectSensor::setFrameDelay(int newDelay)
{
	frameDelay_ = newDelay;
}

int ProcessedObjectSensor::getFrameDelay() const
{
	return frameDelay_;
}

ProcessedObjectSensor& ProcessedObjectSensor::operator=(const ProcessedObjectSensor& drop)
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
	frameDelay_ = drop.frameDelay_;
	return *this;
}
