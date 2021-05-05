#pragma once

#include <QWidget>
#include "ui_QtGuiProgramDetails.h"
#include "Processing Object/ProcessedObj.h"
#include "QtImgInScrolBar.h"
#include <qmessagebox.h>
#include "QtProgramCopyProcesObj.h"

class QtGuiProgramDetails : public QWidget
{
	Q_OBJECT
	ProcessedObj *firstProcesObj;
	int activ_ProcesObj;
	QtImgInScrolBar* scrolImg;
	QtProgramCopyProcesObj *copyProcesObj;
public:
	QtGuiProgramDetails(QWidget *parent = Q_NULLPTR);
	~QtGuiProgramDetails();
	
private:
	Ui::QtGuiProgramDetails ui;
	
private slots:
	void slot_dataFromGuiSimulator(ProcessedObj* first);
	void slot_changeActivImg(int idImg, QString ProgName);
	void slot_importImg();
	void slot_copyImg();
	void slot_updateImg(int);
	void slot_renameProgName(QString newProgName);
signals:
	void add_Images(int activObj);
};
