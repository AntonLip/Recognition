#include "QtProcessedArea.h"

QtProcessedArea::QtProcessedArea(QObject* parent)
	: QObject(parent),
	processedAreaType(0),
	areaType(0),
	rect(QtRotateRect{}),
	circle(MyCircle{}),
	activ(false),
	draw(false),
	systemName(QString{}),
	userName(QString{}),
	doubleTreshF(0),
	doubleTreshS(0),
	singlTresActiv(false),
	counterProcessed{ new ProcessingCountours{} },
	colorProcessed{ new ProcessingColor{} },
	positionAdjustmentProcessed{ new ProcessingPositionAdjustment{} }
	//counterProc(nullptr)
{
	
}

QtProcessedArea::QtProcessedArea(int processedType, int areaType_, QtRotateRect newRect, QObject* parent)
	: QObject(parent),
	processedAreaType(processedType),
	areaType(areaType_),
	rect(newRect),
	activ(true),
	draw(true),
	circle(MyCircle{}),
	systemName(QString{}),
	userName(QString{}),
	doubleTreshF(0),
	doubleTreshS(0),
	singlTresActiv(false),
	counterProcessed{ new ProcessingCountours{} },
	colorProcessed{ new ProcessingColor{} },
	positionAdjustmentProcessed{ new ProcessingPositionAdjustment{} }
	
	//counterProc(nullptr)
{
	if (processedType == 1)
	{
		
	}
}

QtProcessedArea::QtProcessedArea(int processedType, int areaType_, MyCircle newCircle, QObject* parent) :

	processedAreaType(processedType),
	areaType(areaType_),
	rect(QtRotateRect()),
	activ(true),
	draw(true),
	circle(newCircle),
	systemName(QString{}),
	userName(QString{}),
	doubleTreshF(0),
	doubleTreshS(0),
	singlTresActiv(false),
	counterProcessed{ new ProcessingCountours{} },
	colorProcessed{ new ProcessingColor{} },
	positionAdjustmentProcessed{ new ProcessingPositionAdjustment{} }
	//counterProc(nullptr)
{
	if (processedType == 1)
	{

	}
}

QtProcessedArea::QtProcessedArea(const QtProcessedArea& drop)
	:processedAreaType(drop.processedAreaType),
	areaType(drop.areaType),
	rect(drop.rect),
	activ(drop.activ),
	draw(drop.draw),
	systemName(drop.systemName),
	userName(drop.userName),
	doubleTreshF(drop.doubleTreshF),
	doubleTreshS(drop.doubleTreshS),
	singlTresActiv(drop.singlTresActiv),
	circle(drop.circle),
	counterProcessed{ new ProcessingCountours(*drop.counterProcessed) },
	colorProcessed{ new ProcessingColor{*drop.colorProcessed} },
	positionAdjustmentProcessed{ new ProcessingPositionAdjustment{*drop.positionAdjustmentProcessed} }
{
	
}

QtProcessedArea::QtProcessedArea(QtProcessedArea&& drop):
	processedAreaType(drop.processedAreaType),
	areaType(drop.areaType),
	rect(drop.rect),
	activ(drop.activ),
	draw(drop.draw),
	systemName(drop.systemName),
	userName(drop.userName),
	doubleTreshF(drop.doubleTreshF),
	doubleTreshS(drop.doubleTreshS),
	singlTresActiv(drop.singlTresActiv),
	circle(drop.circle),
	counterProcessed{ drop.counterProcessed },
	colorProcessed{ drop.colorProcessed },
	positionAdjustmentProcessed{ drop.positionAdjustmentProcessed }
{
	drop.counterProcessed = nullptr;
	drop.colorProcessed = nullptr;
}

QtProcessedArea::~QtProcessedArea()
{
	
}

void QtProcessedArea::createMaster(cv::Mat const* inputImg)
{
	cv::Rect roi(0, 0, 0, 0);
	if (areaType == 0)
	{
		roi = cv::Rect(rect.getRotateRectSize().x(), rect.getRotateRectSize().y(), rect.getRotateRectSize().width() + 1, rect.getRotateRectSize().height() + 1);
	}
	else if (areaType == 1)
	{
		roi = cv::Rect(circle.getCenterPoint().x() - circle.getRadius(), circle.getCenterPoint().y() - circle.getRadius(), circle.getRadius() * 2, circle.getRadius() * 2);
	}
	if (processedAreaType == 1)
	{
		//cv::Mat procImg(*inputImg);
		//cv::cvtColor(*inputImg, procImg, cv::COLOR_RGB2GRAY);
		//counterProc->findAndSetMasterContours(&procImg);
		counterProcessed->performProcessing(&(*inputImg)(roi));
	}
	else if (processedAreaType == 2)
	{
		colorProcessed->performProcessing(&(*inputImg)(roi));
	}
	else if (processedAreaType == 4)
	{
		positionAdjustmentProcessed->performProcessing(inputImg, &roi);
	}
}

void QtProcessedArea::setRect(QtRotateRect* newRect)
{
	rect = *newRect;
}

//void QtProcessedArea::setScalRect(QtRotateRect* newRect)
//{
//	scalRect = *newRect;
//}

cv::Mat QtProcessedArea::getDrawImage(cv::Mat const* inputImg)
{
	cv::Rect roi(0,0,0,0);
	cv::Mat mask(inputImg->size(), CV_8UC3,cv::Scalar(255,255,255));
	if (areaType == 0)
	{
		cv::Point vertices[4];
		vertices[0] = cv::Point(rect.getUpLeft_X() + 1, rect.getUpLeft_Y() + 1);
		vertices[1] = cv::Point(rect.getUpRigth_X(), rect.getUpRigth_Y() + 1);
		vertices[2] = cv::Point(rect.getDownRigth_X(), rect.getDownRigth_Y());
		vertices[3] = cv::Point(rect.getDownLeft_X() + 1, rect.getDownLeft_Y());
		cv::fillConvexPoly(mask, vertices, 4, cv::Scalar(0, 0, 0));
		roi=cv::Rect(rect.getRotateRectSize().x(), rect.getRotateRectSize().y(), rect.getRotateRectSize().width() + 1, rect.getRotateRectSize().height() + 1);
	}
	else if(areaType == 1)
	{
		cv::circle(mask, cv::Point(circle.getCenterPoint().x(), circle.getCenterPoint().y()), circle.getRadius(), cv::Scalar(0, 0, 0),-1,-1);
		roi = cv::Rect(circle.getCenterPoint().x() - circle.getRadius(), circle.getCenterPoint().y() - circle.getRadius(), circle.getRadius() * 2, circle.getRadius() * 2);
	}
	mask = mask(roi);
	cv::Mat procesingImgPart(*inputImg);
	procesingImgPart = procesingImgPart(roi);
	if (processedAreaType == 1)
	{
		counterProcessed->drawResultImage(procesingImgPart);
	}
	else if (processedAreaType == 2)
	{
		colorProcessed->drawResultImage(procesingImgPart);
	}
	else if (processedAreaType == 4)
	{
		positionAdjustmentProcessed->drawResultImage(procesingImgPart);
	}
	cv::Mat backGround;
	if(inputImg->type()==CV_8U)
		cv::cvtColor(mask, mask, cv::COLOR_RGB2GRAY);
	cv::bitwise_and(cv::Mat(*inputImg,roi), mask, backGround);
	cv::bitwise_not(mask, mask);
	if (inputImg->type() == CV_8U)
		cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);
	cv::bitwise_and(procesingImgPart, mask, procesingImgPart);
	/*if (inputImg->type() == CV_8U)
		cv::cvtColor(backGround, backGround, cv::COLOR_BGR2GRAY);*/
	cv::bitwise_or(procesingImgPart, backGround, procesingImgPart);
	return procesingImgPart;
}

void QtProcessedArea::setCircle(MyCircle* newCircle)
{
	circle = *newCircle;
}

//void QtProcessedArea::setScalCircle(MyCircle* newCirkle)
//{
//	scalCircle = *newCirkle;
//}

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

//QtRotateRect* QtProcessedArea::getScalRect()
//{
//	return &scalRect;
//}

MyCircle* QtProcessedArea::getCircle()
{
	return &circle;
}

//MyCircle* QtProcessedArea::getScalCircle()
//{
//	return &scalCircle;
//}

void QtProcessedArea::getCircleParm(int &radius, QPoint &center)
{
	radius = circle.getRadius();
	center = circle.getCenterPoint();
}

//void QtProcessedArea::getScalCircleParam(int& radius, QPoint& center)
//{
//	radius = scalCircle.getRadius();
//	center = scalCircle.getCenterPoint();
//}

void QtProcessedArea::setProcessing(int typeProcessing)
{
	typeProcessing = processedAreaType;
	//if (typeProcessing == 0)
	//{
	//	typeProcessing = processedAreaType;
	//}
	//else if (typeProcessing == 1)
	//{
	//	typeProcessing = processedAreaType;
	//	//counterProcessed = new ProcessingCountours();
	//}
}

QtProcessedArea& QtProcessedArea::operator=(const QtProcessedArea& drop)
{
	processedAreaType = drop.processedAreaType;
	areaType = drop.areaType;
	rect = drop.rect;
	activ = drop.activ;
	draw = drop.draw;
	systemName = drop.systemName;
	userName = drop.userName;
	doubleTreshF = drop.doubleTreshF;
	doubleTreshS = drop.doubleTreshS;
	singlTresActiv = drop.singlTresActiv;
	circle = drop.circle;
	counterProcessed = new ProcessingCountours(*drop.counterProcessed);
	colorProcessed = new ProcessingColor(*drop.colorProcessed);
	positionAdjustmentProcessed = new ProcessingPositionAdjustment(*drop.positionAdjustmentProcessed);
	std::cout << "=" << std::endl;
	return *this;
}

QRect QtProcessedArea::getOriginalLimitRect()
{
	if (areaType == 0)
	{
		return QRect(rect.getMin_X(), rect.getMin_Y(), rect.getMax_X() - rect.getMin_X() + 1, rect.getMax_Y() - rect.getMin_Y() + 1);
	}
	else if (areaType == 1)
	{
		return QRect(circle.getCenterPoint().x() - circle.getRadius(), circle.getCenterPoint().y() - circle.getRadius(), circle.getRadius() * 2, circle.getRadius() * 2);
	}
}

void QtProcessedArea::updateProcessing(cv::Mat newOriginImeg)
{
	cv::Rect roi(0, 0, 0, 0);
	if (areaType == 0)
	{
		roi = cv::Rect(rect.getRotateRectSize().x(), rect.getRotateRectSize().y(), rect.getRotateRectSize().width() + 1, rect.getRotateRectSize().height() + 1);
	}
	else if (areaType == 1)
	{
		roi = cv::Rect(circle.getCenterPoint().x() - circle.getRadius(), circle.getCenterPoint().y() - circle.getRadius(), circle.getRadius() * 2, circle.getRadius() * 2);
	}
	if (processedAreaType == 1)
	{
		counterProcessed->performProcessing(&newOriginImeg(roi));
	}
	else if (processedAreaType == 2)
	{
		colorProcessed->performProcessing(&newOriginImeg(roi));
	}
	else if (processedAreaType == 4)
	{
		positionAdjustmentProcessed->performProcessing(&newOriginImeg, &roi);
	}
}

void QtProcessedArea::getProcessedThreshold(std::vector<int>& threshold)
{
	if (processedAreaType == 1)
		counterProcessed->getThreshold(threshold);
	else if (processedAreaType = 2)
		colorProcessed->getThreshold(threshold);
	else if (processedAreaType = 4)
		positionAdjustmentProcessed->getThreshold(threshold);
}

void QtProcessedArea::setProcessedThreshold(std::vector<int>& const threshold)
{
	if (processedAreaType == 1)
		counterProcessed->setThreshold(threshold);
	else if (processedAreaType = 2)
		colorProcessed->setThreshold(threshold);
	else if (processedAreaType = 4)
		positionAdjustmentProcessed->setThreshold(threshold);
}

int QtProcessedArea::computeComparsion(cv::Mat* const masterImage)
{
	if (processedAreaType == 1)
	{
		counterProcessed->computeComparsion(true, std::vector<int>{1}, masterImage, rect);
	}
	else if (processedAreaType == 2)
	{
		colorProcessed->computeComparsion(true, std::vector<int>{1}, masterImage, rect);
	}
	else if (processedAreaType == 4)
	{
		positionAdjustmentProcessed->computeComparsion(true, std::vector<int>{1}, masterImage, rect);
	}
	return 0;
}

cv::Mat* QtProcessedArea::getMasterImage()
{
	if (processedAreaType == 1)
	{
		return counterProcessed->getProcessingImage();
	}
	else if (processedAreaType == 2)
	{
		return colorProcessed->getProcessingImage();
	}
	else if (processedAreaType == 4)
	{
		return positionAdjustmentProcessed->getProcessingImage();
	}
}

//QRect QtProcessedArea::getScaledLimitRect()
//{
//	if (areaType == 0)
//	{
//		return QRect(scalRect.getMin_X(), scalRect.getMin_Y(), scalRect.getMax_X() - scalRect.getMin_X(), scalRect.getMax_Y() - scalRect.getMin_Y());
//	}
//	else if (areaType == 1)
//	{
//		return QRect(scalCircle.getCenterPoint().x() - scalCircle.getRadius(), scalCircle.getCenterPoint().y() - scalCircle.getRadius(), scalCircle.getRadius() * 2, scalCircle.getRadius() * 2);
//	}
//}

double QtProcessedArea::getArea(bool scaled)
{
	/*if (scaled)
	{
		if (areaType == 0)
			return scalRect.height() * scalRect.width();
		else if (areaType == 1)
			return scalCircle.getArea();
	}
	else*/
	//{
		if (areaType == 0)
			return rect.height() * rect.width();
		else if (areaType == 1)
			return circle.getArea();
	//}
}