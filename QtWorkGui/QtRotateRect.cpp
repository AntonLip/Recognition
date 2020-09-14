#include "QtRotateRect.h"

QtRotateRect::QtRotateRect(QRect parent, double rotatAngel, QPoint drPoint, QPoint transltPont)
	: QRect(parent), 
	rotationAngle(rotatAngel), 
	drawPoint(drPoint), 
	translatePoint(transltPont), 
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



void QtRotateRect::setRotateAngel(double newAngel)
{
	double buferAngel{ rotationAngle };
	if (newAngel >= 360 )
		rotationAngle = 0;
	else 
	if (newAngel <= 0)
	{
		rotationAngle = 360 + newAngel;
	}
	else
		rotationAngle = newAngel;
	double radius{ sqrt(width() * width() + height() * height()) / 2 };
	double constAngel{ asin((height() / 2) / radius) };
	double buferCor{ upLeftAngel_X - (width() / 2 - (sin((90 - buferAngel) * pi / 180 - constAngel) * radius)) };
	upLeftAngel_X = static_cast<double>(buferCor + width() / 2 - (sin((90 - rotationAngle) * pi / 180 - constAngel) * radius));
	buferCor = upLeftAngel_Y - (height() / 2 - (cos((90 - buferAngel) * pi / 180 - constAngel) * radius));
	upLeftAngel_Y = static_cast<double>(buferCor + height() / 2 - (cos((90 - rotationAngle) * 3.14 / 180 - constAngel) * radius));
	upRigAngel_X = static_cast<double>((this->width() * sin((90 - rotationAngle) * pi / 180.0)) + upLeftAngel_X);
	upRigAngel_Y = static_cast<double>(upLeftAngel_Y + (this->width() * cos((90 - rotationAngle) * pi / 180.0)));
	downLeftAngel_X = static_cast<double>(upLeftAngel_X - (this->height() * cos((90 - rotationAngle) * pi / 180.0)));
	downLeftAngel_Y = static_cast<double>(upLeftAngel_Y + (this->height() * sin((90 - rotationAngle) * pi / 180.0)));
	downRigAngel_X = static_cast<double>(downLeftAngel_X + (this->width() * sin((90 - rotationAngle) * pi / 180.0)));
	downRigAngel_Y = static_cast<double>(downLeftAngel_Y + (this->width() * cos((90 - rotationAngle) * pi / 180.0)));
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
	translatePoint.setX(translatePoint.x() + dx);
	translatePoint.setY(translatePoint.y() + dy);
	upLeftAngel_X+=dx;
	upLeftAngel_Y+=dy;
	upRigAngel_X+=dx;
	upRigAngel_Y+=dy;
	downLeftAngel_X+=dx;
	downLeftAngel_Y+=dy;
	downRigAngel_X+=dx;
	downRigAngel_Y+=dy;
}

QPoint QtRotateRect::getTranslatePoint()
{
	return translatePoint;
}

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

void QtRotateRect::setX(int newX)
{
	int dx{ this->x() - newX };
	QRect::setX(newX);
	upLeftAngel_X -= cos(rotationAngle * pi / 180) * dx;
	upLeftAngel_Y -= sin(rotationAngle * pi / 180) * dx;
	downLeftAngel_X -= cos(rotationAngle * pi / 180) * dx;
	downLeftAngel_Y -= sin(rotationAngle * pi / 180) * dx;
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

void QtRotateRect::setWidth(int newWidth)
{
	int dw{ newWidth - this->width() };
	QRect::setWidth(newWidth);
	downRigAngel_X += cos(rotationAngle * pi / 180) * dw;
	downRigAngel_Y += sin(rotationAngle * pi / 180) * dw;
	upRigAngel_X += cos(rotationAngle * pi / 180) * dw;
	upRigAngel_Y += sin(rotationAngle * pi / 180) * dw;
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

int QtRotateRect::getUpY(int x)
{
	return upLeftAngel_Y + ((x - upLeftAngel_X) * (upRigAngel_Y - upLeftAngel_Y)) / (upRigAngel_X - upLeftAngel_X);
}

int QtRotateRect::getDownY(int x)
{
	return downRigAngel_Y + ((x - downRigAngel_X) * (downLeftAngel_Y - downRigAngel_Y)) / (downLeftAngel_X - downRigAngel_X);
}

int QtRotateRect::getUpX(int y)
{
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
