#include "QtGuiSetupSensor.h"


QtGuiSetupSensor::QtGuiSetupSensor(QWidget *parent)
	: QtSetupSimulator(parent)
{
	ui.setupUi(this);
	setUpGui();
	firstStepEnable = true;
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(false);
	connect(QtSetupSimulator::ui.pushButton_step1, SIGNAL(clicked()), this, SLOT(slot_pushStep1()));
	connect(QtSetupSimulator::ui.pushButton_step2, SIGNAL(clicked()), this, SLOT(slot_pushStep2()));
	connect(QtSetupSimulator::ui.pushButton_step3, SIGNAL(clicked()), this, SLOT(slot_pushStep3()));
	connect(QtSetupSimulator::ui.pushButton_step4, SIGNAL(clicked()), this, SLOT(slot_pushStep4()));
}

QtGuiSetupSensor::~QtGuiSetupSensor()
{
}

void QtGuiSetupSensor::setUpGui()
{
	HL_forFirstStep = new QHBoxLayout();
	QtSetupSimulator::ui.page_step1->setLayout(HL_forFirstStep);
	HL_forFirstStep->addWidget(ui.setupSensorParams);
}

void QtGuiSetupSensor::slot_updateSensorObject(ProcessedObj* sensorObj)
{
	sensorObject = sensorObj;
	if (!masterIsActivObject)
	{
		QtSetupSimulator::ui.widget_getMasterImg->updateProcessObj(sensorObj);
	}
}

void QtGuiSetupSensor::slot_pushStep1()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(false);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(sensorObject);
	masterIsActivObject = false;
}

void QtGuiSetupSensor::slot_pushStep2()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(true);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(&masterObjct);
	masterIsActivObject = true;
}

void QtGuiSetupSensor::slot_pushStep3()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(true);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(&masterObjct);
	masterIsActivObject = true;
}

void QtGuiSetupSensor::slot_dataFromWorkWithSensor(ProcessedObj* sensorObj, ProcessedObj* masterObj, CameraPtrVector& cams, int index)
{
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(sensorObj);
	masterObjct = *masterObj;
	sensorObject = sensorObj;
	masterIsActivObject = false;
	cameras = cams;
}