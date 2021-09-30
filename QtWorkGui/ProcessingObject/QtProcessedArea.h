#pragma once

#include <QObject>
#include <qrect.h>
#include "MyCircle.h"
#include "QtRotateRect.h"
#include "Processing/CountoursProcessing.h"
#include "Processing/ProcessingCountours.h"
#include "Processing/ProcessingColor.h"
#include "Processing/ProcessingPositionAdjustment.h"
#include "qimage.h"

class QtProcessedArea : public QObject
{
	Q_OBJECT
	int processedAreaType; ///0-BrightnesCorrect, 1-outlineArea, 2-color, 3-edgePixel, 4-positionAdjustment, 5-width, 6-diametr, 7-edge, 8-pitch, 9-HighSpeed,10-OCR
	int areaType;///0-rectangel,1-circle,2-enter
	QtRotateRect rect;
	MyCircle circle;
	bool activ;
	bool draw;
	QString systemName;
	QString userName;
	int doubleTreshF;
	int doubleTreshS;
	bool singlTresActiv;
	//CountoursProcessing *counterProc;
	ProcessingCountours* counterProcessed;
	ProcessingColor* colorProcessed;
	ProcessingPositionAdjustment* positionAdjustmentProcessed;
public:
	QtProcessedArea(QObject *parent=Q_NULLPTR );
	QtProcessedArea(int processedType, int areaType, QtRotateRect newRect, QObject* parent = Q_NULLPTR);
	QtProcessedArea(int processedType, int areaType, MyCircle newCircle, QObject* parent = Q_NULLPTR);
	QtProcessedArea(const QtProcessedArea& drop);
	QtProcessedArea(QtProcessedArea&& drop);
	~QtProcessedArea();
	void createMaster(cv::Mat const *inputImg);
	void setRect(QtRotateRect* newRect);
	cv::Mat getDrawImage(cv::Mat const* inputImg);
	void setCircle(MyCircle* newCircle);
	void setAreaType(int newType);
	void setProcessedType(int newType);
	void setActiv(bool isActiv);
	void setDraw(bool isDraw);
	void setSystemName(QString newName);
	void setActivTres(bool isSingel);
	void setDoubelTreshF(int min);
	void setDoubelTreshS(int max);
	bool singelIsActivTresh();
	int getDoubelTresF();
	int getDoubelTresS();
	QString getSystemName();
	QString getProcesName();
	void setUserName(QString newName);
	QString getUserName();
	bool isActiv();
	bool isDraw();
	int getAreaType();
	int getProcesseedType();
	double getArea(bool scaled=false);
	QtRotateRect* getRect();
	MyCircle* getCircle();
	void getCircleParm(int& radius, QPoint& center);
	void setProcessing(int typeProcessing = 0);
	QtProcessedArea& operator=(const QtProcessedArea& drop);
	QRect getOriginalLimitRect();
	void updateProcessing(cv::Mat newOriginImeg);
	void getProcessedThreshold(std::vector<int>& threshold);
	void setProcessedThreshold(std::vector<int>& const threshold);
	int computeComparsion(cv::Mat* const masterImage);
	cv::Mat* getMasterImage();
	void setCenter(cv::Point const newCenter);
	void setRotateAngel(float const newRotateAngel);
	
};
