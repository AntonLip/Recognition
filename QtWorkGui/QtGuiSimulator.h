#pragma once

#include <QMainWindow>
#include "ui_QtGuiSimulator.h"
#include "qfiledialog.h"
#include "qlistview.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include "qstandarditemmodel.h"

#include "ProcessedObj.h"
#include "QtSetupSimulator.h"
#include "QtGuiProgramDetails.h"

class QtGuiSimulator : public QMainWindow
{
	Q_OBJECT
	std::vector<ProcessedObj> loadObj;
	int activLoadObj;
	QListView *view;
	QStandardItemModel *model;
	QtGuiProgramDetails *Programdetail;
	QtSetupSimulator* SetupSimulator;
public:
	QtGuiSimulator(QWidget *parent = Q_NULLPTR);
	~QtGuiSimulator();
private:
	Ui::QtGuiSimulator ui;
	
private slots:
	void dataFromMainMenu(cv::Mat tempImg_out, QString fileName_in);
	void slot_SetActivObj(int newActivObj);
	void slot_openProgramDetail();
	void slot_updateComboBox(int activObj);
	void slot_openSetupSimulator();
	void slot_dataFromSetupSim(ProcessedObj* changedObj);
	void slot_changeActivProcArea(int newActiv);
signals:
	void dataToProgramDeyls(ProcessedObj *objts);
	void dataToSetingSim(ProcessedObj* objts);
};
