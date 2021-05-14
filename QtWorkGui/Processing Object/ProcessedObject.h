#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "qpixmap.h"

#ifndef  processedObject_h
#define  processedObject_h

class ProcessedObject
{
protected:
	QString fileName_;
	QString dirName_;
	QPixmap originalPixmap_;
	cv::Mat originalMat_;
	QPixmap correctPixmap_;
	cv::Mat correctMat_;
public:
	ProcessedObject();
	ProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap);
	QString getFileName();
	void setFileName(QString newFileName);
	QString getDirName();
	void setDirName(QString newDirName);
	QPixmap getOriginalPixmap();
	cv::Mat getOriginalMat();
	QPixmap getCorrectPixmap();
	cv::Mat getCorrectMat();
	virtual void updateMat(cv::Mat newMat, QPixmap newPixmap) = 0;
};

#endif