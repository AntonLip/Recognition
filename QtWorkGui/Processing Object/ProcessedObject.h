#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "qpixmap.h"
#include "QtProcessedArea.h"

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
	std::vector<QtProcessedArea> processedArears_;
public:
	ProcessedObject();
	ProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap);
	ProcessedObject(const ProcessedObject& dep);
	QString getFileName();
	void setFileName(QString newFileName);
	QString getDirName();
	void setDirName(QString newDirName);
	QPixmap getOriginalPixmap();
	cv::Mat getOriginalMat();
	QPixmap getCorrectPixmap();
	cv::Mat getCorrectMat();
	void setProcessedArears(std::vector<QtProcessedArea> *newProcessedAreas);
	std::vector<QtProcessedArea>* getProcessedArears();
	
	virtual void updateMat(cv::Mat newMat, QPixmap newPixmap) = 0;
	virtual ProcessedObject* getThis() = 0;
	virtual void assign(ProcessedObject& dep) = 0;
};

#endif