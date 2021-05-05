#pragma once

#include <QObject>
#include <opencv2/core/core.hpp>

#include "Processing Object/QtProcessedArea.h"

class QtAreaToProcessed : public QObject
{
	Q_OBJECT
	cv::Rect ROI;
	int processedType;
	int doubleThreshRigth;
	int doubleThreshLeft;
	int singelThresh;
public:
	QtAreaToProcessed(QObject *parent=Q_NULLPTR);
	QtAreaToProcessed(QtProcessedArea *procesArea, QObject* parent=Q_NULLPTR);
	~QtAreaToProcessed();
};
