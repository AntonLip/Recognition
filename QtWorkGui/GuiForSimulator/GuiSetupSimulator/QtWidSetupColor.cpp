#include "QtWidSetupColor.h"

QtWidSetupColor::QtWidSetupColor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->updateGeometry();
	ui.H_lavel->setRenge(0, 255);
	ui.S_lavel->setRenge(0, 255);
	ui.V_lavel->setRenge(0, 255);
}

QtWidSetupColor::~QtWidSetupColor()
{
}
