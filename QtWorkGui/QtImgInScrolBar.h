#pragma once

#include <QWidget>
#include <qevent.h>
#include "ui_QtImgInScrolBar.h"
#include "QtImgWidgets.h"
class QtImgInScrolBar : public QWidget
{
	Q_OBJECT
	QtImgWidgets *wid[32];
	int activ_wid;
public:
	QtImgInScrolBar(ProcessedObj* first, QWidget *parent = Q_NULLPTR);
	~QtImgInScrolBar();
	void set_ImgInQtImgWid(QPixmap newImg);
	void update_qtImgWid(int idWid, ProcessedObj *activObj);
private:
	Ui::QtImgInScrolBar ui;
	void mousePressEvent(QMouseEvent *evnt );

	
public slots:
	void slot_actived(int id);
signals:
	void change_activImg(int id, QString ProgName);
};
