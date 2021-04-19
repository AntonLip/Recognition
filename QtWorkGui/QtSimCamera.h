#pragma once

#include <QWidget>
#include "ui_QtSimCamera.h"
#include "QtGuiSimulator.h"

class QtSimCamera : public QtGuiSimulator
{
	Q_OBJECT

public:
	QtSimCamera(QWidget *parent = Q_NULLPTR);
	~QtSimCamera();

private:
	Ui::QtSimCamera ui;
};
