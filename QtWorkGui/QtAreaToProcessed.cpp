#include "QtAreaToProcessed.h"

QtAreaToProcessed::QtAreaToProcessed(QObject *parent)
	: QObject(parent),
	ROI(0, 0, 0, 0),
	processedType(0),
	doubleThreshRigth(0),
	doubleThreshLeft(0),
	singelThresh(0)
{
}

QtAreaToProcessed::QtAreaToProcessed(QtProcessedArea* procesArea, QObject* parent)
	:QObject(parent),
	ROI(0, 0, 0, 0),
	processedType(procesArea->getProcesseedType()),
	doubleThreshRigth(procesArea->getDoubelTresS()),
	doubleThreshLeft(procesArea->getDoubelTresF()),
	singelThresh(procesArea->getDoubelTresF())
{
	if (procesArea->getAreaType() == 0)
	{
		ROI = cv::Rect(cv::Point(procesArea->getRect()->getMin_X(), procesArea->getRect()->getMin_Y()), cv::Point(procesArea->getRect()->getMax_X(), procesArea->getRect()->getMax_Y()));
	}
	else if (procesArea->getAreaType() == 1)
	{
		QPoint center{ 0,0 };
		int radius{ 0 };
		procesArea->getCircleParm(radius, center);
		ROI = cv::Rect(cv::Point(center.x() - radius, center.y() - radius), cv::Point(center.x() + radius, center.y() + radius));
	}
	else if (procesArea->getAreaType() == 2)
	{
		ROI = cv::Rect(0, 0, 0, 0);
	}
}

QtAreaToProcessed::~QtAreaToProcessed()
{
}
