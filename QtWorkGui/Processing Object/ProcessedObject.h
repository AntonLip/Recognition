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
	bool imageCorrected_;
	bool imageIsNull_;
	QString programName_;

public:
	ProcessedObject();
	ProcessedObject(QString inputFileName, QString inputDirName, cv::Mat inputMat, QPixmap inputPixmap, QString programName, bool imageIsNull = false);
	ProcessedObject(const ProcessedObject& dep);
	QString getFileName();
	void setFileName(QString newFileName);
	QString getDirName();
	void setDirName(QString newDirName);
	QPixmap getOriginalPixmap();
	cv::Mat getOriginalMat();
	QPixmap getCorrectPixmap();
	cv::Mat getMat();
	void setProcessedArears(std::vector<QtProcessedArea> *newProcessedAreas);
	std::vector<QtProcessedArea>* getProcesArears();
	void updateMat(cv::Mat newMat, QPixmap newPixmap);
	ProcessedObject& operator=(const ProcessedObject& drop);
	bool imageCorrected();
	bool imageIsNull();
	void setFlagImageIsNull(bool imageIsNull);
	QString getProgramName();
	void setProgramName(QString newProgramName);
};

#endif