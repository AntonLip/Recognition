#pragma once
#include "qlabel.h"
#include <qdebug.h>
#include <qevent.h>
#include <qpainter.h>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <iostream>

#include "ProcessedObj.h"

class myLabel :
	public QLabel
{
	QPixmap my_Pixmap;
	QPixmap my_PixmapOriginal;
	QPixmap *myPixmap_bufer;
	QPixmap *myPixmap_mouve;
	QCursor myCursor;
	QPoint drPoint;
	QPoint original_drPoint;
	QSize originalSize;
	QSize scaledSize;
	QSize oldSize;
	//std::vector<QRect> rect_roi;
	bool add;
	bool up_or_left, down_or_right;
	bool imgIsShow;
	int imgScaled;
	double *_scaled;
	int activ_scaled;
	int min_activ_scaled, max_activ_scaled;
	int x_labl, y_labl;
	int x_lablG, y_lablG;
	int first_x_labl, first_y_labl;
	int f_x_pixMap, f_y_pixMap;
	int x_pixMap, y_pixMap;
	Q_OBJECT
public:
	explicit myLabel(QWidget *parent = 0);
	QPixmap myPixmap() const;
	QPixmap getPixmapWithROI(std::vector<QRect> &Input) const;
	void mouseMoveEvent(QMouseEvent *evnt);
	void mousePressEvent(QMouseEvent *evnt);
	void mouseReleaseEvent(QMouseEvent *evnt);
	void leaveEvent(QEvent *evnt);
	void set_myPixmap(const QPixmap& pixmap);
	void add_rect(QRect &Input, QPen color = QPen(Qt::red, 1, Qt::DashLine));
	void set_rect(std::vector<QRect> &InOutput);
	void rotatr_rect(QtRotateRect& InOutput);
	void resize_rect(QtRotateRect &InOutput);
	void resize_circle(const QPoint& centerPoint, int& radius);
	void muve_roiRect(QtRotateRect &InOutput);
	void muve_roiCircle(QPoint& centerPoint,const int& radius);
	void show_roi(std::vector<QRect> &Input);
	void draw_rect(QtRotateRect* Input, QPen color=QPen(Qt::red, 1, Qt::DashLine));
	void draw_circle(QPoint* centerPoint, int radius, QPen color = QPen(Qt::red, 1, Qt::DashLine));
	void show_roi(std::vector<QRect> &Input, std::vector<int> rect, int circle);
	void show_partImg(int dx, int dy, int width, int height);
	void show_partImg();
	void reset_x_y();
	void getDrPoint(int &inOutX, int &inOutY);
	void moveImg(int &dx, int &dy);
	double scaledPixmap(int scaled, int &dx, int &dy);
	void scaledPixmap();
	void getMaxMinScal(int &max, int &min);
	void toCenterPoint(QPoint &upLeftPoint);
	void toUpLeftpoint(QPoint &centerPoint);
	void toUpLeftpoint(int &x, int &y);
	void resizeEvent(QResizeEvent* event);
	QPoint* getImgPoint(void);
	QSize getOldSize();
	QSize* getScaledImgSize();
	QSize* getOriginalImgSize();
	void setAllImgScaled();
	void getPointInImg(int& x, int& y);
	int f_x_labl, f_y_labl;
	int s_x_labl, s_y_labl;
	int s_x_pixMap, s_y_pixMap;
	int ref_x, ref_y;
	void toImgCoordinate(int &inOutX, int &inOutY, bool isContains=true);
	~myLabel();
signals:
	void mousePressed();
	void mousePos();
	void mouseLeft();
	void mouseLeftMouveRoi(int direct); ///0 - x<-, 1- x->, 2- y^, 3- y_ 
	void mouseRelease();
};

