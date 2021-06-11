#pragma once

#include <QWidget>
#include "ui_QtImgWidgets.h"
#include "Processing Object/ProcessedObj.h"
#include <qevent.h>
class QtImgWidgets : public QWidget
{
	Q_OBJECT

public:
	QtImgWidgets(QWidget *parent = Q_NULLPTR);
	~QtImgWidgets();
	void setImgName(QString name);
	QString getImgName();
	int getId();
	void setId(int id_in);
	void mousePressEvent(QMouseEvent *evnt);
	void setImg(QPixmap newImg);
protected:
	Ui::QtImgWidgets ui;
	int id;
signals:
	void mousePres(int idWig);
};
