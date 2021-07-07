#pragma once

#include <QWidget>
#include "ui_QtWidSetupColor.h"

class QtWidSetupColor : public QWidget
{
	Q_OBJECT

public:
	QtWidSetupColor(QWidget *parent = Q_NULLPTR);
	~QtWidSetupColor();

private:
	Ui::QtWidSetupColor ui;
private slots:
	void slot_OK();
	void slot_canel();
};
