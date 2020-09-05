#pragma once

#include <QWidget>
#include "ui_QtAddToolGUI.h"
#include "QtMyDialog.h"
#include <QCloseEvent>

class QtAddToolGUI : public QWidget
{
	Q_OBJECT
	QList<QPushButton*> PButtonList;
	QtMyDialog* dialog;
	int checkedButton;
	bool isClose;
	void closeEvent(QCloseEvent* event);
public:
	QtAddToolGUI(QWidget *parent = Q_NULLPTR);
	~QtAddToolGUI();
private slots:
	void slot_pushButtonClic();
	void slot_chanchTab(int activTab);
	void slot_clicOK();
	void slot_clicCanel();
	void slot_dataFromDialog(bool answer);
private:
	Ui::QtAddToolGUI ui;
signals:
	void dataToSetup(int procesedType, int areaType);
};
