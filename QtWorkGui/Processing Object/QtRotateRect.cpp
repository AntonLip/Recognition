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

void QtRotateRect::resizeRect(QPoint imgPoint, QPoint globalImgPoint, QPoint& firstPoint, Qt::CursorShape cursorShape)
{
	//double rotAngel_{ rotationAngle };
	//if ((cursorShape == Qt::SizeHorCursor && (((rotAngel_ >= 337.5 && rotAngel_ <= 360) || (rotAngel_ >= 0 && rotAngel_ < 22.5)) || (rotAngel_ >= 157.5 && rotAngel_ < 202.5)))
	//	|| (cursorShape == Qt::SizeVerCursor && ((rotAngel_ >= 67.5 && rotAngel_ < 112.5) || (rotAngel_ >= 247.5 && rotAngel_ < 292.5)))
	//	|| (cursorShape == Qt::SizeFDiagCursor && ((rotAngel_ >= 22.5 && rotAngel_ < 67.5) || (rotAngel_ >= 202.5 && rotAngel_ < 247.5)))
	//	|| (cursorShape == Qt::SizeBDiagCursor && ((rotAngel_ >= 112.5 && rotAngel_ < 157.5) || (rotAngel_ >= 292.5 && rotAngel_ < 337.5))))
	//{
	//	if (((f_x_pixMap < getRigthX(imgPoint.y()) && ((rotAngel_ >= 337.5 && rotAngel_ <= 360) || (rotAngel_ >= 0 && rotAngel_ < 22.5) || (rotAngel_ >= 22.5 && rotAngel_ < 67.5) || (rotAngel_ >= 292.5 && rotAngel_ < 337.5)))
	//		|| (f_y_pixMap < getRigthY(imgPoint.x()) && (rotAngel_ >= 67.5 && rotAngel_ < 112.5))
	//		|| (f_y_pixMap > getRigthY(imgPoint.x()) && (rotAngel_ >= 247.5 && rotAngel_ < 292.5))
	//		|| (f_x_pixMap > getRigthX(imgPoint.y()) && ((rotAngel_ >= 157.5 && rotAngel_ < 202.5) || (rotAngel_ >= 112.5 && rotAngel_ < 157.5) || (rotAngel_ >= 202.5 && rotAngel_ < 247.5))))
	//		&& !down_or_right)
	//	{
	//		up_or_left = true;
	//		double dx{ 0 };
	//		bool dx_isSet{ false };
	//		if (((rotAngel >= 67.5 && rotAngel < 112.5) && y_labl < InOutput.getRigthY(x_labl))
	//			|| ((rotAngel >= 247.5 && rotAngel < 292.5) && y_labl > InOutput.getRigthY(x_labl)))
	//		{
	//			dx = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getLeftY(x_labl));
	//		}
	//		else if ((x_labl < InOutput.getRigthX(y_labl) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//			|| (x_labl > InOutput.getRigthX(y_labl) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5))))
	//		{
	//			dx = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getLeftX(y_labl));
	//		}
	//		else
	//		{
	//			InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//			dx_isSet = true;
	//		}
	//		if (!dx_isSet)
	//		{
	//			InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//			if (InOutput.width() <= 0)
	//			{
	//				InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//			}
	//		}
	//	}
	//	else if (!up_or_left)
	//	{
	//		down_or_right = true;
	//		double dw{ 0 };
	//		bool widt_isSet{ false };
	//		if (((rotAngel >= 67.5 && rotAngel < 112.5) && y_labl > InOutput.getLeftY(x_labl))
	//			|| ((rotAngel >= 247.5 && rotAngel < 292.5) && y_labl < InOutput.getLeftY(x_labl)))
	//		{
	//			dw = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getRigthY(x_labl));
	//		}
	//		else if ((x_labl > InOutput.getLeftX(y_labl) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//			|| (x_labl < InOutput.getLeftX(y_labl) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5))))
	//		{
	//			dw = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getRigthX(y_labl));
	//		}
	//		else
	//		{
	//			InOutput.setWidth(1);
	//			widt_isSet = true;
	//		}
	//		if (!widt_isSet)
	//		{
	//			InOutput.setWidth(InOutput.width() + static_cast<int>(dw), this->getOriginalImgSize());
	//			if (InOutput.width() <= 0)
	//			{
	//				InOutput.setWidth(1);
	//			}
	//		}
	//	}
	//}
	//else
	//	if ((this->cursor().shape() == Qt::SizeVerCursor && (((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5)) || (rotAngel >= 157.5 && rotAngel < 202.5)))
	//		|| (this->cursor().shape() == Qt::SizeHorCursor && ((rotAngel >= 67.5 && rotAngel < 112.5) || (rotAngel >= 247.5 && rotAngel < 292.5)))
	//		|| (this->cursor().shape() == Qt::SizeBDiagCursor && ((rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 202.5 && rotAngel < 247.5)))
	//		|| (this->cursor().shape() == Qt::SizeFDiagCursor && ((rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 292.5 && rotAngel < 337.5))))

	//	{
	//		if (((f_y_pixMap < InOutput.getDownY(x_labl) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//			|| (f_y_pixMap > InOutput.getDownY(x_labl) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5)))
	//			|| ((rotAngel >= 67.5 && rotAngel < 112.5) && f_x_pixMap > InOutput.getDownX(y_labl))
	//			|| ((rotAngel >= 247.5 && rotAngel < 292.5) && f_x_pixMap < InOutput.getDownX(y_labl)))
	//			&& !down_or_right)
	//		{
	//			up_or_left = true;
	//			double dy_first{ 0 };

	//			bool dy_isSet{ false };
	//			bool dy_isMinus{ false };
	//			if (((rotAngel >= 67.5 && rotAngel < 112.5) && x_labl > InOutput.getDownX(y_labl))
	//				|| ((rotAngel >= 247.5 && rotAngel < 292.5) && x_labl < InOutput.getDownX(y_labl)))
	//			{
	//				dy_first = sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getUpX(y_labl));
	//				dy_isMinus = true;
	//			}
	//			else if ((y_labl < InOutput.getDownY(x_labl) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//				|| (y_labl > InOutput.getDownY(x_labl) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5))))
	//			{
	//				dy_first = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getUpY(x_labl));
	//			}
	//			else
	//			{
	//				InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//				dy_isSet = true;
	//			}
	//			if (!dy_isSet)
	//			{
	//				if (dy_isMinus)
	//				{
	//					InOutput.setY(InOutput.y() - static_cast<int>(dy_first), this->getOriginalImgSize());
	//				}
	//				else
	//				{
	//					InOutput.setY(InOutput.y() + static_cast<int>(dy_first), this->getOriginalImgSize());
	//				}
	//			}
	//		}
	//		else if (!up_or_left)
	//		{
	//			down_or_right = true;
	//			bool dh_isSet{ false };
	//			bool dh_isMinus{ false };
	//			double dh_first{ 0 };
	//			if (((rotAngel >= 67.5 && rotAngel < 112.5) && x_labl < InOutput.getUpX(y_labl))
	//				|| ((rotAngel >= 247.5 && rotAngel < 292.5) && x_labl > InOutput.getUpX(y_labl)))
	//			{
	//				dh_first = sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getDownX(y_labl));
	//				dh_isMinus = true;
	//			}
	//			else if ((y_labl > InOutput.getUpY(x_labl) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//				|| (y_labl < InOutput.getUpY(x_labl) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5))))
	//			{
	//				dh_first = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getDownY(x_labl));
	//			}
	//			else
	//			{
	//				InOutput.setHeight(1);
	//				dh_isSet = true;
	//			}
	//			if (!dh_isSet)
	//			{
	//				if (dh_isMinus)
	//				{
	//					InOutput.setHeight(InOutput.height() - static_cast<int>(dh_first), this->getOriginalImgSize());
	//				}
	//				else
	//				{
	//					std::cout << "h" << std::endl;
	//					InOutput.setHeight(InOutput.height() + static_cast<int>(dh_first), this->getOriginalImgSize());
	//				}
	//			}
	//		}
	//	}
	//	else
	//		if ((this->cursor().shape() == Qt::SizeFDiagCursor && (((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5)) || (rotAngel >= 157.5 && rotAngel < 202.5)))
	//			|| (this->cursor().shape() == Qt::SizeBDiagCursor && ((rotAngel >= 67.5 && rotAngel < 112.5) || (rotAngel >= 247.5 && rotAngel < 292.5)))
	//			|| (this->cursor().shape() == Qt::SizeVerCursor && ((rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 202.5 && rotAngel < 247.5)))
	//			|| (this->cursor().shape() == Qt::SizeHorCursor && ((rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 292.5 && rotAngel < 337.5))))
	//		{
	//			if (((f_y_pixMap < InOutput.getDownRigth_Y() && (rotAngel >= 0 && rotAngel < 90))
	//				|| (f_x_pixMap > InOutput.getDownRigth_X() && (rotAngel >= 90 && rotAngel < 180))
	//				|| (f_y_pixMap > InOutput.getDownRigth_Y() && (rotAngel >= 180 && rotAngel < 270))
	//				|| (f_x_pixMap < InOutput.getDownRigth_X() && (rotAngel >= 270 && rotAngel <= 360)))
	//				&& !down_or_right)
	//			{
	//				up_or_left = true;
	//				if (((y_labl < InOutput.getDownY(x_lablG) && x_labl < InOutput.getRigthX(y_lablG)) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//					|| (f_x_pixMap > InOutput.getDownX(y_lablG) && y_labl < InOutput.getRigthY(x_lablG) && x_labl > InOutput.getDownX(y_lablG) && (rotAngel >= 67.5 && rotAngel < 112.5))
	//					|| (f_x_pixMap < InOutput.getDownX(y_lablG) && y_labl > InOutput.getRigthY(x_lablG) && x_labl < InOutput.getDownX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//					|| ((y_labl > InOutput.getDownY(x_lablG) && x_labl > InOutput.getRigthX(y_lablG)) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//				{
	//					double dy{ 0 };
	//					double dx{ 0 };
	//					if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//					{
	//						dy = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getUpLeft_Y());
	//						dx = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getUpLeft_X());
	//					}
	//					else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//					{
	//						dy = -sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getUpLeft_X());
	//						dx = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getUpLeft_Y());
	//					}
	//					InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//					InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//					if (InOutput.height() <= 0)
	//					{
	//						InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//					}
	//					if (InOutput.width() <= 0)
	//					{
	//						InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//					}
	//				}
	//				else
	//					if ((y_labl >= InOutput.getDownY(x_lablG) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//						|| (f_x_pixMap > InOutput.getDownX(y_lablG) && x_labl <= InOutput.getDownX(y_lablG) + 1 && (rotAngel >= 67.5 && rotAngel < 112.5))
	//						|| (f_x_pixMap < InOutput.getDownX(y_lablG) && x_labl >= InOutput.getDownX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//						|| (y_labl <= InOutput.getDownY(x_lablG) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//					{
	//						InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//						double dx{ 0 };
	//						if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//						{
	//							dx = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getUpLeft_X());
	//						}
	//						else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//						{
	//							dx = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getUpLeft_Y());
	//						}

	//						if (InOutput.getDownRigth_Y() >= InOutput.getUpLeft_Y() && InOutput.getDownRigth_X() >= InOutput.getUpLeft_X())
	//						{
	//							InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//							if ((InOutput.getDownRigth_X() < InOutput.getUpLeft_X() || InOutput.width() <= 0))
	//							{
	//								InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//							}
	//						}
	//						else
	//							if (InOutput.getDownRigth_Y() >= InOutput.getUpLeft_Y() && InOutput.getDownRigth_X() < InOutput.getUpLeft_X())
	//							{
	//								InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//								if (InOutput.getDownRigth_Y() < InOutput.getUpLeft_Y() || InOutput.width() <= 0)
	//								{
	//									InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//								}
	//							}
	//							else
	//								if (InOutput.getDownRigth_Y() < InOutput.getUpLeft_Y() && InOutput.getDownRigth_X() < InOutput.getUpLeft_X())
	//								{
	//									InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//									if (InOutput.getDownRigth_X() > InOutput.getUpLeft_X() || InOutput.width() <= 0)
	//									{
	//										InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//									}
	//								}
	//								else
	//									if (InOutput.getDownRigth_Y() < InOutput.getUpLeft_Y() && InOutput.getDownRigth_X() >= InOutput.getUpLeft_X())
	//									{
	//										InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//										if (InOutput.getDownRigth_Y() > InOutput.getUpLeft_Y() || InOutput.width() <= 0)
	//										{
	//											InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//										}
	//									}
	//					}
	//					else
	//						if ((x_labl >= InOutput.getRigthX(y_lablG) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//							|| (f_x_pixMap > InOutput.getDownX(y_lablG) && x_labl >= InOutput.getDownRigth_X() && (rotAngel >= 67.5 && rotAngel < 112.5))
	//							|| (f_x_pixMap < InOutput.getDownX(y_lablG) && x_labl <= InOutput.getDownRigth_X() && (rotAngel >= 247.5 && rotAngel < 292.5))
	//							|| (x_labl <= InOutput.getRigthX(y_lablG) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//						{
	//							InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//							double dy{ 0 };
	//							bool dy_isMinus{ false };
	//							if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//							{
	//								dy = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getUpLeft_Y());
	//							}
	//							else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//							{
	//								dy = -sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getUpLeft_X());
	//								dy_isMinus = true;
	//							}
	//							if (InOutput.getDownRigth_Y() >= InOutput.getUpLeft_Y() && InOutput.getDownRigth_X() >= InOutput.getUpLeft_X())
	//							{
	//								InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//								if (InOutput.getDownRigth_Y() < InOutput.getUpLeft_Y() || InOutput.height() <= 0)
	//								{
	//									InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//								}
	//							}
	//							else
	//								if (InOutput.getDownRigth_Y() >= InOutput.getUpLeft_Y() && InOutput.getDownRigth_X() < InOutput.getUpLeft_X())
	//								{
	//									InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//									if (InOutput.getDownRigth_X() > InOutput.getUpLeft_X() || InOutput.height() <= 0)
	//									{
	//										InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//									}
	//								}
	//								else
	//									if (InOutput.getDownRigth_Y() < InOutput.getUpLeft_Y() && InOutput.getDownRigth_X() < InOutput.getUpLeft_X())
	//									{
	//										InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//										if (InOutput.getDownRigth_Y() > InOutput.getUpLeft_Y() || InOutput.height() <= 0)
	//										{
	//											InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//										}
	//									}
	//									else
	//										if (InOutput.getDownRigth_Y() < InOutput.getUpLeft_Y() && InOutput.getDownRigth_X() >= InOutput.getUpLeft_X())
	//										{
	//											InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//											if (InOutput.getDownRigth_X() < InOutput.getUpLeft_X() || InOutput.height() <= 0)
	//											{
	//												InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//											}
	//										}
	//						}
	//						else
	//						{
	//							InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//							InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//						}
	//			}
	//			else if (!up_or_left)
	//			{
	//				down_or_right = true;
	//				if (((y_labl > InOutput.getUpY(x_lablG) && x_labl > InOutput.getLeftX(y_lablG)) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//					|| (f_x_pixMap < InOutput.getUpX(y_lablG) && y_labl > InOutput.getLeftY(x_lablG) && x_labl < InOutput.getUpX(y_lablG) && (rotAngel >= 67.5 && rotAngel < 112.5))
	//					|| (f_x_pixMap > InOutput.getUpX(y_lablG) && y_labl < InOutput.getLeftY(x_lablG) && x_labl > InOutput.getUpX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//					|| ((y_labl < InOutput.getUpY(x_lablG) && x_labl < InOutput.getLeftX(y_lablG)) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//				{
	//					double dh{ 0 };
	//					double dw{ 0 };

	//					if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//					{
	//						dh = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getDownY(x_labl));
	//						dw = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getRigthX(y_labl));
	//					}
	//					else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//					{
	//						dh = -sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getDownX(y_labl));
	//						dw = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getRigthY(x_labl));
	//					}
	//					InOutput.setHeight(InOutput.height() + static_cast<int>(dh), this->getOriginalImgSize());
	//					InOutput.setWidth(InOutput.width() + static_cast<int>(dw), this->getOriginalImgSize());
	//					if (InOutput.height() <= 0)
	//					{
	//						InOutput.setHeight(1);
	//					}
	//					if (InOutput.width() <= 0)
	//					{
	//						InOutput.setWidth(1);
	//					}
	//				}
	//				else
	//					if ((y_labl <= InOutput.getUpY(x_lablG) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//						|| (f_x_pixMap < InOutput.getUpX(y_lablG) && x_labl >= InOutput.getUpX(y_lablG) + 1 && (rotAngel >= 67.5 && rotAngel < 112.5))
	//						|| (f_x_pixMap > InOutput.getUpX(y_lablG) && x_labl <= InOutput.getUpX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//						|| (y_labl >= InOutput.getUpY(x_lablG) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//					{
	//						InOutput.setHeight(1);
	//						double dw{ 0 };
	//						if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//						{
	//							dw = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getRigthX(y_labl));
	//						}
	//						else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//						{
	//							dw = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getRigthY(x_labl));
	//						}
	//						InOutput.setWidth(InOutput.width() + static_cast<int>(dw), this->getOriginalImgSize());
	//						if (InOutput.width() <= 0)
	//						{
	//							InOutput.setWidth(1);
	//						}
	//					}
	//					else
	//						if ((x_labl <= InOutput.getLeftX(y_lablG) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//							|| (f_x_pixMap < InOutput.getUpX(y_lablG) && x_labl <= InOutput.getUpX(y_lablG) && (rotAngel >= 67.5 && rotAngel < 112.5))
	//							|| (f_x_pixMap > InOutput.getUpX(y_lablG) && x_labl >= InOutput.getUpX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//							|| (x_labl >= InOutput.getLeftX(y_lablG) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//						{
	//							InOutput.setWidth(1);
	//							double dh{ 0 };
	//							bool dh_isMinus{ false };
	//							if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//							{
	//								dh = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getDownY(x_labl));
	//							}
	//							else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//							{
	//								dh = -sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getDownX(y_labl));
	//								dh_isMinus = false;
	//							}
	//							InOutput.setHeight(InOutput.height() + static_cast<int>(dh), this->getOriginalImgSize());
	//							if (InOutput.height() <= 0)
	//							{
	//								InOutput.setHeight(1);
	//							}
	//						}
	//						else
	//						{
	//							InOutput.setHeight(1);
	//							InOutput.setWidth(1);
	//						}
	//			}
	//		}
	//		else
	//			if ((this->cursor().shape() == Qt::SizeBDiagCursor && (((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5)) || (rotAngel >= 157.5 && rotAngel < 202.5)))
	//				|| (this->cursor().shape() == Qt::SizeFDiagCursor && ((rotAngel >= 67.5 && rotAngel < 112.5) || (rotAngel >= 247.5 && rotAngel < 292.5)))
	//				|| (this->cursor().shape() == Qt::SizeHorCursor && ((rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 202.5 && rotAngel < 247.5)))
	//				|| (this->cursor().shape() == Qt::SizeVerCursor && ((rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 292.5 && rotAngel < 337.5))))

	//			{
	//				if (((f_x_pixMap > InOutput.getDownLeft_X() && (rotAngel >= 0 && rotAngel < 90))
	//					|| (f_y_pixMap > InOutput.getDownLeft_Y() && (rotAngel >= 90 && rotAngel < 180))
	//					|| (f_x_pixMap < InOutput.getDownLeft_X() && (rotAngel >= 180 && rotAngel < 270))
	//					|| (f_y_pixMap < InOutput.getDownLeft_Y() && (rotAngel >= 270 && rotAngel <= 360)))
	//					&& !down_or_right)
	//				{
	//					up_or_left = true;
	//					if (((y_labl < InOutput.getDownY(x_lablG) && x_labl > InOutput.getLeftX(y_lablG)) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//						|| (f_x_pixMap > InOutput.getDownX(y_lablG) && y_labl > InOutput.getLeftY(x_lablG) && x_labl > InOutput.getDownX(y_lablG) && (rotAngel >= 67.5 && rotAngel < 112.5))
	//						|| (f_x_pixMap < InOutput.getDownX(y_lablG) && y_labl < InOutput.getLeftY(x_lablG) && x_labl < InOutput.getDownX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//						|| ((y_labl > InOutput.getDownY(x_lablG) && x_labl < InOutput.getLeftX(y_lablG)) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//					{
	//						double dy{ 0 };
	//						double dw{ 0 };
	//						if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//						{
	//							dy = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getUpRigth_Y());
	//							dw = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getRigthX(y_labl));
	//						}
	//						else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//						{
	//							dy = -sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getUpRigth_X());
	//							dw = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getRigthY(x_labl));
	//						}
	//						InOutput.setWidth(InOutput.width() + static_cast<int>(dw), this->getOriginalImgSize());
	//						InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//						if (InOutput.height() <= 0)
	//						{
	//							InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//						}
	//						if (InOutput.width() <= 0)
	//						{
	//							InOutput.setWidth(1);
	//						}
	//					}
	//					else
	//						if ((y_labl >= InOutput.getDownY(x_lablG) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//							|| (f_x_pixMap > InOutput.getDownX(y_lablG) && x_labl <= InOutput.getDownX(y_lablG) + 1 && (rotAngel >= 67.5 && rotAngel < 112.5))
	//							|| (f_x_pixMap < InOutput.getDownX(y_lablG) && x_labl >= InOutput.getDownX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//							|| (y_labl <= InOutput.getDownY(x_lablG) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//						{
	//							InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//							double dw{ 0 };
	//							if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//							{
	//								dw = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getRigthX(y_labl));
	//							}
	//							else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//							{
	//								dw = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getRigthY(x_labl));
	//							}
	//							InOutput.setWidth(InOutput.width() + static_cast<int>(dw), this->getOriginalImgSize());
	//							if (InOutput.width() <= 0)
	//							{
	//								InOutput.setWidth(1);
	//							}
	//						}
	//						else
	//							if ((x_labl <= InOutput.getLeftX(y_lablG) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//								|| (f_x_pixMap > InOutput.getDownX(y_lablG) && y_labl <= InOutput.getRigthY(x_lablG) && (rotAngel >= 67.5 && rotAngel < 112.5))
	//								|| (f_x_pixMap < InOutput.getDownX(y_lablG) && x_labl <= InOutput.getUpX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//								|| (x_labl >= InOutput.getLeftX(y_lablG) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//							{
	//								InOutput.setWidth(1);
	//								double dy{ 0 };
	//								if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//								{
	//									dy = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getUpRigth_Y());
	//								}
	//								else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//								{
	//									dy = -sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getUpRigth_X());
	//								}
	//								if (InOutput.getDownLeft_Y() >= InOutput.getUpRigth_Y() && InOutput.getDownLeft_X() < InOutput.getUpRigth_X())
	//								{
	//									InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//									if (InOutput.getDownRigth_Y() < InOutput.getUpLeft_Y() || InOutput.height() <= 0)
	//									{
	//										InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//									}
	//								}
	//								else
	//									if (InOutput.getDownLeft_Y() < InOutput.getUpRigth_Y() && InOutput.getDownLeft_X() < InOutput.getUpRigth_X())
	//									{
	//										InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//										if (InOutput.getDownRigth_X() > InOutput.getUpLeft_X() || InOutput.height() <= 0)
	//										{
	//											InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//										}
	//									}
	//									else
	//										if (InOutput.getDownLeft_Y() < InOutput.getUpRigth_Y() && InOutput.getDownLeft_X() >= InOutput.getUpRigth_X())
	//										{
	//											InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//											if (InOutput.getDownRigth_Y() > InOutput.getUpLeft_Y() || InOutput.height() <= 0)
	//											{
	//												InOutput.setY(InOutput.y() + InOutput.height() - 1);

	//											}
	//										}
	//										else
	//											if (InOutput.getDownLeft_Y() >= InOutput.getUpRigth_Y() && InOutput.getDownLeft_X() >= InOutput.getUpRigth_X())
	//											{
	//												InOutput.setY(InOutput.y() + static_cast<int>(dy), this->getOriginalImgSize());
	//												if (InOutput.getDownRigth_X() < InOutput.getUpLeft_X() || InOutput.height() <= 0)
	//												{
	//													InOutput.setY(InOutput.y() + InOutput.height() - 1);
	//												}
	//											}
	//							}
	//							else
	//							{
	//								InOutput.setHeight(1);
	//								InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//							}
	//				}
	//				else if (!up_or_left)
	//				{
	//					down_or_right = true;
	//					if (((y_labl > InOutput.getUpY(x_lablG) && x_labl < InOutput.getRigthX(y_lablG)) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//						|| (f_x_pixMap < InOutput.getUpX(y_lablG) && y_labl < InOutput.getRigthY(x_lablG) && x_labl < InOutput.getUpX(y_lablG) && (rotAngel >= 67.5 && rotAngel < 112.5))
	//						|| (f_x_pixMap > InOutput.getUpX(y_lablG) && y_labl > InOutput.getRigthY(x_lablG) && x_labl > InOutput.getUpX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//						|| ((y_labl < InOutput.getUpY(x_lablG) && x_labl > InOutput.getRigthX(y_lablG)) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//					{
	//						double dx{ 0 };
	//						double dh{ 0 };
	//						if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//						{
	//							dx = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getDownLeft_X());
	//							dh = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getDownY(x_labl));
	//						}
	//						else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//						{
	//							dx = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getDownLeft_Y());
	//							dh = -sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getDownX(y_labl));
	//						}
	//						InOutput.setHeight(InOutput.height() + static_cast<int>(dh), this->getOriginalImgSize());
	//						InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//						if (InOutput.width() <= 0)
	//						{
	//							InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//						}
	//						if (InOutput.height() <= 0)
	//						{
	//							InOutput.setHeight(1);
	//						}
	//					}
	//					else
	//						if ((y_labl <= InOutput.getUpY(x_lablG) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//							|| (f_x_pixMap < InOutput.getUpX(y_lablG) && x_labl >= InOutput.getUpX(y_lablG) && (rotAngel >= 67.5 && rotAngel < 112.5))
	//							|| (f_x_pixMap > InOutput.getUpX(y_lablG) && x_labl <= InOutput.getUpX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//							|| (y_labl >= InOutput.getUpY(x_lablG) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//						{
	//							InOutput.setHeight(1);
	//							double dx{ 0 };
	//							if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//							{
	//								dx = cos(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getDownLeft_X());
	//							}
	//							else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//							{
	//								dx = sin(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getUpLeft_Y());
	//							}
	//							if (InOutput.getDownLeft_Y() >= InOutput.getUpRigth_Y() && InOutput.getDownLeft_X() < InOutput.getUpRigth_X())
	//							{
	//								InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//								if ((InOutput.getDownRigth_X() < InOutput.getUpLeft_X() || InOutput.width() <= 0))
	//								{
	//									InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//								}
	//							}
	//							else
	//								if (InOutput.getDownLeft_Y() < InOutput.getUpRigth_Y() && InOutput.getDownLeft_X() < InOutput.getUpRigth_X())
	//								{
	//									InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//									if (InOutput.getDownRigth_Y() < InOutput.getUpLeft_Y() || InOutput.width() <= 0)
	//									{
	//										InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//									}
	//								}
	//								else
	//									if (InOutput.getDownLeft_Y() < InOutput.getUpRigth_Y() && InOutput.getDownLeft_X() >= InOutput.getUpRigth_X())
	//									{
	//										InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());					//InOutput.setX(InOutput.x() + static_cast<int>(outForBoard_X(&InOutput, dx, true)));
	//										if (InOutput.getDownRigth_X() > InOutput.getUpLeft_X() || InOutput.width() <= 0)
	//										{
	//											InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//											//InOutput.setDrowPoint(QPoint(InOutput.x() - InOutput.getTranslatePoint().x(), InOutput.y() - InOutput.getTranslatePoint().y()));
	//										}
	//									}
	//									else
	//										if (InOutput.getDownLeft_Y() >= InOutput.getUpRigth_Y() && InOutput.getDownLeft_X() >= InOutput.getUpRigth_X())
	//										{
	//											InOutput.setX(InOutput.x() + static_cast<int>(dx), this->getOriginalImgSize());
	//											if (InOutput.getDownRigth_Y() > InOutput.getUpLeft_Y() || InOutput.width() <= 0)
	//											{
	//												InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//											}
	//										}
	//						}
	//						else
	//							if ((x_labl >= InOutput.getRigthX(y_lablG) && ((rotAngel >= 337.5 && rotAngel <= 360) || (rotAngel >= 0 && rotAngel < 22.5) || (rotAngel >= 22.5 && rotAngel < 67.5) || (rotAngel >= 292.5 && rotAngel < 337.5)))
	//								|| (f_x_pixMap < InOutput.getUpX(y_lablG) && y_labl >= InOutput.getRigthY(x_lablG) && (rotAngel >= 67.5 && rotAngel < 112.5))
	//								|| (f_x_pixMap > InOutput.getUpX(y_lablG) && x_labl <= InOutput.getDownX(y_lablG) && (rotAngel >= 247.5 && rotAngel < 292.5))
	//								|| (x_labl <= InOutput.getRigthX(y_lablG) && ((rotAngel >= 157.5 && rotAngel < 202.5) || (rotAngel >= 112.5 && rotAngel < 157.5) || (rotAngel >= 202.5 && rotAngel < 247.5) || (rotAngel >= 247.5 && rotAngel < 292.5))))
	//							{
	//								InOutput.setX(InOutput.x() + InOutput.width() - 1);
	//								double dh{ 0 };
	//								if ((rotAngel >= 315.0 && rotAngel <= 360.0) || (rotAngel >= 0.0 && rotAngel < 45.0) || (rotAngel >= 135.0 && rotAngel < 225.0))
	//								{
	//									dh = cos(InOutput.getRotateAngel(true)) * (y_labl - InOutput.getDownY(x_labl));
	//								}
	//								else if ((rotAngel >= 45.0 && rotAngel < 135.0) || (rotAngel >= 225.0 && rotAngel < 315.0))
	//								{
	//									dh = -sin(InOutput.getRotateAngel(true)) * (x_labl - InOutput.getDownX(y_labl));
	//								}
	//								InOutput.setHeight(InOutput.height() + static_cast<int>(dh), this->getOriginalImgSize());
	//								if (InOutput.height() <= 0)
	//								{
	//									InOutput.setHeight(1);
	//								}
	//							}
	//							else
	//							{
	//							}
	//				}
	//			}
	//InOutput.setTranslatePoint(QPoint(InOutput.x() + cos(InOutput.getRotateAngel(true)) * InOutput.width() / 2, InOutput.y() + sin(InOutput.getRotateAngel(true)) * InOutput.height() / 2));
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
	return QRect(getMin_X(),getMin_Y(),getMax_X()-getMin_X(),getMax_Y()-getMin_Y());
}

QPoint QtRotateRect::getUpLeftPoint()
{
	return QPoint(getMin_X(), getMin_Y());
}

void QtRotateRect::setResizeType(int activType)
{
	activResizeType_ = activType;
}
