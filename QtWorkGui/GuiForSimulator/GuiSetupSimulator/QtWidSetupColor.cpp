#include "QtWidSetupColor.h"

QtWidSetupColor::QtWidSetupColor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->updateGeometry();
	ui.H_lavel->setRenge(0, 255);
	ui.S_lavel->setRenge(0, 255);
	ui.V_lavel->setRenge(0, 255);
	connect(ui.PB_canel, SIGNAL(clicked()), this, SLOT(slot_canel()));
	connect(ui.PB_ok, SIGNAL(clicked()), this, SLOT(slot_OK()));
	setAttribute(Qt::WA_DeleteOnClose, true);
}

QtWidSetupColor::~QtWidSetupColor()
{
}

void QtWidSetupColor::slot_canel()
{
	this->close();
}

void QtWidSetupColor::slot_OK()
{
	this->close();
}
