#pragma once

#include <QWidget>
#include "ui_QtGuiSetupSensor.h"
#include "Gui For Simulator/Gui Setup Simulator/QtSetupSimulator.h"
//#include "myscrollarea.h"
#include "widget.h"
#include "qspinbox.h"
#include "Work With Camera/FrameObserver.h"
#include "Loger/simplLoger.h"


using namespace AVT;
using namespace VmbAPI;
using namespace cv;

class QtGuiSetupSensor : public QtSetupSimulator
{
	Q_OBJECT

public:
	QtGuiSetupSensor(QWidget *parent = Q_NULLPTR);
	~QtGuiSetupSensor();
	//int m_kW = 4872, m_kH = 3248;
	friend class FrameObserver;
	//void scaledImages(double factor);
	double getKoefficient(int value);  //����������� ���������� ���� � ����������� �� ����������


private:
	Ui::QtGuiSetupSensor ui;
	QPixmap img;
	QHBoxLayout* HL_forFirstStep;
	CameraPtrVector cameras;
	void setUpGui();
	ProcessedObj* sensorObject;
	bool masterIsActivObject;
	VmbInt64_t nPLS;// Payload size value
	FeaturePtr pFeature; // Generic feature pointer
	CameraPtr camera;
	FramePtr frame_ptr;

	VimbaSystem& system = VimbaSystem::GetInstance();
	FramePtrVector frames{ 3 }; // Frame array
	FeaturePtr m_ExposureAutoTargetFeature;
	FeaturePtr feature;
	bool makePhoto = true;
	QtGuiDisplay* videoDisplay;
	QSizeF maxFrameSize;
	bool chagheROI;
	void setCameraParamsInGui();
	
public slots:
	void slot_dataFromWorkWithSensor(ProcessedObj* sensorObj, ProcessedObj* masterObj, CameraPtr& cams, int index, QtGuiDisplay* videoDisplay);
	void slot_updateSensorObject(ProcessedObj* sensorObj);
	void slot_pushStep1();
	void slot_pushStep2();
	void slot_pushStep3();
	void slot_cahgeOfsetX(int newOffsetX);
	void slot_cahgeOfsetY(int newOffsetY);
	void slot_cahgeHeigth(int newHeigth);
	void slot_cahgeWidth(int newWidth);


	void slot_setOffset(QRectF& point);
	void slot_setSizeItemInSpinBox(QSizeF& itemSize);
	void slot_changeBinning(int value);
	
	//VmbErrorType GetExposureAutoTargetFeature(FeaturePtr& feature, CameraPtr& camera);
	//VmbErrorType GetExposureAutoTarget(VmbInt64_t& value, CameraPtr& camera);
	//VmbErrorType SetExposureAutoTarget(VmbInt64_t value, CameraPtr& camera);
	//void slot_push_clicked();
	//void on_pushButton_2_clicked();
	void slot_pushFull();
	void slot_pushOneQuarter();
	void slot_pushOneEighth();
	void slot_pushSetRoi();

	//expouser auto
	void slot_pushContinous();//continous
	void slot_pushOnce();//once
	void slot_pushOff();//off

signals:
	void sl_BinningChange(int value);
	void sl_buttonChangeSizeClicked(double changeKoef);
	void signal_getNewOffsetX(int newOffsetX);
	void signal_getNewOffsetY(int newOffsetY);
	void signal_getNewHeigth(int newHeigth);
	void signal_getNewWidth(int newWidth);
};
