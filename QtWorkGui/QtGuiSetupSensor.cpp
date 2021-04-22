#include "QtGuiSetupSensor.h"


QtGuiSetupSensor::QtGuiSetupSensor(QWidget *parent)
	: QtSetupSimulator(parent)
{
	firstStepEnable = true;
	ui.setupUi(this);
	setUpGui();
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

void QtGuiSetupSensor::slot_dataFromWorkWithSensor(ProcessedObj* masterObject, CameraPtrVector& cams, int index)
{
	QtSetupSimulator::ui.widget_getMasterImg->updateProcessObj(masterObject);
	
}