#include "QtProcessedArea.h"

QtProcessedArea::QtProcessedArea(QObject *parent)
	: QObject(parent)
{
	
	processedAreaType = 0;
	areaType = 0;
	rect = QtRotateRect{};
	scalRect = QtRotateRect{};
	circle = MyCircle{};
	scalCircle = MyCircle{};
	activ = false;
	draw = false;
	systemName = QString{};
	userName = QString{};
	doubleTreshF = 0;
	doubleTreshS = 0;
	singlTresActiv = false;
}

QtProcessedArea::QtProcessedArea( int processedType,  int areaType_, QtRotateRect newRect, QObject* parent)
	: QObject(parent)
{
	processedAreaType = processedType;
	areaType = areaType_;
	rect = newRect;
	scalRect = newRect;
	activ = true;
	draw = true;
	circle = MyCircle{};
	scalCircle = MyCircle{};
	systemName = QString{};
	userName = QString{};
	doubleTreshF = 0;
	doubleTreshS = 0;
	singlTresActiv = false;
}

QtProcessedArea::QtProcessedArea(int processedType, int areaType_, MyCircle newCircle, QObject* parent)
{
	processedAreaType = processedType;
	areaType = areaType_;
	rect = QtRotateRect();
	scalRect = QtRotateRect();
	activ = true;
	draw = true;
	circle = newCircle;
	scalCircle = newCircle;
	systemName = QString{};
	userName = QString{};
	doubleTreshF = 0;
	doubleTreshS = 0;
	singlTresActiv = false;
}

QtProcessedArea::QtProcessedArea(const QtProcessedArea& drop):processedAreaType(drop.processedAreaType),areaType(drop.areaType),rect(drop.rect),scalRect(drop.scalRect), activ(drop.activ), draw(drop.draw), systemName(drop.systemName), userName(drop.userName), doubleTreshF(drop.doubleTreshF), doubleTreshS(drop.doubleTreshS), singlTresActiv(drop.singlTresActiv), circle(drop.circle), scalCircle(drop.scalCircle)
{
}

QtProcessedArea::~QtProcessedArea()
{
}

void QtProcessedArea::setRect(QtRotateRect* newRect)
{
	rect = *newRect;
}

void QtProcessedArea::setScalRect(QtRotateRect* newRect)
{
	scalRect = *newRect;
}

void QtProcessedArea::setCircle(MyCircle* newCircle)
{
	circle = *newCircle;
}

void QtProcessedArea::setScalCircle(MyCircle* newCirkle)
{
	scalCircle = *newCirkle;
}

void QtProcessedArea::setAreaType(int newType)
{
	areaType = newType;
}

void QtProcessedArea::setProcessedType(int newType)
{
	processedAreaType = newType;
}

void QtProcessedArea::setActiv(bool isActiv)
{
	activ = isActiv;
}

void QtProcessedArea::setDraw(bool isDraw)
{
	draw = isDraw;
}

void QtProcessedArea::setSystemName(QString newName)
{
	systemName = newName;
}

void QtProcessedArea::setActivTres(bool isSingel)
{
	singlTresActiv = isSingel;
}

void QtProcessedArea::setDoubelTreshF(int min)
{	
	doubleTreshF = min;
}

void QtProcessedArea::setDoubelTreshS(int max)
{

	doubleTreshS = max;
}

bool QtProcessedArea::singelIsActivTresh()
{
	return singlTresActiv;
}

int QtProcessedArea::getDoubelTresF()
{
	return doubleTreshF;
}

int QtProcessedArea::getDoubelTresS()
{
	return doubleTreshS;
}

QString QtProcessedArea::getSystemName()
{
	return systemName;
}

QString QtProcessedArea::getProcesName()
{
	if (processedAreaType == 1)
		return "Outline";
	else if (processedAreaType == 2)
		return "Color";
	else if (processedAreaType == 3)
		return "Edge Pixel";
	else if (processedAreaType == 4)
		return "Position Adjustment";
	else if (processedAreaType == 5)
		return "Width";
	else if (processedAreaType == 6)
		return "Diametr";
	else if (processedAreaType == 7)
		return "Edge";
	else if (processedAreaType == 8)
		return "Pitch";
	else if (processedAreaType == 9)
		return "High-Speed";
	else if (processedAreaType == 10)
		return "OCR";
	else
		return "";
}

void QtProcessedArea::setUserName(QString newName)
{
	userName = newName;
}

QString QtProcessedArea::getUserName()
{
	return userName;
}

bool QtProcessedArea::isActiv()
{
	return activ;
}

bool QtProcessedArea::isDraw()
{
	return draw;
}

int QtProcessedArea::getAreaType()
{
	return areaType;
}

int QtProcessedArea::getProcesseedType()
{
	return processedAreaType;
}

QtRotateRect* QtProcessedArea::getRect()
{
	return &rect;
}

QtRotateRect* QtProcessedArea::getScalRect()
{
	return &scalRect;
}

MyCircle* QtProcessedArea::getCircle()
{
	return &circle;
}

MyCircle* QtProcessedArea::getScalCircle()
{
	return &scalCircle;
}

void QtProcessedArea::getCircleParm(int &radius, QPoint &center)
{
	radius = circle.getRadius();
	center = circle.getCenterPoint();
}

void QtProcessedArea::getScalCircleParam(int& radius, QPoint& center)
{
	radius = scalCircle.getRadius();
	center = scalCircle.getCenterPoint();
}

QtProcessedArea& QtProcessedArea::operator=(const QtProcessedArea& drop)
{
	processedAreaType = drop.processedAreaType;
	areaType = drop.areaType;
	rect = drop.rect;
	scalRect = drop.scalRect;
	activ = drop.activ;
	draw = drop.draw;
	systemName = drop.systemName;
	userName = drop.userName;
	doubleTreshF = drop.doubleTreshF;
	doubleTreshS = drop.doubleTreshS;
	singlTresActiv = drop.singlTresActiv;
	circle = drop.circle;
	scalCircle = drop.scalCircle;
	return *this;
}

double QtProcessedArea::getArea(bool scaled)
{
	if (scaled)
	{
		if (areaType == 0)
			return scalRect.height() * scalRect.width();
		else if (areaType == 1)
			return scalCircle.getArea();
	}
	else
	{
		if (areaType == 0)
			return rect.height() * rect.width();
		else if (areaType == 1)
			return circle.getArea();
	}
}