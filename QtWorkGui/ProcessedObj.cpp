#include "ProcessedObj.h"


ProcessedObj::ProcessedObj()
{
	processAreas.push_back(QtProcessedArea(0,0,QtRotateRect()));
	brightnesCorrectSet = false;
}


ProcessedObj::~ProcessedObj()
{
}

ProcessedObj::ProcessedObj(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap)
{
	brightnesCorrectSet = false;
	processAreas.push_back(QtProcessedArea(0, 0, QtRotateRect()));
	fileName = inputFileName;
	dirName = inputDirName;
	mainImgMat = inputMat;
	mainImgPixmap = inputPixmap;
	brightnesCorrectSet = false;
}

ProcessedObj::ProcessedObj(QString inputFileName, QString inputDirName, QString inputProgName, cv::Mat inputMat, QPixmap inputPixmap, bool imgIsNull_)
{
	brightnesCorrectSet = false;
	processAreas.push_back(QtProcessedArea(0, 0, QtRotateRect()));
	imgIsNull = imgIsNull_;
	programName = inputProgName;
	fileName = inputFileName;
	dirName = inputDirName;
	mainImgMat = inputMat;
	mainImgPixmap = inputPixmap;
	brightnesCorrectSet = false;
}

QString ProcessedObj::getFileName()
{
	return fileName;
}

void ProcessedObj::SetFileName(QString inputFileName)
{
	fileName = inputFileName;
}

QString ProcessedObj::getDirName()
{
	return dirName;
}

void ProcessedObj::SetDirName(QString inputDirName)
{
	dirName = inputDirName;
}

QPixmap ProcessedObj::getPixmap()
{
	return mainImgPixmap;
}

QPixmap ProcessedObj::getTestPixmap(int number)
{
	return testImgPixmap[number];
}

cv::Mat ProcessedObj::getTestMat(int number)
{
	return testImgMat[number];
}

cv::Mat ProcessedObj::getMat()
{
	return mainImgMat;
}

void ProcessedObj::updateObj(QPixmap inputPixmap)
{
	mainImgPixmap = inputPixmap;
}

void ProcessedObj::SetObjParams(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, bool imgIsNull_)
{
	imgIsNull = imgIsNull_;
	fileName = inputFileName;
	dirName = inputDirName;
	mainImgMat = inputMat;
	mainImgPixmap = inputPixmap;
}

void ProcessedObj::setProgramName(QString newName)
{
	programName = newName;
}

void ProcessedObj::setBrightnesCorrectArea(QRect *area)
{
	processAreas[0].setScalRect(&QtRotateRect(*area));
	brightnesCorrectSet = true;
}

void ProcessedObj::deletBrightnesCorrectArea()
{
	brightnesCorrectSet = false;
	QRect QR(0, 0, 0, 0);
	processAreas[0].setRect(&QtRotateRect(QR));
	processAreas[0].setScalRect(&QtRotateRect(QR));
	processAreas[0].setActiv(false);
}

void ProcessedObj::addTestImg(QString nameImg)
{
	testImgPixmap.push_back(QPixmap(nameImg));
	testImgMat.push_back(cv::imread(nameImg.toStdString()));
}

int ProcessedObj::getTestVecSize()
{
	return testImgPixmap.size();
}

std::vector<QtProcessedArea>* ProcessedObj::getProcesArears()
{
	return &processAreas;
}

bool ProcessedObj::brightnesCorrectAreaIsSet()
{
	return brightnesCorrectSet;
}

QRect* ProcessedObj::getBrightnesCorrectArea()
{
	if (brightnesCorrectSet)
		return processAreas[0].getRect();
	else
		return nullptr;
}


QString ProcessedObj::getProgramName()
{
	return programName;
}

bool ProcessedObj::imgIsLoaded()
{
	if (imgIsNull)
		return false;
	else
		return true;
}
