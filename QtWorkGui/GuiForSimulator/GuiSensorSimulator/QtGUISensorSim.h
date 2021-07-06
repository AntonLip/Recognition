#pragma once

#include <QWidget>
#include "ui_QtGUISensorSim.h"
#include "qmessagebox.h"
#include "QtImgWidgetsForTesting.h"
#include "ProcessingObject/ProcessedObj.h"
#include "QtWidProcesAreaForTesting.h"
#include <iostream>
#include "Loger/simplLoger.h"

class QtGUISensorSim : public QWidget
{
	Q_OBJECT
	ProcessedObject *masterObject;
	std::vector<ProcessedObject> testingObjects;
	int activTestObject;
	std::vector<QtImgWidgetsForTesting*> imgWidgetsVector;
	std::vector<QSpacerItem*> imgWidgetsSpaser;
	std::vector<QtWidProcesAreaForTesting*> testArearsStatus;
	int activTestArear;
public:
	QtGUISensorSim(QWidget *parent = Q_NULLPTR);
	~QtGUISensorSim();

private:
	Ui::QtGUISensorSim ui;
private slots:
	void slot_dataFromGuiSimulator(ProcessedObject& data);
	void slot_loadImageFromLocalMachine(int loadType);
	void slot_newActivObject(int newActiv);
	void slot_setActivProcesArea(int newActivArea);
};