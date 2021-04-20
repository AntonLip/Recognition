#pragma once

#include <QWidget>
#include "ui_QtGuiSetupSensor.h"
#include "QtSetupSimulator.h"

class QtGuiSetupSensor : public QtSetupSimulator
{
	Q_OBJECT

public:
	QtGuiSetupSensor(QWidget *parent = Q_NULLPTR);
	~QtGuiSetupSensor();

private:
	Ui::QtGuiSetupSensor ui;
};
