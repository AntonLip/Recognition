#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GE_Widget.h"
#include <opencv2/opencv.hpp>
#include "VimbaCPP.h"
#include <qdebug.h>
#include "widget.h"
#include "ui_widget.h"
#include "myscrollarea.h"
#include "FrameObserver.h"


#include <qlabel.h>
#include <qpushbutton.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qtabbar.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qscrollarea.h>
#include <qstring.h>
#include <qwidget.h>
#include <QWheelEvent>

using namespace AVT;
using namespace VmbAPI;
using namespace cv;

class GE_Widget : public QWidget
{
    Q_OBJECT

public:
	GE_Widget(QWidget* parent = Q_NULLPTR);
	~GE_Widget();
	int m_kW = 4872, m_kH = 3248;
	friend class FrameObserver;
	void scaledImages(double factor);
	double getKoefficient(int value);  //коэффициент уменьшения окна в зависимости от спинбоксов


protected:
	bool eventFilter(QObject*, QEvent* event);


private:
	QPixmap img;
	Ui::GE_WidgetClass ui;
	VmbInt64_t nPLS;// Payload size value
	FeaturePtr pFeature; // Generic feature pointer
	CameraPtr camera;
	CameraPtrVector cameras;
	VimbaSystem& system = VimbaSystem::GetInstance();
	FramePtrVector frames{ 3 }; // Frame array
	FeaturePtr m_ExposureAutoTargetFeature;
	FeaturePtr feature;
	bool makePhoto = true;



public slots:
	void setOffset(QPointF& point);
	void SetSizeItemInSpinBox(QPointF& itemSize);
	void st_ChangeBinning(int value);


	VmbErrorType GetExposureAutoTargetFeature(FeaturePtr& feature, CameraPtr& camera);
	VmbErrorType GetExposureAutoTarget(VmbInt64_t& value, CameraPtr& camera);
	VmbErrorType SetExposureAutoTarget(VmbInt64_t value, CameraPtr& camera);
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();

	void on_pushButton_9_clicked();


	//expouser auto
	void on_pushButton_6_clicked();//continous
	void on_pushButton_7_clicked();//once
	void on_pushButton_8_clicked();//off

signals:
	void sl_BinningChange(int value);
	void sl_buttonChangeSizeClicked(double changeKoef);
};
