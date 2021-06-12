#pragma once

#include <QWidget>
#include "ui_QtWidProcesArea.h"
#include <QMouseEvent>

class QtWidProcesArea : public QWidget
{
	Q_OBJECT
	void mousePressEvent(QMouseEvent* event);
	int idWid;
public:
	QtWidProcesArea(QWidget* parent = Q_NULLPTR);
	QtWidProcesArea(QString newName, bool isSingelThres, int f_thres, int s_thres, int id, QWidget* parent = Q_NULLPTR);
	~QtWidProcesArea();
	void setProcesName(QString newName);
	void setSliderPos(bool isSingelThres, int f_thres, int s_thres);
	void setId(int newId);
protected:
	Ui::QtWidProcesArea ui;
signals:
	void setNewActivArea(int newActiv);
public slots:
	void slot_clicInslider();
};
