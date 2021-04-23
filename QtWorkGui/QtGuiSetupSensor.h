#pragma once

#include <QWidget>
#include "ui_QtGuiSetupSensor.h"
#include "QtSetupSimulator.h"
#include "myscrollarea.h"
#include "widget.h"
#include "qspinbox.h"
#include "FrameObserver.h"
#include "simplLoger.h"
class QtGuiSetupSensor : public QtSetupSimulator
{
	Q_OBJECT

public:
	QtGuiSetupSensor(QWidget *parent = Q_NULLPTR);
	~QtGuiSetupSensor();

private:
	Ui::QtGuiSetupSensor ui;
	QHBoxLayout* HL_forFirstStep;
	CameraPtrVector cameras;
	void setUpGui();
	ProcessedObj* sensorObject;
	bool masterIsActivObject;
private slots:
	void slot_dataFromWorkWithSensor(ProcessedObj* sensorObj, ProcessedObj* masterObj, CameraPtrVector& cams, int index);
	void slot_updateSensorObject(ProcessedObj* sensorObj);
	void slot_pushStep1();
	void slot_pushStep2();
	void slot_pushStep3();
};
