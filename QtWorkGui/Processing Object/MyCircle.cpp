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

void MyCircle::resizeCircle(QPoint const imgPoint, QPoint const firstPoint, QSize* boundingSize)
{
	int step_X{ imgPoint.x() - firstPoint.x() };
	int step_Y{ imgPoint.y() - firstPoint.y() };
	bool overflow{ false };
	double step{ sqrt(step_X * step_X + step_Y * step_Y) };
	if (centerPoint.x() - radius - step < 0)
	{
		step_X = 0;
		overflow = true;
	}
	if ((centerPoint.x() + radius + step > boundingSize->width()) && !overflow)
	{
		step_X = 0;
		overflow = true;
	}

	if ((centerPoint.y() - radius - step) < 0 && !overflow)
	{
		step_Y = 0;
		overflow = true;
	}
	if ((centerPoint.y() + radius + step > boundingSize->height()) && !overflow)
	{
		step_Y = 0;
		overflow = true;
	}
	double r_2{ sqrt(pow(static_cast<double>(centerPoint.x() - imgPoint.x()),2) + pow(static_cast<double>(centerPoint.y() - imgPoint.y()),2)) };
	if (static_cast<int>(r_2) > radius && !overflow)
		radius += (sqrt(step_X * step_X + step_Y * step_Y));
	else if (static_cast<int>(r_2) < radius)
		radius -= (sqrt(step_X * step_X + step_Y * step_Y));
	if (radius <= 0)
		radius = 1;
}

void MyCircle::changePosition(QPoint const imgPoint, QPoint const firstPoint, QSize* boundingSize)
{
	int step_X{ imgPoint.x() - firstPoint.x() };
	int step_Y{ imgPoint.y() - firstPoint.y() };

	if (centerPoint.x() - radius + step_X < 0)
	{
		step_X = 0;
		centerPoint.setX(radius);
	}
	else if (centerPoint.x() + radius + step_X > boundingSize->width() - 1)
	{
		step_X = 0;
		centerPoint.setX(boundingSize->width() - radius - 1);
	}

	if (centerPoint.y() - radius + step_Y < 0)
	{
		step_Y = 0;
		centerPoint.setY(radius);
	}
	else if (centerPoint.y() + radius + step_Y > boundingSize->height() - 1)
	{
		step_Y = 0;
		centerPoint.setY(boundingSize->height() - radius - 1);
	}
	centerPoint.setX(centerPoint.x() + step_X);
	centerPoint.setY(centerPoint.y() + step_Y);

}
