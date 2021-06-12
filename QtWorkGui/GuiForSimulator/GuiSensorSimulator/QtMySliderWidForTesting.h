#pragma once

#include <GuiForSimulator/GuiSetupSimulator/QtMySliderWid.h>
#include "ui_QtMySliderWidForTesting.h"

class QtMySliderWidForTesting : public QtMySliderWid
{
	Q_OBJECT

public:
	QtMySliderWidForTesting(QWidget *parent = Q_NULLPTR);
	~QtMySliderWidForTesting();

private:
	Ui::QtMySliderWidForTesting ui;
};
