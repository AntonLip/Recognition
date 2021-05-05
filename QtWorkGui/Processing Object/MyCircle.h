#pragma once
#include <cmath>
#include <qpoint.h>

class MyCircle
{
	QPoint centerPoint;
	int radius;
public:
	MyCircle();
	MyCircle(QPoint center_, int radius_);
	bool contains(QPoint point);
	QPoint getCenterPoint();
	int getRadius();
	int getArea();
	void setCenter(QPoint newCenter);
	void SetRadius(int newRadius);
	void translate(int x_step, int y_step);
};

