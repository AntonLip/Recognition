#pragma once

#include <GuiForSimulator/GuiSimulator/QtImgWidgets.h>
#include "ui_QtImgWidgetsForTesting.h"

class QtImgWidgetsForTesting : public QtImgWidgets
{
	Q_OBJECT

public:
	QtImgWidgetsForTesting(QWidget *parent = Q_NULLPTR);
	~QtImgWidgetsForTesting();

private:
	Ui::QtImgWidgetsForTesting ui;
};
