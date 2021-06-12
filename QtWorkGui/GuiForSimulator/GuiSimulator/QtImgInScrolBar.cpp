#include "QtImgInScrolBar.h"

QtImgInScrolBar::QtImgInScrolBar(ProcessedObject *first, QWidget *parent)
	: QWidget(parent),
	wid(nullptr)
{
	ui.setupUi(this);
	wid = new QtImgWidgets[32];
	for (int i{ 0 }; i < 32; ++i)
	{
		wid[i].setImgName((first+i)->getProgramName());
		wid[i].setImg((first + i)->getCorrectPixmap());
		wid[i].setId(i);
		ui.horizontalLayout->addWidget(&wid[i]);
		connect(&wid[i], SIGNAL(mousePres(int)), this, SLOT(slot_actived(int)));
	}
	//slot_actived(0);
	setAttribute(Qt::WA_DeleteOnClose);
}

QtImgInScrolBar::~QtImgInScrolBar()
{
	delete[]wid;
}

void QtImgInScrolBar::mousePressEvent(QMouseEvent *evnt)
{

}

void QtImgInScrolBar::update_qtImgWid(int idWid, ProcessedObject* activObj)
{
	wid[idWid].setImgName((activObj)->getProgramName());
	wid[idWid].setImg((activObj)->getCorrectPixmap());
}

void QtImgInScrolBar::set_ImgInQtImgWid(QPixmap newImg)
{
	wid[0].setImg(newImg);
	wid[0].setStyleSheet("border : 1px solid red;");
}

void QtImgInScrolBar::slot_actived(int id)
{
	for (int i{ 0 }; i < 32; ++i)
	{
		if (i != id)
			wid[i].setStyleSheet("");
		else
		{
			wid[i].setStyleSheet("border : 1px solid red;");
			emit change_activImg(i, wid[i].getImgName());
			activ_wid = i;
		}
	}
}