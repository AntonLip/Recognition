#include "QtGuiSetupSensor.h"


QtGuiSetupSensor::QtGuiSetupSensor(QWidget *parent)
	: QtSetupSimulator(parent)
{
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