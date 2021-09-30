#include "QtRotateRect.h"

QtRotateRect::QtRotateRect(QRect parent, double rotatAngel)
	: QRect(parent), 
	rotationAngle(rotatAngel), 
	drawPoint(0,0), 
	translatePoint(0,0), 
	upLeftAngel_X(0), upLeftAngel_Y(0), 
	upRigAngel_X(0), upRigAngel_Y(0), 
	downLeftAngel_X(0), 
	downLeftAngel_Y(0), 
	downRigAngel_X(0), 
	downRigAngel_Y(0)
{
	double radius{ sqrt(width() * width() + height() * height()) / 2 };
	double constAngel{ asin((height() / 2) / radius) };
	upLeftAngel_X = static_cast<double>(this->x() + width() / 2 - (sin((90 - rotationAngle) * pi / 180 - constAngel) * radius) );
	upLeftAngel_Y = static_cast<double>(this->y() + height() / 2 - (cos((90 - rotationAngle) * pi / 180 - constAngel) * radius));
	upRigAngel_X = static_cast<double>((this->width() * sin((90 - rotationAngle) * pi / 180.0)) + upLeftAngel_X );
	upRigAngel_Y = static_cast<double>(upLeftAngel_Y + (this->width() * cos((90 - rotationAngle) * pi / 180.0)) );
	downLeftAngel_X = static_cast<double>(upLeftAngel_X - (this->height() * cos((90 - rotationAngle) * pi / 180.0)));
	downLeftAngel_Y = static_cast<double>(upLeftAngel_Y + (this->height() * sin((90 - rotationAngle) * pi / 180.0)));
	downRigAngel_X = static_cast<double>(downLeftAngel_X + (this->width() * sin((90 - rotationAngle) * pi / 180.0)));
	downRigAngel_Y = static_cast<double>(downLeftAngel_Y + (this->width() * cos((90 - rotationAngle) * pi / 180.0)));
}

QtRotateRect::QtRotateRect(QRect parent, double rotateAngel, QPoint centerPoint):
	QRect(parent),
	rotationAngle(rotateAngel),
	drawPoint(0,0),
	translatePoint(0,0),
	upLeftAngel_X(0), upLeftAngel_Y(0),
	upRigAngel_X(0), upRigAngel_Y(0),
	downLeftAngel_X(0),
	downLeftAngel_Y(0),
	downRigAngel_X(0),
	downRigAngel_Y(0)
{
	double radius{ sqrt(width() * width() + height() * height()) / 2 };
	double constAngel{ asin((static_cast<double>(width()) / 2) / radius) };
	upLeftAngel_X = static_cast<double>(centerPoint.x() - static_cast<double>(sin(constAngel - rotationAngle * pi / 180.0) * radius));
	upLeftAngel_Y = static_cast<double>(centerPoint.y() - static_cast<double>(cos(constAngel - rotationAngle * pi / 180.0) * radius));
	upRigAngel_X = static_cast<double>((this->width() * sin((90.0 - rotationAngle) * pi / 180.0)) + upLeftAngel_X);
	upRigAngel_Y = static_cast<double>(upLeftAngel_Y + (this->width() * cos((90.0 - rotationAngle) * pi / 180.0)));
	downLeftAngel_X = static_cast<double>(upLeftAngel_X - (this->height() * cos((90.0 - rotationAngle) * pi / 180.0)));
	downLeftAngel_Y = static_cast<double>(upLeftAngel_Y + (this->height() * sin((90.0 - rotationAngle) * pi / 180.0)));
	downRigAngel_X = static_cast<double>(downLeftAngel_X + (this->width() * sin((90.0 - rotationAngle) * pi / 180.0)));
	downRigAngel_Y = static_cast<double>(downLeftAngel_Y + (this->width() * cos((90.0 - rotationAngle) * pi / 180.0)));
}

QtRotateRect::QtRotateRect(int upLeft_X, int upLeft_Y, int width, int height, double rotAngel):
	QRect(0,0,width,height),
	rotationAngle(rotAngel),
	drawPoint(QPoint(0,0)),
	translatePoint(QPoint(0,0)),
	upLeftAngel_X(upLeft_X),
	upLeftAngel_Y(upLeft_Y),
	upRigAngel_X(0),
	upRigAngel_Y(0),
	downLeftAngel_X(0),
	downLeftAngel_Y(0),
	downRigAngel_X(0),
	downRigAngel_Y(0)
{
	upRigAngel_X = static_cast<double>((width * sin((90 - rotationAngle) * pi / 180.0)) + upLeftAngel_X);
	upRigAngel_Y = static_cast<double>(upLeftAngel_Y + (width * cos((90 - rotationAngle) * pi / 180.0)));
	downLeftAngel_X = static_cast<double>(upLeftAngel_X - (height * cos((90 - rotationAngle) * pi / 180.0)));
	downLeftAngel_Y = static_cast<double>(upLeftAngel_Y + (height * sin((90 - rotationAngle) * pi / 180.0)));
	downRigAngel_X = static_cast<double>(downLeftAngel_X + (width * sin((90 - rotationAngle) * pi / 180.0)));
	downRigAngel_Y = static_cast<double>(downLeftAngel_Y + (width * cos((90 - rotationAngle) * pi / 180.0)));
}

QtRotateRect::~QtRotateRect()
{
}



void QtRotateRect::setRotateAngel(double newAngel, QPoint *center_start)
{
	QPoint center{ 0,0 };
	if (center_start == nullptr)
	{
		center.setX(static_cast<int>(getMin_X()) + static_cast<double>(getMax_X() - getMin_X()) / 2 + 1);
		center.setY(static_cast<int>(getMin_Y()) + static_cast<double>(getMax_Y() - getMin_Y()) / 2 + 1);
	}
	else
	{
		center.setX(center_start->x());
		center.setY(center_start->y());
	}
	double buferAngel{ rotationAngle };
	if (newAngel >= 360 )
		rotationAngle = 0;
	else 
	if (newAngel <= 0)
	{
		rotationAngle = 360 + newAngel;
	}
	else if(newAngel>0)
		rotationAngle = newAngel;
	
	double radius{ sqrt(width() * width() + height() * height()) / 2 };
	double constAngel{ asin((static_cast<double>(width()) / 2) / radius) };
	upLeftAngel_X = static_cast<double>(center.x() - static_cast<double>(sin(constAngel - rotationAngle * pi / 180.0) * radius));
	upLeftAngel_Y = static_cast<double>(center.y() - static_cast<double>(cos(constAngel - rotationAngle * pi / 180.0) * radius));
	upRigAngel_X = static_cast<double>((this->width() * sin((90.0 - rotationAngle) * pi / 180.0)) + upLeftAngel_X);
	upRigAngel_Y = static_cast<double>(upLeftAngel_Y + (this->width() * cos((90.0 - rotationAngle) * pi / 180.0)));
	downLeftAngel_X = static_cast<double>(upLeftAngel_X - (this->height() * cos((90.0 - rotationAngle) * pi / 180.0)));
	downLeftAngel_Y = static_cast<double>(upLeftAngel_Y + (this->height() * sin((90.0 - rotationAngle) * pi / 180.0)));
	downRigAngel_X = static_cast<double>(downLeftAngel_X + (this->width() * sin((90.0 - rotationAngle) * pi / 180.0)));
	downRigAngel_Y = static_cast<double>(downLeftAngel_Y + (this->width() * cos((90.0 - rotationAngle) * pi / 180.0)));
}

int QtRotateRect::setRotateAngel(double newAngel, QSize *limitSize, QPoint* center_start)
{
	QPoint center{ 0,0 };
	if (center_start == nullptr)
	{
		center.setX(static_cast<int>(getMin_X()) + static_cast<double>(getMax_X() - getMin_X()) / 2 + 1);
		center.setY(static_cast<int>(getMin_Y()) + static_cast<double>(getMax_Y() - getMin_Y()) / 2 + 1);
	}
	else
	{
		center.setX(center_start->x());
		center.setY(center_start->y());
	}
	double buferAngel{ rotationAngle };
	if (newAngel >= 360)
		rotationAngle = 0;
	else
		if (newAngel < 0)
		{
			rotationAngle = 360 + newAngel;
		}
	else if (newAngel >= 0)
		rotationAngle = newAngel;


	double radius{ sqrt(width() * width() + height() * height()) / 2 };
	double constAngel{ asin((static_cast<double>(width()) / 2) / radius) };
	double buferCor[8];
	buferCor[0] = static_cast<double>(center.x() - static_cast<double>(sin(constAngel - rotationAngle * pi / 180.0) * radius));
	if (buferCor[0] >= limitSize->width() || buferCor[0] < 0)
	{
		rotationAngle = buferAngel;
		return -1;
	}
	buferCor[1] = static_cast<double>(center.y() - static_cast<double>(cos(constAngel - rotationAngle * pi / 180.0) * radius));
	if (buferCor[1] >= limitSize->height() || buferCor[1] < 0)
	{
		rotationAngle = buferAngel;
		return -1;
	}
	buferCor[2] = static_cast<double>((this->width() * sin((90.0 - rotationAngle) * pi / 180.0)) + buferCor[0]);
	if (buferCor[2] >= limitSize->width() || buferCor[2] < 0)
	{
		rotationAngle = buferAngel;
		return -1;
	}
	buferCor[3] = static_cast<double>(buferCor[1] + (this->width() * cos((90.0 - rotationAngle) * pi / 180.0)));
	if (buferCor[3] >= limitSize->height() || buferCor[3] < 0)
	{
		rotationAngle = buferAngel;
		return -1;
	}
	buferCor[4] = static_cast<double>(buferCor[0] - (this->height() * cos((90.0 - rotationAngle) * pi / 180.0)));
	if (buferCor[4] >= limitSize->width() || buferCor[4] < 0)
	{
		rotationAngle = buferAngel;
		return -1;
	}
	buferCor[5] = static_cast<double>(buferCor[1] + (this->height() * sin((90.0 - rotationAngle) * pi / 180.0)));
	if (buferCor[5] >= limitSize->height() || buferCor[5] < 0)
	{
		rotationAngle = buferAngel;
		return -1;
	}
	buferCor[6] = static_cast<double>(buferCor[4] + (this->width() * sin((90.0 - rotationAngle) * pi / 180.0)));
	if (buferCor[6] >= limitSize->width() || buferCor[6] < 0)
	{
		rotationAngle = buferAngel;
		return -1;
	}
	buferCor[7] = static_cast<double>(buferCor[5] + (this->width() * cos((90.0 - rotationAngle) * pi / 180.0)));
	if (buferCor[7] >= limitSize->height() || buferCor[7] < 0)
	{
		rotationAngle = buferAngel;
		return -1;
	}
	upLeftAngel_X = buferCor[0];
	upLeftAngel_Y = buferCor[1];
	upRigAngel_X = buferCor[2];
	upRigAngel_Y = buferCor[3];
	downLeftAngel_X = buferCor[4];
	downLeftAngel_Y = buferCor[5];
	downRigAngel_X = buferCor[6];
	downRigAngel_Y = buferCor[7];
	return 0;
}

int QtRotateRect::resetAngel(QSize* limitSize)
{
	if (rotationAngle != 0.0)
	{
		QPoint center{ 0,0 };
		center.setX(static_cast<int>(getMin_X()) + static_cast<double>(getMax_X() - getMin_X()) / 2 + 1);
		center.setY(static_cast<int>(getMin_Y()) + static_cast<double>(getMax_Y() - getMin_Y()) / 2 + 1);
		double buferAngel{ rotationAngle };
		rotationAngle = 0.0;
		double radius{ sqrt(width() * width() + height() * height()) / 2 };
		double constAngel{ asin((static_cast<double>(width()) / 2) / radius) };
		double buferCor[8];
		buferCor[0] = static_cast<double>(center.x() - static_cast<double>(sin(constAngel - rotationAngle * pi / 180.0) * radius));
		if (buferCor[0] >= limitSize->width() || buferCor[0] < 0)
		{
			rotationAngle = buferAngel;
			return -1;
		}
		buferCor[1] = static_cast<double>(center.y() - static_cast<double>(cos(constAngel - rotationAngle * pi / 180.0) * radius));
		if (buferCor[1] >= limitSize->height() || buferCor[1] < 0)
		{
			rotationAngle = buferAngel;
			return -1;
		}
		buferCor[2] = static_cast<double>((this->width() * sin((90.0 - rotationAngle) * pi / 180.0)) + buferCor[0]);
		if (buferCor[2] >= limitSize->width() || buferCor[2] < 0)
		{
			rotationAngle = buferAngel;
			return -1;
		}
		buferCor[3] = static_cast<double>(buferCor[1] + (this->width() * cos((90.0 - rotationAngle) * pi / 180.0)));
		if (buferCor[3] >= limitSize->height() || buferCor[3] < 0)
		{
			rotationAngle = buferAngel;
			return -1;
		}
		buferCor[4] = static_cast<double>(buferCor[0] - (this->height() * cos((90.0 - rotationAngle) * pi / 180.0)));
		if (buferCor[4] >= limitSize->width() || buferCor[4] < 0)
		{
			rotationAngle = buferAngel;
			return -1;
		}
		buferCor[5] = static_cast<double>(buferCor[1] + (this->height() * sin((90.0 - rotationAngle) * pi / 180.0)));
		if (buferCor[5] >= limitSize->height() || buferCor[5] < 0)
		{
			rotationAngle = buferAngel;
			return -1;
		}
		buferCor[6] = static_cast<double>(buferCor[4] + (this->width() * sin((90.0 - rotationAngle) * pi / 180.0)));
		if (buferCor[6] >= limitSize->width() || buferCor[6] < 0)
		{
			rotationAngle = buferAngel;
			return -1;
		}
		buferCor[7] = static_cast<double>(buferCor[5] + (this->width() * cos((90.0 - rotationAngle) * pi / 180.0)));
		if (buferCor[7] >= limitSize->height() || buferCor[7] < 0)
		{
			rotationAngle = buferAngel;
			return -1;
		}
		upLeftAngel_X = buferCor[0];
		upLeftAngel_Y = buferCor[1];
		upRigAngel_X = buferCor[2];
		upRigAngel_Y = buferCor[3];
		downLeftAngel_X = buferCor[4];
		downLeftAngel_Y = buferCor[5];
		downRigAngel_X = buferCor[6];
		downRigAngel_Y = buferCor[7];
	}
	return 0;
}

void QtRotateRect::setCenter(QPoint* center)
{
	int buferH{ height() };
	int buferW{ width() };
	int deltaX{ QRect::center().x() - center->x() };
	int deltaY{ QRect::center().y() - center->y() };
	setX(QRect::x() - deltaX);
	setY(QRect::y() - deltaY);
	setWidth(buferW);
	setHeight(buferH);
}

double QtRotateRect::getRotateAngel(bool inRad )
{
	if (!inRad)
		return rotationAngle;
	else
		return rotationAngle * pi / 180;
}

void QtRotateRect::setDrowPoint(QPoint drPoint)
{
	drawPoint = drPoint;
}

QPoint QtRotateRect::getDrawPoint()
{
	return drawPoint;
}

void QtRotateRect::setTranslatePoint(QPoint transltPont)
{
	translatePoint = transltPont;
}

void QtRotateRect::translateTranslatePoint(int dx, int dy)
{
	//translatePoint.setX(translatePoint.x() + dx);
	//translatePoint.setY(translatePoint.y() + dy);
	upLeftAngel_X+=dx;
	upLeftAngel_Y+=dy;
	upRigAngel_X+=dx;
	upRigAngel_Y+=dy;
	downLeftAngel_X+=dx;
	downLeftAngel_Y+=dy;
	downRigAngel_X+=dx;
	downRigAngel_Y+=dy;
}

//QPoint QtRotateRect::getTranslatePoint()
//{
//	return translatePoint;
//}

bool QtRotateRect::contains(QPoint point)
{
	int upLeftAngel_X{ static_cast<int>(this->width() -ceil( cos(rotationAngle) * this->width())) + this->x() };
	int upLeftAngel_Y{ static_cast<int>(this->y() - ceil(sin(rotationAngle) * this->height())) };
	int upRidAngel_X{ static_cast<int>(ceil(this->width() * cos(rotationAngle)) + upLeftAngel_X) };
	int upRidAngel_Y{ static_cast<int>(this->y() + ceil(sin(rotationAngle) * this->height())) };
	if (point.x() > upLeftAngel_X && point.x() < upRidAngel_X && point.y() > (-((upLeftAngel_Y - upRidAngel_Y) * point.x() + (upLeftAngel_X * upRidAngel_Y - upRidAngel_X * upLeftAngel_Y)) / (upRidAngel_X - upLeftAngel_X)))
	{
		return true;
	}
	else
		return false;
}

bool QtRotateRect::contains(int x, int y)
{
	/*if (((static_cast<int>(ceil(upLeftAngel_X)) == static_cast<int>(ceil(upRidAngel_X)) || static_cast<int>(ceil(downLeftAngel_X)) == static_cast<int>(ceil(downRidAngel_X)))||(static_cast<int>(ceil(upLeftAngel_Y)) == static_cast<int>(ceil(downLeftAngel_Y)) || static_cast<int>(ceil(upRidAngel_Y)) == static_cast<int>(ceil(downRidAngel_Y))))&&((rotationAngle>80&& rotationAngle<100)||(rotationAngle > 260 && rotationAngle < 280)))
	{
		return QRect(downLeftAngel_X, downLeftAngel_Y, this->height()+2, this->width()+2).contains(x, y);
	}
	else if (((static_cast<int>(ceil(upLeftAngel_Y)) == static_cast<int>(ceil(downLeftAngel_Y)) || static_cast<int>(ceil(upRidAngel_Y))== static_cast<int>(ceil(downRidAngel_Y))) || (static_cast<int>(ceil(upLeftAngel_Y)) == static_cast<int>(ceil(downLeftAngel_Y)) || static_cast<int>(ceil(upRidAngel_Y)) == static_cast<int>(ceil(downRidAngel_Y)))) && ((rotationAngle >= 337.5 && rotationAngle < 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle > 170 && rotationAngle < 190)))
	{
		return QRect::contains(x, y);
	}
	else*/
	/*double denominator{ 1.0 };
	if (upRigAngel_X / upLeftAngel_X < 0.1)
		denominator*/
	if (y >= (upLeftAngel_Y + ((x - upLeftAngel_X) * (upRigAngel_Y - upLeftAngel_Y)) / (upRigAngel_X - upLeftAngel_X)) &&
			y <= (downLeftAngel_Y + ((x - downLeftAngel_X) * (downRigAngel_Y - downLeftAngel_Y)) / (downRigAngel_X - downLeftAngel_X)) &&
			x >=(upLeftAngel_X + ((y - upLeftAngel_Y) * (downLeftAngel_X - upLeftAngel_X)) / (downLeftAngel_Y - upLeftAngel_Y)) &&
			x <= (upRigAngel_X + ((y - upRigAngel_Y) * (downRigAngel_X - upRigAngel_X)) / (downRigAngel_Y - upRigAngel_Y)) && (rotationAngle < 90 || rotationAngle > 270))
	{
		return true;
	}
	else if (x <= (downLeftAngel_X + ((y - downLeftAngel_Y) * (upLeftAngel_X - downLeftAngel_X)) / (upLeftAngel_Y - downLeftAngel_Y)) &&
			x >=(downRigAngel_X + ((y - downRigAngel_Y) * (upRigAngel_X - downRigAngel_X)) / (upRigAngel_Y - downRigAngel_Y)) &&
			y >=(downRigAngel_Y + ((x - downRigAngel_X) * (downLeftAngel_Y - downRigAngel_Y)) / (downLeftAngel_X - downRigAngel_X)) &&
			y <=(upRigAngel_Y + ((x - upRigAngel_X) * (upLeftAngel_Y - upRigAngel_Y)) / (upLeftAngel_X - upRigAngel_X)) && (rotationAngle > 90 || rotationAngle < 270))
	{
		return true;
	}
	else
		return false;
}

int QtRotateRect::getUpLeft_X()
{
	return static_cast<int>(round(upLeftAngel_X));
}

int QtRotateRect::getUpLeft_Y()
{
	return static_cast<int>(round(upLeftAngel_Y));
}

int QtRotateRect::getDownLeft_X()
{
	return static_cast<int>(round(downLeftAngel_X));
}

int QtRotateRect::getDownLeft_Y()
{
	return static_cast<int>(round(downLeftAngel_Y));
}

int QtRotateRect::getUpRigth_X()
{
	return static_cast<int>(round(upRigAngel_X));
}

int QtRotateRect::getUpRigth_Y()
{
	return static_cast<int>(round(upRigAngel_Y));
}

int QtRotateRect::getDownRigth_X()
{
	return static_cast<int>(round(downRigAngel_X));
}

int QtRotateRect::getDownRigth_Y()
{
	return static_cast<int>(round(downRigAngel_Y));
}

int QtRotateRect::getMax_X()
{
	if (upLeftAngel_X > downLeftAngel_X && upLeftAngel_X > upRigAngel_X && upLeftAngel_X > downRigAngel_X)
	{
		return upLeftAngel_X;
	}
	if (downLeftAngel_X > upLeftAngel_X && downLeftAngel_X > upRigAngel_X && downLeftAngel_X > downRigAngel_X)
	{
		return downLeftAngel_X;
	}
	if (upRigAngel_X > downLeftAngel_X && upRigAngel_X > upLeftAngel_X && upRigAngel_X > downRigAngel_X)
	{
		return upRigAngel_X;
	}
	else
		return downRigAngel_X;
}

int QtRotateRect::getMin_X()
{
	if (upLeftAngel_X < downLeftAngel_X && upLeftAngel_X < upRigAngel_X && upLeftAngel_X < downRigAngel_X)
	{
		return upLeftAngel_X;
	}
	else if (downLeftAngel_X < upLeftAngel_X && downLeftAngel_X < upRigAngel_X && downLeftAngel_X < downRigAngel_X)
	{
		return downLeftAngel_X;
	}
	else if (upRigAngel_X < downLeftAngel_X && upRigAngel_X < upLeftAngel_X && upRigAngel_X < downRigAngel_X)
	{
		return upRigAngel_X;
	}
	else
		return downRigAngel_X;
}

int QtRotateRect::getMax_Y()
{
	if (upLeftAngel_Y > downLeftAngel_Y && upLeftAngel_Y > upRigAngel_Y && upLeftAngel_Y > downRigAngel_Y)
	{
		return upLeftAngel_Y;
	}
	if (downLeftAngel_Y > upLeftAngel_Y && downLeftAngel_Y > upRigAngel_Y && downLeftAngel_Y > downRigAngel_Y)
	{
		return downLeftAngel_Y;
	}
	if (upRigAngel_Y > downLeftAngel_Y && upRigAngel_Y > upLeftAngel_Y && upRigAngel_Y > downRigAngel_Y)
	{
		return upRigAngel_Y;
	}
	else
		return downRigAngel_Y;
}

int QtRotateRect::getMin_Y()
{
	if (upLeftAngel_Y < downLeftAngel_Y && upLeftAngel_Y < upRigAngel_Y && upLeftAngel_Y < downRigAngel_Y)
	{
		return upLeftAngel_Y;
	}
	if (downLeftAngel_Y < upLeftAngel_Y && downLeftAngel_Y < upRigAngel_Y && downLeftAngel_Y < downRigAngel_Y)
	{
		return downLeftAngel_Y;
	}
	if (upRigAngel_Y < downLeftAngel_Y && upRigAngel_Y < upLeftAngel_Y && upRigAngel_Y < downRigAngel_Y)
	{
		return upRigAngel_Y;
	}
	else
		return downRigAngel_Y;
}

int QtRotateRect::getLeftAngel()
{
	if (upLeftAngel_X < downLeftAngel_X && upLeftAngel_X < upRigAngel_X && upLeftAngel_X < downRigAngel_X)
	{
		return 0; //upLeftAngel_Y
	}
	else if (downLeftAngel_X < upLeftAngel_X && downLeftAngel_X < upRigAngel_X && downLeftAngel_X < downRigAngel_X)
	{
		return 3; //downLeftAngel_Y
	}
	else if (upRigAngel_X < downLeftAngel_X && upRigAngel_X < upLeftAngel_X && upRigAngel_X < downRigAngel_X)
	{
		return 1; //upRigAngel_Y
	}
	else
		return 2; //downRigAngel_Y
}

int QtRotateRect::getRigthAngel()
{
	if (upLeftAngel_X > downLeftAngel_X && upLeftAngel_X > upRigAngel_X && upLeftAngel_X > downRigAngel_X)
	{
		return 0; //upLeftAngel_Y
	}
	if (downLeftAngel_X > upLeftAngel_X && downLeftAngel_X > upRigAngel_X && downLeftAngel_X > downRigAngel_X)
	{
		return 3; //downLeftAngel_Y
	}
	if (upRigAngel_X > downLeftAngel_X && upRigAngel_X > upLeftAngel_X && upRigAngel_X > downRigAngel_X)
	{
		return 1; //upRigAngel_Y
	}
	else
		return 2; //downRigAngel_Y
}

int QtRotateRect::getTopAngel()
{
	if (upLeftAngel_Y < downLeftAngel_Y && upLeftAngel_Y < upRigAngel_Y && upLeftAngel_Y < downRigAngel_Y)
	{
		return 0; //upLeftAngel_Y
	}
	if (downLeftAngel_Y < upLeftAngel_Y && downLeftAngel_Y < upRigAngel_Y && downLeftAngel_Y < downRigAngel_Y)
	{
		return 3; //downLeftAngel_Y
	}
	if (upRigAngel_Y < downLeftAngel_Y && upRigAngel_Y < upLeftAngel_Y && upRigAngel_Y < downRigAngel_Y)
	{ 
		return 1; //upRigAngel_Y
	}
	else
		return 2; //downRigAngel_Y
}

int QtRotateRect::getLowAngel()
{
	if (upLeftAngel_Y > downLeftAngel_Y && upLeftAngel_Y > upRigAngel_Y && upLeftAngel_Y > downRigAngel_Y)
	{
		return 0; //upLeftAngel_Y
	}
	if (downLeftAngel_Y > upLeftAngel_Y && downLeftAngel_Y > upRigAngel_Y && downLeftAngel_Y > downRigAngel_Y)
	{ 
		return 3; //downLeftAngel_Y
	}
	if (upRigAngel_Y > downLeftAngel_Y && upRigAngel_Y > upLeftAngel_Y && upRigAngel_Y > downRigAngel_Y)
	{
		return 1; //upRigAngel_Y
	}
	else
		return 2; //downRigAngel_Y
}


int QtRotateRect::setX(int newX, QSize *limitSize)
{
	int dx{ this->x() - newX };
	double bufer[4];
	bufer[0]= upLeftAngel_X - cos(rotationAngle * pi / 180) * dx;
	if (bufer[0] > limitSize->width() || bufer[0] < 0)
		return -1;
	bufer[1] = upLeftAngel_Y - sin(rotationAngle * pi / 180) * dx;
	if (bufer[1] > limitSize->height() || bufer[1] < 0)
		return -1;
	bufer[2] = downLeftAngel_X - cos(rotationAngle * pi / 180) * dx;
	if (bufer[2] > limitSize->width() || bufer[2] < 0)
		return -1;
	bufer[3] = downLeftAngel_Y - sin(rotationAngle * pi / 180) * dx;
	if (bufer[3] > limitSize->height() || bufer[3] < 0)
		return -1;
	QRect::setX(newX);
	upLeftAngel_X = bufer[0];
	upLeftAngel_Y = bufer[1];
	downLeftAngel_X = bufer[2];
	downLeftAngel_Y = bufer[3];
	return 0;
}

void QtRotateRect::setX(int newX)
{
	int dx{ this->x() - newX };
	QRect::setX(newX);
	downLeftAngel_Y -= sin(rotationAngle * pi / 180) * dx;
	downLeftAngel_X -= cos(rotationAngle * pi / 180) * dx;
	upLeftAngel_Y -= sin(rotationAngle * pi / 180) * dx;
	upLeftAngel_X -= cos(rotationAngle * pi / 180) * dx;
}

int QtRotateRect::setY(int newY, QSize* limitSize)
{
	int dy{ this->y() - newY };
	double bufer[4];
	bufer[0] = upLeftAngel_X + sin(rotationAngle * pi / 180) * dy;
	if (bufer[0] > limitSize->width() || bufer[0] < 0)
		return -1;
	bufer[1] = upLeftAngel_Y - cos(rotationAngle * pi / 180) * dy;
	if (bufer[1] > limitSize->height() || bufer[1] < 0)
		return -1;
	bufer[2] = upRigAngel_X + sin(rotationAngle * pi / 180) * dy;
	if (bufer[2] > limitSize->width() || bufer[2] < 0)
		return -1;
	bufer[3] = upRigAngel_Y - cos(rotationAngle * pi / 180) * dy;
	if (bufer[3] > limitSize->height() || bufer[3] < 0)
		return -1;
	QRect::setY(newY);
	upLeftAngel_X = bufer[0];
	upLeftAngel_Y = bufer[1];
	upRigAngel_X = bufer[2];
	upRigAngel_Y = bufer[3];
	return 0;
}

void QtRotateRect::setY(int newY)
{
	int dy{ this->y() - newY };
	QRect::setY(newY);
	upLeftAngel_X += sin(rotationAngle * pi / 180) * dy;
	upLeftAngel_Y -= cos(rotationAngle * pi / 180) * dy;
	upRigAngel_X += sin(rotationAngle * pi / 180) * dy;
	upRigAngel_Y -= cos(rotationAngle * pi / 180) * dy;
}

int QtRotateRect::setWidth(int newWidth, QSize* limitSize)
{
	int dw{ newWidth - this->width() };
	double bufer[4];
	bufer[0] = downRigAngel_X + cos(rotationAngle * pi / 180) * dw;
	if (bufer[0] > limitSize->width() || bufer[0] < 0)
		return -1;
	bufer[1] = downRigAngel_Y + sin(rotationAngle * pi / 180) * dw;
	if (bufer[1] > limitSize->height() || bufer[1] < 0)
		return -1;
	bufer[2] = upRigAngel_X + cos(rotationAngle * pi / 180) * dw;
	if (bufer[2] > limitSize->width() || bufer[2] < 0)
		return -1;
	bufer[3] = upRigAngel_Y + sin(rotationAngle * pi / 180) * dw;
	if (bufer[3] > limitSize->height() || bufer[3] < 0)
		return -1;
	QRect::setWidth(newWidth);
	downRigAngel_X = bufer[0];
	downRigAngel_Y = bufer[1];
	upRigAngel_X = bufer[2];
	upRigAngel_Y = bufer[3];
	return 0;
}

void QtRotateRect::setWidth(int newWidth)
{
	int dw{ newWidth - this->width() };
	QRect::setWidth(newWidth);
	downRigAngel_X += cos(rotationAngle * pi / 180) * dw;
	downRigAngel_Y += sin(rotationAngle * pi / 180) * dw;
	upRigAngel_X += cos(rotationAngle * pi / 180) * dw;
	upRigAngel_Y += sin(rotationAngle * pi / 180) * dw;
}

int QtRotateRect::setHeight(int newHeigth, QSize* limitSize)
{
	int dh{ newHeigth - this->height() };
	double bufer[4];
	bufer[0] = downLeftAngel_X - sin(rotationAngle * pi / 180) * dh;
	if (bufer[0] > limitSize->width() || bufer[0] < 0)
		return -1;
	bufer[1] = downLeftAngel_Y + cos(rotationAngle * pi / 180) * dh;
	if (bufer[1] > limitSize->height() || bufer[1] < 0)
		return -1;
	bufer[2] = downRigAngel_X - sin(rotationAngle * pi / 180) * dh;
	if (bufer[2] > limitSize->width() || bufer[2] < 0)
		return -1;
	bufer[3] = downRigAngel_Y + cos(rotationAngle * pi / 180) * dh;
	if (bufer[3] > limitSize->height() || bufer[3] < 0)
		return -1;
	QRect::setHeight(newHeigth);
	downLeftAngel_X = bufer[0];
	downLeftAngel_Y = bufer[1];
	downRigAngel_X = bufer[2];
	downRigAngel_Y = bufer[3];
	return 0;
}

void QtRotateRect::setHeight(int newHeigth)
{
	int dh{ newHeigth - this->height() };
	QRect::setHeight(newHeigth);
	downLeftAngel_X -= sin(rotationAngle * pi / 180) * dh;
	downLeftAngel_Y += cos(rotationAngle * pi / 180) * dh;
	downRigAngel_X -= sin(rotationAngle * pi / 180) * dh;
	downRigAngel_Y += cos(rotationAngle * pi / 180) * dh;
}

int QtRotateRect::getUpY(int x,int y)
{
	if (static_cast<int>(round(upRigAngel_X)) - static_cast<int>(round(upLeftAngel_X)) == 0)
		return y;
	else
		return upLeftAngel_Y + ((x - upLeftAngel_X) * (upRigAngel_Y - upLeftAngel_Y)) / (upRigAngel_X - upLeftAngel_X);
}

int QtRotateRect::getDownY(int x)
{
	return downRigAngel_Y + ((x - downRigAngel_X) * (downLeftAngel_Y - downRigAngel_Y)) / (downLeftAngel_X - downRigAngel_X);
}

int QtRotateRect::getUpX(int y, int x)
{
	if (static_cast<int>(round(upRigAngel_Y)) - static_cast<int>(round(upLeftAngel_Y)) == 0)
		return x;
	else
		return upLeftAngel_X+((y-upLeftAngel_Y)*(upRigAngel_X-upLeftAngel_X))/(upRigAngel_Y-upLeftAngel_Y);
}

int QtRotateRect::getDownX(int y)
{
	return downLeftAngel_X+((y-downLeftAngel_Y)*(downRigAngel_X-downLeftAngel_X))/(downRigAngel_Y-downLeftAngel_Y);
}

int QtRotateRect::getLeftX(int y)
{
	return downLeftAngel_X + ((y - downLeftAngel_Y) * (upLeftAngel_X - downLeftAngel_X)) / (upLeftAngel_Y - downLeftAngel_Y);
}

int QtRotateRect::getRigthX(int y)
{
	return downRigAngel_X + ((y - downRigAngel_Y) * (upRigAngel_X - downRigAngel_X)) / (upRigAngel_Y - downRigAngel_Y);
}

int QtRotateRect::getRigthY(int x)
{
	return upRigAngel_Y + ((x - upRigAngel_X) * (downRigAngel_Y - upRigAngel_Y) / (downRigAngel_X - upRigAngel_X));
}

int QtRotateRect::getLeftY(int x)
{
	return upLeftAngel_Y + ((x - upLeftAngel_X) * (downLeftAngel_Y - upLeftAngel_Y) / (downLeftAngel_X - upLeftAngel_X));
}

double QtRotateRect::getDiagonal()
{
	return sqrt(width() * width() + height() * height());
}

void QtRotateRect::resizeRect(QPoint const imgPoint, QPoint const globalImgPoint, QPoint const firstPoint, QSize* boundingSize)
{

	int x_lablG{ globalImgPoint.x() };
	int y_lablG{ globalImgPoint.y() };
	int x_labl{ imgPoint.x() };
	int y_labl{ imgPoint.y() };
	int f_x_pixMap{ firstPoint.x() };
	int f_y_pixMap{ firstPoint.y() };

	if (getResizeType() == Resize_X)
	{
		double dx{ 0 };
		bool dx_isSet{ false };
		if (((rotationAngle >= 67.5 && rotationAngle < 112.5) && y_labl < getRigthY(x_labl))
			|| ((rotationAngle >= 247.5 && rotationAngle < 292.5) && y_labl > getRigthY(x_labl)))
		{
			dx = sin(getRotateAngel(true)) * (y_labl - getLeftY(x_labl));
		}
		else if ((x_labl < getRigthX(y_labl) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (x_labl > getRigthX(y_labl) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5))))
		{
			dx = cos(getRotateAngel(true)) * (x_labl - getLeftX(y_labl));
		}
		else
		{
			setX(x() + width() - 1);
			dx_isSet = true;
		}
		if (!dx_isSet)
		{
			setX(x() + static_cast<int>(dx), boundingSize);
			if (width() <= 0)
			{
				setX(x() + width() - 1);
			}
		}
	}
	else if (getResizeType() == Resize_Width)
	{
		double dw{ 0 };
		bool widt_isSet{ false };
		if (((rotationAngle >= 67.5 && rotationAngle < 112.5) && y_labl > getLeftY(x_labl))
			|| ((rotationAngle >= 247.5 && rotationAngle < 292.5) && y_labl < getLeftY(x_labl)))
		{
			dw = sin(getRotateAngel(true)) * (y_labl - getRigthY(x_labl));
		}
		else if ((x_labl > getLeftX(y_labl) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (x_labl < getLeftX(y_labl) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5))))
		{
			dw = cos(getRotateAngel(true)) * (x_labl - getRigthX(y_labl));
		}
		else
		{
			setWidth(1);
			widt_isSet = true;
		}
		if (!widt_isSet)
		{
			setWidth(width() + static_cast<int>(dw), boundingSize);
			if (width() <= 0)
			{
				setWidth(1);
			}
		}
	}

	if (getResizeType() == Resize_Y)
	{
		double dy_first{ 0 };

		bool dy_isSet{ false };
		bool dy_isMinus{ false };
		if (((rotationAngle >= 67.5 && rotationAngle < 112.5) && x_labl > getDownX(y_labl))
			|| ((rotationAngle >= 247.5 && rotationAngle < 292.5) && x_labl < getDownX(y_labl)))
		{
			dy_first = sin(getRotateAngel(true)) * (x_labl - getUpX(y_labl));
			dy_isMinus = true;
		}
		else if ((y_labl < getDownY(x_labl) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (y_labl > getDownY(x_labl) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5))))
		{
			dy_first = cos(getRotateAngel(true)) * (y_labl - getUpY(x_labl));
		}
		else
		{
			setY(y() + height() - 1);
			dy_isSet = true;
		}
		if (!dy_isSet)
		{
			if (dy_isMinus)
			{
				setY(y() - static_cast<int>(dy_first), boundingSize);
			}
			else
			{
				setY(y() + static_cast<int>(dy_first), boundingSize);
			}
		}
	}
	else if (getResizeType() == Resize_Height)
	{
		bool dh_isSet{ false };
		bool dh_isMinus{ false };
		double dh_first{ 0 };
		if (((rotationAngle >= 67.5 && rotationAngle < 112.5) && x_labl < getUpX(y_labl))
			|| ((rotationAngle >= 247.5 && rotationAngle < 292.5) && x_labl > getUpX(y_labl)))
		{
			dh_first = sin(getRotateAngel(true)) * (x_labl - getDownX(y_labl));
			dh_isMinus = true;
		}
		else if ((y_labl > getUpY(x_labl) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (y_labl < getUpY(x_labl) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5))))
		{
			dh_first = cos(getRotateAngel(true)) * (y_labl - getDownY(x_labl));
		}
		else
		{
			setHeight(1);
			dh_isSet = true;
		}
		if (!dh_isSet)
		{
			if (dh_isMinus)
			{
				setHeight(height() - static_cast<int>(dh_first), boundingSize);
			}
			else
			{
				setHeight(height() + static_cast<int>(dh_first), boundingSize);
			}
		}
	}
	else if (getResizeType() == Resize_XAndY)
	{
		if (((y_labl < getDownY(x_lablG) && x_labl < getRigthX(y_lablG)) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (f_x_pixMap > getDownX(y_lablG) && y_labl < getRigthY(x_lablG) && x_labl > getDownX(y_lablG) && (rotationAngle >= 67.5 && rotationAngle < 112.5))
			|| (f_x_pixMap < getDownX(y_lablG) && y_labl > getRigthY(x_lablG) && x_labl < getDownX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
			|| ((y_labl > getDownY(x_lablG) && x_labl > getRigthX(y_lablG)) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
		{
			double dy{ 0 };
			double dx{ 0 };
			if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
			{
				dy = cos(getRotateAngel(true)) * (y_labl - getUpLeft_Y());
				dx = cos(getRotateAngel(true)) * (x_labl - getUpLeft_X());
			}
			else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
			{
				dy = -sin(getRotateAngel(true)) * (x_labl - getUpLeft_X());
				dx = sin(getRotateAngel(true)) * (y_labl - getUpLeft_Y());
			}
			setY(y() + static_cast<int>(dy), boundingSize);
			setX(x() + static_cast<int>(dx), boundingSize);
			if (height() <= 0)
			{
				setY(y() + height() - 1);
			}
			if (width() <= 0)
			{
				setX(x() + width() - 1);
			}
		}
		else
			if ((y_labl >= getDownY(x_lablG) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
				|| (f_x_pixMap > getDownX(y_lablG) && x_labl <= getDownX(y_lablG) + 1 && (rotationAngle >= 67.5 && rotationAngle < 112.5))
				|| (f_x_pixMap < getDownX(y_lablG) && x_labl >= getDownX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
				|| (y_labl <= getDownY(x_lablG) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
			{
				setY(y() + height() - 1);
				double dx{ 0 };
				if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
				{
					dx = cos(getRotateAngel(true)) * (x_labl - getUpLeft_X());
				}
				else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
				{
					dx = sin(getRotateAngel(true)) * (y_labl - getUpLeft_Y());
				}

				if (getDownRigth_Y() >= getUpLeft_Y() && getDownRigth_X() >= getUpLeft_X())
				{
					setX(x() + static_cast<int>(dx), boundingSize);
					if ((getDownRigth_X() < getUpLeft_X() || width() <= 0))
					{
						setX(x() + width() - 1);
					}
				}
				else
				if (getDownRigth_Y() >= getUpLeft_Y() && getDownRigth_X() < getUpLeft_X())
				{
					setX(x() + static_cast<int>(dx), boundingSize);
					if (getDownRigth_Y() < getUpLeft_Y() || width() <= 0)
					{
						setX(x() + width() - 1);
					}
				}
				else
				if (getDownRigth_Y() < getUpLeft_Y() && getDownRigth_X() < getUpLeft_X())
				{
					setX(x() + static_cast<int>(dx), boundingSize);
					if (getDownRigth_X() > getUpLeft_X() || width() <= 0)
					{
						setX(x() + width() - 1);
					}
				}
				else
				if (getDownRigth_Y() < getUpLeft_Y() && getDownRigth_X() >= getUpLeft_X())
				{
					setX(x() + static_cast<int>(dx), boundingSize);
					if (getDownRigth_Y() > getUpLeft_Y() || width() <= 0)
					{
						setX(x() + width() - 1);
					}
				}
			}
			else
				if ((x_labl >= getRigthX(y_lablG) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
					|| (f_x_pixMap > getDownX(y_lablG) && x_labl >= getDownRigth_X() && (rotationAngle >= 67.5 && rotationAngle < 112.5))
					|| (f_x_pixMap < getDownX(y_lablG) && x_labl <= getDownRigth_X() && (rotationAngle >= 247.5 && rotationAngle < 292.5))
					|| (x_labl <= getRigthX(y_lablG) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
				{
					setX(x() + width() - 1);
					double dy{ 0 };
					bool dy_isMinus{ false };
					if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
					{
						dy = cos(getRotateAngel(true)) * (y_labl - getUpLeft_Y());
					}
					else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
					{
						dy = -sin(getRotateAngel(true)) * (x_labl - getUpLeft_X());
						dy_isMinus = true;
					}
					if (getDownRigth_Y() >= getUpLeft_Y() && getDownRigth_X() >= getUpLeft_X())
					{
						setY(y() + static_cast<int>(dy), boundingSize);
						if (getDownRigth_Y() < getUpLeft_Y() || height() <= 0)
						{
							setY(y() + height() - 1);
						}
					}
					else
					if (getDownRigth_Y() >= getUpLeft_Y() && getDownRigth_X() < getUpLeft_X())
					{
						setY(y() + static_cast<int>(dy), boundingSize);
						if (getDownRigth_X() > getUpLeft_X() || height() <= 0)
						{
							setY(y() + height() - 1);
						}
					}
					else
					if (getDownRigth_Y() < getUpLeft_Y() && getDownRigth_X() < getUpLeft_X())
					{
						setY(y() + static_cast<int>(dy), boundingSize);
						if (getDownRigth_Y() > getUpLeft_Y() || height() <= 0)
						{
							setY(y() + height() - 1);
						}
					}
					else
					if (getDownRigth_Y() < getUpLeft_Y() && getDownRigth_X() >= getUpLeft_X())
					{
						setY(y() + static_cast<int>(dy), boundingSize);
						if (getDownRigth_X() < getUpLeft_X() || height() <= 0)
						{
							setY(y() + height() - 1);
						}
					}
				}
				else
				{
					setX(x() + width() - 1);
					setY(y() + height() - 1);
				}
	}
	else if (getResizeType() == Resize_HeigthAndWidth)
	{
		if (((y_labl > getUpY(x_lablG) && x_labl > getLeftX(y_lablG)) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (f_x_pixMap < getUpX(y_lablG) && y_labl > getLeftY(x_lablG) && x_labl < getUpX(y_lablG) && (rotationAngle >= 67.5 && rotationAngle < 112.5))
			|| (f_x_pixMap > getUpX(y_lablG) && y_labl < getLeftY(x_lablG) && x_labl > getUpX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
			|| ((y_labl < getUpY(x_lablG) && x_labl < getLeftX(y_lablG)) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
		{
			double dh{ 0 };
			double dw{ 0 };

			if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
			{
				dh = cos(getRotateAngel(true)) * (y_labl - getDownY(x_labl));
				dw = cos(getRotateAngel(true)) * (x_labl - getRigthX(y_labl));
			}
			else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
			{
				dh = -sin(getRotateAngel(true)) * (x_labl - getDownX(y_labl));
				dw = sin(getRotateAngel(true)) * (y_labl - getRigthY(x_labl));
			}
			setHeight(height() + static_cast<int>(dh), boundingSize);
			setWidth(width() + static_cast<int>(dw), boundingSize);
			if (height() <= 0)
			{
				setHeight(1);
			}
			if (width() <= 0)
			{
				setWidth(1);
			}
		}
		else
			if ((y_labl <= getUpY(x_lablG) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
				|| (f_x_pixMap < getUpX(y_lablG) && x_labl >= getUpX(y_lablG) + 1 && (rotationAngle >= 67.5 && rotationAngle < 112.5))
				|| (f_x_pixMap > getUpX(y_lablG) && x_labl <= getUpX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
				|| (y_labl >= getUpY(x_lablG) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
			{
				setHeight(1);
				double dw{ 0 };
				if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
				{
					dw = cos(getRotateAngel(true)) * (x_labl - getRigthX(y_labl));
				}
				else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
				{
					dw = sin(getRotateAngel(true)) * (y_labl - getRigthY(x_labl));
				}
				setWidth(width() + static_cast<int>(dw), boundingSize);
				if (width() <= 0)
				{
					setWidth(1);
				}
			}
			else
			if ((x_labl <= getLeftX(y_lablG) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
				|| (f_x_pixMap < getUpX(y_lablG) && x_labl <= getUpX(y_lablG) && (rotationAngle >= 67.5 && rotationAngle < 112.5))
				|| (f_x_pixMap > getUpX(y_lablG) && x_labl >= getUpX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
				|| (x_labl >= getLeftX(y_lablG) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
			{
				setWidth(1);
				double dh{ 0 };
				bool dh_isMinus{ false };
				if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
				{
					dh = cos(getRotateAngel(true)) * (y_labl - getDownY(x_labl));
				}
				else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
				{
					dh = -sin(getRotateAngel(true)) * (x_labl - getDownX(y_labl));
					dh_isMinus = false;
				}
				setHeight(height() + static_cast<int>(dh), boundingSize);
				if (height() <= 0)
				{
					setHeight(1);
				}
			}
			else
			{
				setHeight(1);
				setWidth(1);
			}
	}
	
	else if (getResizeType() == Resize_YAndWidth)
	{
		if (((y_labl < getDownY(x_lablG) && x_labl > getLeftX(y_lablG)) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (f_x_pixMap > getDownX(y_lablG) && y_labl > getLeftY(x_lablG) && x_labl > getDownX(y_lablG) && (rotationAngle >= 67.5 && rotationAngle < 112.5))
			|| (f_x_pixMap < getDownX(y_lablG) && y_labl < getLeftY(x_lablG) && x_labl < getDownX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
			|| ((y_labl > getDownY(x_lablG) && x_labl < getLeftX(y_lablG)) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
		{
			double dy{ 0 };
			double dw{ 0 };
			if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
			{
				dy = cos(getRotateAngel(true)) * (y_labl - getUpRigth_Y());
				dw = cos(getRotateAngel(true)) * (x_labl - getRigthX(y_labl));
			}
			else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
			{
				dy = -sin(getRotateAngel(true)) * (x_labl - getUpRigth_X());
				dw = sin(getRotateAngel(true)) * (y_labl - getRigthY(x_labl));
			}
			setWidth(width() + static_cast<int>(dw), boundingSize);
			setY(y() + static_cast<int>(dy), boundingSize);
			if (height() <= 0)
			{
				setY(y() + height() - 1);
			}
			if (width() <= 0)
			{
				setWidth(1);
			}
		}
		else
		if ((y_labl >= getDownY(x_lablG) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (f_x_pixMap > getDownX(y_lablG) && x_labl <= getDownX(y_lablG) + 1 && (rotationAngle >= 67.5 && rotationAngle < 112.5))
			|| (f_x_pixMap < getDownX(y_lablG) && x_labl >= getDownX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
			|| (y_labl <= getDownY(x_lablG) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
		{
			setY(y() + height() - 1);
			double dw{ 0 };
			if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
			{
				dw = cos(getRotateAngel(true)) * (x_labl - getRigthX(y_labl));
			}
			else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
			{
				dw = sin(getRotateAngel(true)) * (y_labl - getRigthY(x_labl));
			}
			setWidth(width() + static_cast<int>(dw), boundingSize);
			if (width() <= 0)
			{
				setWidth(1);
			}
		}
		else
		if ((x_labl <= getLeftX(y_lablG) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (f_x_pixMap > getDownX(y_lablG) && y_labl <= getRigthY(x_lablG) && (rotationAngle >= 67.5 && rotationAngle < 112.5))
			|| (f_x_pixMap < getDownX(y_lablG) && x_labl <= getUpX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
			|| (x_labl >= getLeftX(y_lablG) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
		{
			setWidth(1);
			double dy{ 0 };
			if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
			{
				dy = cos(getRotateAngel(true)) * (y_labl - getUpRigth_Y());
			}
			else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
			{
				dy = -sin(getRotateAngel(true)) * (x_labl - getUpRigth_X());
			}
			if (getDownLeft_Y() >= getUpRigth_Y() && getDownLeft_X() < getUpRigth_X())
			{
				setY(y() + static_cast<int>(dy), boundingSize);
				if (getDownRigth_Y() < getUpLeft_Y() || height() <= 0)
				{
					setY(y() + height() - 1);
				}
			}
			else
			if (getDownLeft_Y() < getUpRigth_Y() && getDownLeft_X() < getUpRigth_X())
			{
				setY(y() + static_cast<int>(dy), boundingSize);
				if (getDownRigth_X() > getUpLeft_X() || height() <= 0)
				{
					setY(y() + height() - 1);
				}
			}
			else
			if (getDownLeft_Y() < getUpRigth_Y() && getDownLeft_X() >= getUpRigth_X())
			{
				setY(y() + static_cast<int>(dy), boundingSize);
				if (getDownRigth_Y() > getUpLeft_Y() || height() <= 0)
				{
					setY(y() + height() - 1);

				}
			}
			else
			if (getDownLeft_Y() >= getUpRigth_Y() && getDownLeft_X() >= getUpRigth_X())
			{
				setY(y() + static_cast<int>(dy), boundingSize);
				if (getDownRigth_X() < getUpLeft_X() || height() <= 0)
				{
					setY(y() + height() - 1);
				}
			}
		}
		else
		{
			setHeight(1);
			setX(x() + width() - 1);
		}
	}
	else if (getResizeType() == Resize_XAndHeight)
	{
		if (((y_labl > getUpY(x_lablG) && x_labl < getRigthX(y_lablG)) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
			|| (f_x_pixMap < getUpX(y_lablG) && y_labl < getRigthY(x_lablG) && x_labl < getUpX(y_lablG) && (rotationAngle >= 67.5 && rotationAngle < 112.5))
			|| (f_x_pixMap > getUpX(y_lablG) && y_labl > getRigthY(x_lablG) && x_labl > getUpX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
			|| ((y_labl < getUpY(x_lablG) && x_labl > getRigthX(y_lablG)) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
		{
			double dx{ 0 };
			double dh{ 0 };
			if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
			{
				dx = cos(getRotateAngel(true)) * (x_labl - getDownLeft_X());
				dh = cos(getRotateAngel(true)) * (y_labl - getDownY(x_labl));
			}
			else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
			{
				dx = sin(getRotateAngel(true)) * (y_labl - getDownLeft_Y());
				dh = -sin(getRotateAngel(true)) * (x_labl - getDownX(y_labl));
			}
			setHeight(height() + static_cast<int>(dh), boundingSize);
			setX(x() + static_cast<int>(dx), boundingSize);
			if (width() <= 0)
			{
				setX(x() + width() - 1);
			}
			if (height() <= 0)
			{
				setHeight(1);
			}
		}
		else
			if ((y_labl <= getUpY(x_lablG) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
				|| (f_x_pixMap < getUpX(y_lablG) && x_labl >= getUpX(y_lablG) && (rotationAngle >= 67.5 && rotationAngle < 112.5))
				|| (f_x_pixMap > getUpX(y_lablG) && x_labl <= getUpX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
				|| (y_labl >= getUpY(x_lablG) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
			{
				setHeight(1);
				double dx{ 0 };
				if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
				{
					dx = cos(getRotateAngel(true)) * (x_labl - getDownLeft_X());
				}
				else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
				{
					dx = sin(getRotateAngel(true)) * (y_labl - getUpLeft_Y());
				}
				if (getDownLeft_Y() >= getUpRigth_Y() && getDownLeft_X() < getUpRigth_X())
				{
					setX(x() + static_cast<int>(dx), boundingSize);
					if ((getDownRigth_X() < getUpLeft_X() || width() <= 0))
					{
						setX(x() + width() - 1);
					}
				}
				else
					if (getDownLeft_Y() < getUpRigth_Y() && getDownLeft_X() < getUpRigth_X())
					{
						setX(x() + static_cast<int>(dx), boundingSize);
						if (getDownRigth_Y() < getUpLeft_Y() || width() <= 0)
						{
							setX(x() + width() - 1);
						}
					}
					else
						if (getDownLeft_Y() < getUpRigth_Y() && getDownLeft_X() >= getUpRigth_X())
						{
							setX(x() + static_cast<int>(dx), boundingSize);					
							if (getDownRigth_X() > getUpLeft_X() || width() <= 0)
							{
								setX(x() + width() - 1);
							}
						}
						else
							if (getDownLeft_Y() >= getUpRigth_Y() && getDownLeft_X() >= getUpRigth_X())
							{
								setX(x() + static_cast<int>(dx), boundingSize);
								if (getDownRigth_Y() > getUpLeft_Y() || width() <= 0)
								{
									setX(x() + width() - 1);
								}
							}
			}
			else
				if ((x_labl >= getRigthX(y_lablG) && ((rotationAngle >= 337.5 && rotationAngle <= 360) || (rotationAngle >= 0 && rotationAngle < 22.5) || (rotationAngle >= 22.5 && rotationAngle < 67.5) || (rotationAngle >= 292.5 && rotationAngle < 337.5)))
					|| (f_x_pixMap < getUpX(y_lablG) && y_labl >= getRigthY(x_lablG) && (rotationAngle >= 67.5 && rotationAngle < 112.5))
					|| (f_x_pixMap > getUpX(y_lablG) && x_labl <= getDownX(y_lablG) && (rotationAngle >= 247.5 && rotationAngle < 292.5))
					|| (x_labl <= getRigthX(y_lablG) && ((rotationAngle >= 157.5 && rotationAngle < 202.5) || (rotationAngle >= 112.5 && rotationAngle < 157.5) || (rotationAngle >= 202.5 && rotationAngle < 247.5) || (rotationAngle >= 247.5 && rotationAngle < 292.5))))
				{
					setX(x() + width() - 1);
					double dh{ 0 };
					if ((rotationAngle >= 315.0 && rotationAngle <= 360.0) || (rotationAngle >= 0.0 && rotationAngle < 45.0) || (rotationAngle >= 135.0 && rotationAngle < 225.0))
					{
						dh = cos(getRotateAngel(true)) * (y_labl - getDownY(x_labl));
					}
					else if ((rotationAngle >= 45.0 && rotationAngle < 135.0) || (rotationAngle >= 225.0 && rotationAngle < 315.0))
					{
						dh = -sin(getRotateAngel(true)) * (x_labl - getDownX(y_labl));
					}
					setHeight(height() + static_cast<int>(dh), boundingSize);
					if (height() <= 0)
					{
						setHeight(1);
					}
				}
				else
				{
				}
	}
	//setTranslatePoint(QPoint(x() + cos(getRotateAngel(true)) * width() / 2, y() + sin(getRotateAngel(true)) * height() / 2));
}

//QPointF QtRotateRect::getEdgePoint(int typePoint)
//{
//	// type point: 0-upLeftAngel_Y, 1-upRigAngel_Y, 2-downRigAngel_Y, 3-downLeftAngel_Y
//	switch (typePoint)
//	{
//	case(0):
//		return QPointF(upLeftAngel_X,upLeftAngel_Y);
//		break;
//	case(1):
//		return QPointF(upRigAngel_X, upLeftAngel_Y);
//		break;
//	case(2):
//		return QPointF(downRigAngel_X, downRigAngel_Y);
//		break;
//	case(3):
//		return QPointF(downLeftAngel_X, downLeftAngel_Y);
//		break;
//	default:
//		return QPointF(0.0, 0.0);
//		break;
//	}
//}

QRect QtRotateRect::getRotateRectSize()
{
	return QRect(getMin_X(),getMin_Y(),getMax_X()-getMin_X()+1,getMax_Y()-getMin_Y()+1);
}

QRect QtRotateRect::getOriginalRect() const
{
	return QRect(x(),y(),width(),height());
}

QPoint QtRotateRect::getUpLeftPoint()
{
	return QPoint(getMin_X(), getMin_Y());
}

void QtRotateRect::changePosition(QPoint const imgPoint, QPoint const firstPoint, QSize boundingSize)
{
	int step_X{ imgPoint.x() - firstPoint.x() };
	int step_Y{ imgPoint.y() - firstPoint.y() };
	if (trunc(getMin_X()) + step_X < 1)
	{
		step_X = 0;
	}
	else if (trunc(getMax_X()) + step_X > boundingSize.width() - 1)
	{
		step_X = 0;
	}
	if (trunc(getMin_Y()) + step_Y < 1)
	{
		step_Y = 0;
	}
	else if (trunc(getMax_Y()) + step_Y > boundingSize.height() - 1)
	{
		step_Y = 0;
	}
	int buferW{ width() }, buferH{ height() };
	QRect::setX(x() + step_X);
	QRect::setY(y() + step_Y);
	QRect::setWidth(buferW);
	QRect::setHeight(buferH);
	upLeftAngel_X += step_X;
	upLeftAngel_Y += step_Y;
	upRigAngel_X += step_X;
	upRigAngel_Y += step_Y;
	downLeftAngel_X += step_X;
	downLeftAngel_Y += step_Y;
	downRigAngel_X += step_X;
	downRigAngel_Y += step_Y;
}

void QtRotateRect::changeAngel(QPoint const imgPoint, QSize boundingSize)
{
	double point_X{ static_cast<double>(getMin_X()) + static_cast<double>(getMax_X() - getMin_X()) / 2 + 1 };
	double point_Y{ static_cast<double>(getMin_Y()) + static_cast<double>(getMax_Y() - getMin_Y()) / 2 + 1 };
	QPointF buferPoint{ static_cast<float>(point_X),static_cast<float>(point_Y - height() / 2) };
	double len_v1{ std::sqrt(std::pow(point_X - buferPoint.x(),2) + std::pow(point_Y - buferPoint.y(),2)) };
	double len_v2{ std::sqrt(std::pow(point_X - imgPoint.x(),2) + std::pow(point_Y - imgPoint.y(),2)) };
	QPointF firstPoint{ static_cast<float>(std::sqrt(std::pow(point_X - buferPoint.x(),2))),static_cast<float>(std::sqrt(std::pow(point_Y - buferPoint.y(),2))) };
	QPointF secondPoint{ static_cast<float>(std::sqrt(std::pow(point_X - imgPoint.x(),2))),static_cast<float>(std::sqrt(std::pow(point_Y - imgPoint.y(),2))) };
	double rotateAngel{ std::acos((firstPoint.x() * secondPoint.x() + firstPoint.y() * secondPoint.y()) / (len_v1 * len_v2)) };

	if (imgPoint.x() > point_X && imgPoint.y() < point_Y)
	{

	}
	else if (imgPoint.x() > point_X && imgPoint.y() > point_Y)
	{
		rotateAngel = pi - rotateAngel;
	}
	else if (imgPoint.x() < point_X && imgPoint.y() > point_Y)
	{
		rotateAngel = pi + rotateAngel;
	}
	else if (imgPoint.x() < point_X && imgPoint.y() < point_Y)
	{
		rotateAngel = 2 * pi - rotateAngel;
	}
	setRotateAngel(rotateAngel * 180 / pi, &boundingSize, &QPoint(point_X, point_Y));
}

int QtRotateRect::getResizeType()
{
	return activResizeType_;
}

void QtRotateRect::setResizeType(int activType)
{
	activResizeType_ = activType;
}
