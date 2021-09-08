#include "ProcessedObject.h"

ProcessedObject::ProcessedObject():
	fileName_{},
	dirName_{},
	originalPixmap_{},
	originalMat_{},
	correctPixmap_{},
	correctMat_{},
	processedArears_{},
	imageCorrected_{ false },
	imageIsNull_{true},
	programName_{}
{
}

ProcessedObject::ProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, QString programName, bool imageIsNull) :
	fileName_{ inputFileName },
	dirName_{inputDirName},
	originalPixmap_{ inputPixmap },
	originalMat_{inputMat},
	correctPixmap_{inputPixmap},
	correctMat_{inputMat},
	processedArears_{ QtProcessedArea(0,0,QtRotateRect(0,0,0,0,0)) },
	imageCorrected_{false},
	imageIsNull_{imageIsNull},
	programName_{programName}
{
}

ProcessedObject::ProcessedObject(const ProcessedObject& dep):
	fileName_{ dep.fileName_ },
	dirName_{dep.dirName_},
	originalPixmap_{dep.originalPixmap_},
	originalMat_{dep.originalMat_},
	correctPixmap_{dep.correctPixmap_},
	correctMat_{dep.correctMat_},
	processedArears_{dep.processedArears_ },
	imageCorrected_{dep.imageCorrected_},
	imageIsNull_{dep.imageIsNull_},
	programName_{dep.programName_}
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

cv::Mat ProcessedObject::getMat()
{
	return correctMat_;
}

void ProcessedObject::setProcessedArears(std::vector<QtProcessedArea> *newProcessedAreas)
{
	processedArears_.assign(newProcessedAreas->begin(), newProcessedAreas->end());
	for (size_t i{ 0 }; i < processedArears_.size(); ++i)
	{
		if(processedArears_[i].getProcesseedType()==1 || processedArears_[i].getProcesseedType() == 2)
			processedArears_[i].updateProcessing(originalMat_);
	}
}

std::vector<QtProcessedArea>* ProcessedObject::getProcesArears()
{
	return &processedArears_;
}

void ProcessedObject::updateMat(cv::Mat newMat, QPixmap newPixmap)
{
	originalMat_ = newMat;
	originalPixmap_ = newPixmap;
	correctMat_ = newMat;
	correctPixmap_ = newPixmap;
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
	imageIsNull_ = drop.imageIsNull_;
	programName_ = drop.programName_;
	return *this;
}

ProcessedObject& ProcessedObject::operator=(ProcessedObject&& drop)
{
	fileName_ = drop.fileName_;
	dirName_ = drop.dirName_;
	originalPixmap_ = drop.originalPixmap_;
	originalMat_ = drop.originalMat_;
	correctPixmap_ = drop.originalPixmap_;
	correctMat_ = drop.correctMat_;
	processedArears_.assign(drop.processedArears_.begin(), drop.processedArears_.end());
	drop.processedArears_.clear();
	imageCorrected_ = drop.imageCorrected_;
	imageIsNull_ = drop.imageIsNull_;
	programName_ = drop.programName_;
	return *this;
}

bool ProcessedObject::imageCorrected()
{
	return imageCorrected_;
}

bool ProcessedObject::imageIsNull()
{
	return imageIsNull_;
}

void ProcessedObject::setFlagImageIsNull(bool imageIsNull)
{
	imageIsNull_ = imageIsNull;
}

QString ProcessedObject::getProgramName()
{
	return programName_;
}

void ProcessedObject::setProgramName(QString newProgramName)
{
	programName_ = newProgramName;
}

int ProcessedObject::loadImage()
{
	QString qstr_bufer{ QFileDialog::getOpenFileName(nullptr, "Images", "D:/", ("Images files (*.png *.jpg *.bmp)")) };
	cv::Mat img_bufer;
	img_bufer = cv::imread(qstr_bufer.toStdString());
	if (!img_bufer.empty())// checking that image has loaded 
	{
		std::size_t found = qstr_bufer.toStdString().find_last_of("/\\");
		fileName_ = QString::fromStdString(qstr_bufer.toStdString().substr(found + 1));
		dirName_ = QString::fromStdString(qstr_bufer.toStdString().substr(0, found));
		originalMat_ = img_bufer;
		correctMat_ = img_bufer;
		originalPixmap_ = QPixmap(qstr_bufer);
		correctPixmap_ = QPixmap(qstr_bufer);
		imageIsNull_ = false;
		return 0;
	}
	else
	{
		return 1;
	}
}

void ProcessedObject::updateProcessedArears()
{
	for (size_t i{ 0 }; i < processedArears_.size(); ++i)
	{
		if (processedArears_[i].getProcesseedType() == 1 || processedArears_[i].getProcesseedType() == 2)
			processedArears_[i].updateProcessing(correctMat_);
	}
}

int ProcessedObject::computeComparsion(std::vector<QtProcessedArea>* const masterProcessedAreas)
{
	for (size_t i{ 0 }; i < processedArears_.size(); ++i)
	{
		if (processedArears_[i].getProcesseedType() == 4)
		{
			processedArears_[i].updateProcessing(originalMat_);
		}
		processedArears_[i].computeComparsion((*masterProcessedAreas)[i].getMasterImage());
		
	}
	return 0;
}
