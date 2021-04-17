#pragma once

#include <qrect.h>
#include <cmath>
double const pi = 3.14159265359;
class QtRotateRect : public QRect
{
	double rotationAngle;
	QPoint drawPoint;
	QPoint translatePoint;
	double upLeftAngel_X;
	double upLeftAngel_Y;
	double upRigAngel_X;
	double upRigAngel_Y;
	double downLeftAngel_X;
	double downLeftAngel_Y;
	double downRigAngel_X;
	double downRigAngel_Y;
	
public:
	QtRotateRect(QRect parent = QRect(0, 0, 0, 0), double rotateAngl = 0.0, QPoint drPoint=QPoint(0,0), QPoint transltPont=QPoint(0,0));
	QtRotateRect(int upLeft_x, int upLeft_Y, int width, int heigth, double ratAngel);
	~QtRotateRect();
	void setRotateAngel(double newAngel);
	double getRotateAngel(bool inRad=false);
	void setDrowPoint(QPoint drPoint);
	QPoint getDrawPoint();
	void setTranslatePoint(QPoint transltPont);
	void translateTranslatePoint(int dx, int dy);
	QPoint getTranslatePoint();
	bool contains(QPoint point);
	bool contains(int x, int y);
	int getUpLeft_X();
	int getUpLeft_Y();
	int getDownLeft_X();
	int getDownLeft_Y();
	int getUpRigth_X();
	int getUpRigth_Y();
	int getDownRigth_X();
	int getDownRigth_Y();
	int getMax_X();
	int getMin_X();
	int getMax_Y();
	int getMin_Y();
	void setX(int newX);
	void setY(int newY);
	void setWidth(int newWidth);
	void setHeight(int newHeigth);
	int getUpY(int x);
	int getDownY(int x);
	int getUpX(int y);
	int getDownX(int y);
	int getLeftX(int y);
	int getRigthX(int y);
	int getRigthY(int x);
	int getLeftY(int x);
};

