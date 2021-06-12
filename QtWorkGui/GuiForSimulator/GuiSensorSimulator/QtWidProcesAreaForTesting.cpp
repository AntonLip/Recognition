#include "QtWidProcesAreaForTesting.h"

QtWidProcesAreaForTesting::QtWidProcesAreaForTesting(QWidget *parent)
	: QtWidProcesArea(parent)
{
	ui.setupUi(this);
	QtWidProcesArea::ui.horizontalLayout->addWidget(ui.label_machingRate);
	QtWidProcesArea::ui.horizontalLayout->addWidget(ui.LE_resultStatus);
}

QtWidProcesAreaForTesting::QtWidProcesAreaForTesting(QString newName, bool isSingelThres, int f_thres, int s_thres, int id, QWidget* parent) :
	QtWidProcesArea{ newName, isSingelThres, f_thres, s_thres, id, parent}
{
	ui.setupUi(this);
	QtWidProcesArea::ui.horizontalLayout->addWidget(ui.label_machingRate);
	QtWidProcesArea::ui.horizontalLayout->addWidget(ui.LE_resultStatus);
	QtWidProcesArea::ui.horizontalLayout->setStretch(0, 4);
	QtWidProcesArea::ui.horizontalLayout->setStretch(1, 1);
	QtWidProcesArea::ui.horizontalLayout->setStretch(2, 1);
}

QtWidProcesAreaForTesting::~QtWidProcesAreaForTesting()
{
}

void QtWidProcesAreaForTesting::setStatus(bool isOk)
{
	if (isOk)
	{
		ui.LE_resultStatus->setText("OK");
	}
	else
	{
		ui.LE_resultStatus->setText("Neg");
	}
}

void QtWidProcesAreaForTesting::SetMachingRate(int newRate)
{
	ui.label_machingRate->setText(QString::number(newRate));
}
