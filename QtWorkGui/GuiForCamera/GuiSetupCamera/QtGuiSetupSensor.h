#pragma once

#include <QWidget>
#include "ui_QtGuiSetupSensor.h"
#include "GuiForSimulator/GuiSetupSimulator/QtSetupSimulator.h"
//#include "myscrollarea.h"
#include "widget.h"
#include "qspinbox.h"
#include "WorkWithCamera/FrameObserver.h"
#include "Loger/simplLoger.h"
#include "ProcessingObject/ProcessedObjectSensor.h"

//using namespace AVT;
//using namespace VmbAPI;
using namespace cv;

class QtGuiSetupSensor : public QtSetupSimulator
{
	Q_OBJECT

public:
	QtGuiSetupSensor(QWidget *parent = Q_NULLPTR);
	~QtGuiSetupSensor();
	friend class FrameObserver;
	double getKoefficient(int value);  //коэффициент уменьшения окна в зависимости от спинбоксов

private:
	Ui::QtGuiSetupSensor ui;
	QHBoxLayout* HL_forFirstStep;
	void setUpGui();
	ProcessedObjectSensor* sensorObject;
	bool masterIsActivObject;
//	CameraPtr camera;
	QtGuiDisplay* videoDisplay;
	QSizeF const maxFrameSize;
	bool chagheROI;
	bool updateCameraParams;
	int oldFrameDelay;
	void setCameraParamsInGui();
	void closeEvent(QCloseEvent* event);
	void setExprosureValue();
	void setGainValue();
public slots:
	void slot_dataFromWorkWithSensor(ProcessedObjectSensor* sensorObj, ProcessedObject* masterObj, QtGuiDisplay* videoDisplay);
	void slot_updateSensorObject(ProcessedObjectSensor* sensorObj);
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
	void slot_pushGainContinous();//continous
	void slot_pushGainOnce();//once
	void slot_pushGainOff();//off
	void slot_dataToGuiWorkWithCamera();
	void slot_changeExprosureSeconds(int newValue);
	void slot_changeExprosureMilSeconds(int newValue);
	void slot_changeExprosureMicSeconds(int newValue);
	void slot_changeExprosure();
	void slot_changeGain(int newValue);
	void slot_changeExprosureAutoTarget(int newValue);
signals:
	void sl_BinningChange(int value);
	void sl_buttonChangeSizeClicked(double changeKoef);
	void signal_getNewOffsetX(int newOffsetX);
	void signal_getNewOffsetY(int newOffsetY);
	void signal_getNewHeigth(int newHeigth);
	void signal_getNewWidth(int newWidth);
};
