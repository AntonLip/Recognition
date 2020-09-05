#include "MyCircle.h"

MyCircle::MyCircle()
{
	centerPoint = QPoint(0, 0);
	radius = 0;
}

MyCircle::MyCircle(QPoint center_, int radius_):centerPoint(center_),radius(radius_)
{
}

bool MyCircle::contains(QPoint point)
{
	int dx{ centerPoint.x() - point.x() };
	int dy{ centerPoint.y() - point.y() };
	if (sqrt(dx * dx + dy * dy) <= radius)
		return true;
	else
		return false;
}

QPoint MyCircle::getCenterPoint()
{
	return centerPoint;
}

int MyCircle::getRadius()
{
	return radius;
}

int MyCircle::getArea()
{
	return (3.14*radius*radius);
}

void MyCircle::setCenter(QPoint newCenter)
{
	centerPoint = newCenter;
}

void MyCircle::SetRadius(int newRadius)
{
	radius = newRadius;
}

void MyCircle::translate(int x_step, int y_step)
{
	centerPoint.setX(centerPoint.x() + x_step);
	centerPoint.setY(centerPoint.y() + y_step);
}
