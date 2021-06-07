#pragma once

#include <QWidget>
#include "ui_QtGUISensorSim.h"
#include "Processing Object/ProcessedObj.h"

class QtGUISensorSim : public QWidget
{
	Q_OBJECT
	ProcessedObject mainProcesObj;
public:
	QtGUISensorSim(QWidget *parent = Q_NULLPTR);
	~QtGUISensorSim();

private:
	Ui::QtGUISensorSim ui;
private slots:
	void slot_dataFromGuiSimulator(ProcessedObject& data);
};
