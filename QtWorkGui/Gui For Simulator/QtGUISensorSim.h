#pragma once

#include <QWidget>
#include "ui_QtGUISensorSim.h"
#include "qmessagebox.h"
#include "QtImgWidgetsForTesting.h"
#include "Processing Object/ProcessedObj.h"
#include <iostream>

class QtGUISensorSim : public QWidget
{
	Q_OBJECT
	ProcessedObject *masterObject;
	std::vector<ProcessedObject> testingObjects;
	int activTestObject;
	std::vector<QtImgWidgetsForTesting*> imgWidgetsVector;
	std::vector<QSpacerItem*> imgWidgetsSpaser;
public:
	QtGUISensorSim(QWidget *parent = Q_NULLPTR);
	~QtGUISensorSim();

private:
	Ui::QtGUISensorSim ui;
private slots:
	void slot_dataFromGuiSimulator(ProcessedObject& data);
	void slot_loadImageFromLocalMachine(int loadType);
	void slot_newActivObject(int newActiv);
};
