#pragma once

#include <QMainWindow>
#include "ui_QtGuiSimulator.h"
#include "qfiledialog.h"
#include "qlistview.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "qstandarditemmodel.h"
#include "Loger/simplLoger.h"

//#include "Processing Object/ProcessedObj.h"
#include "GuiForSimulator/GuiSetupSimulator/QtSetupSimulator.h"
#include "QtGuiProgramDetails.h"
#include "GuiForSimulator/GuiSensorSimulator/QtGUISensorSim.h"

class QtGuiSimulator : public QMainWindow
{
	Q_OBJECT
	
	
public:
	QtGuiSimulator(QWidget *parent = Q_NULLPTR);
	~QtGuiSimulator();
protected:
	Ui::QtGuiSimulator ui;
	//std::vector<ProcessedObj> loadObj;
	std::vector<ProcessedObject> loadObj;
	int activLoadObj;
	QListView *view;
	QStandardItemModel *model;
	QtGuiProgramDetails *Programdetail;
	QtSetupSimulator* SetupSimulator;
	QtGUISensorSim* SensorSimulator;

protected slots:
	void dataFromMainMenu(cv::Mat tempImg_out, QString fileName_in);
	void slot_SetActivObj(int newActivObj);
	void slot_openProgramDetail();
	void slot_updateComboBox(int activObj);
	void slot_openSetupSimulator();
	void slot_dataFromSetupSim(ProcessedObject* changedObj);
	void slot_changeActivProcArea(int newActiv);
	void slot_openSensorSim();

signals:
	void dataToProgramDeyls(ProcessedObject *objts);
	void dataToSetingSim(ProcessedObject& objts);
	void dataToSensorSim(ProcessedObject& objts);

	/*void dataToProgramDeyls(ProcessedObj* objts);
	void dataToSetingSim(ProcessedObj* objts);
	void dataToSensorSim(ProcessedObj& objts);*/
};
