#pragma once

#include "GuiForSimulator/GuiSetupSimulator/QtWidProcesArea.h"
#include "ui_QtWidProcesAreaForTesting.h"

class QtWidProcesAreaForTesting : public QtWidProcesArea
{
	Q_OBJECT

public:
	QtWidProcesAreaForTesting(QWidget *parent = Q_NULLPTR);
	QtWidProcesAreaForTesting(QString newName, bool isSingelThres, int f_thres, int s_thres, int id, QWidget *parent = Q_NULLPTR);
	~QtWidProcesAreaForTesting();
	void setStatus(bool isOk);
	void SetMachingRate(int newRate);
private:
	Ui::QtWidProcesAreaForTesting ui;

};
