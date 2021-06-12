#pragma once

#include <QWidget>
#include "ui_QtProgramCopyProcesObj.h"
#include <qlistview.h>
#include <qstandarditemmodel.h>
#include "ProcessingObject/ProcessedObject.h"


class QtProgramCopyProcesObj : public QWidget
{
	Q_OBJECT

public:
	QtProgramCopyProcesObj(ProcessedObject *firstObj,QWidget *parent = Q_NULLPTR);
	~QtProgramCopyProcesObj();

private:
	ProcessedObject *firstObject;
	QListView* viewForFrom;
	QListView* viewForTo;
	QStandardItemModel* modelForFrom;
	QStandardItemModel* modelForTo;
	Ui::QtProgramCopyProcesObj ui;
	void closeEvent(QCloseEvent* event);
private slots:
	void slot_copyImg();
	void slot_closeWid();
signals:
	void objIsCopy(int idCopyTo);
	void gui_close();
};
