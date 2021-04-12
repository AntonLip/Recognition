#include "QtMyDialog.h"

QtMyDialog::QtMyDialog(QString masseg, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.label->setText(masseg);
	this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	connect(ui.pushButton_canel, SIGNAL(clicked()), this, SLOT(slot_canel()));
	connect(ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(slot_OK()));
	//setAttribute(Qt::WA_DeleteOnClose);
}

QtMyDialog::~QtMyDialog()
{
}

void QtMyDialog::slot_OK()
{
	emit answer(true);
	//this->parentWidget()->close();
	this->close();
}
void QtMyDialog::slot_canel()
{
	emit answer(false);
	this->close();
}