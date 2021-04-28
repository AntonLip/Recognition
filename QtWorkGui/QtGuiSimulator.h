#pragma once

#include <QMainWindow>
#include "ui_QtGuiSimulator.h"
#include "qfiledialog.h"
#include "qlistview.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "qstandarditemmodel.h"
#include "simplLoger.h"

#include "ProcessedObj.h"
#include "QtSetupSimulator.h"
#include "QtGuiProgramDetails.h"
#include "QtGUISensorSim.h"

class QtGuiSimulator : public QMainWindow
{
	Q_OBJECT
	
	
public:
	QtGuiSimulator(QWidget *parent = Q_NULLPTR);
	~QtGuiSimulator();
protected:
	Ui::QtGuiSimulator ui;
	std::vector<ProcessedObj> loadObj;
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
	void slot_dataFromSetupSim(ProcessedObj* changedObj);
	void slot_changeActivProcArea(int newActiv);
	void slot_openSensorSim();

signals:
	void dataToProgramDeyls(ProcessedObj *objts);
	void dataToSetingSim(ProcessedObj* objts);
	void dataToSensorSim(ProcessedObj& objts);
};
