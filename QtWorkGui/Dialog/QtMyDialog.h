#pragma once

#include <QWidget>
#include "ui_QtMyDialog.h"

class QtMyDialog : public QWidget
{
	Q_OBJECT

public:
	QtMyDialog(QString masseg, QWidget *parent = Q_NULLPTR);
	~QtMyDialog();

private:
	Ui::QtMyDialog ui;
private slots:
	void slot_OK();
	void slot_canel();
signals:
	void answer(bool answer);
};
