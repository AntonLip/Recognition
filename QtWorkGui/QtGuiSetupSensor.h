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
private slots:
	void slot_dataFromWorkWithSensor(ProcessedObj* masterObject, CameraPtrVector& cams, int index);
};
