#include "QtImgInScrolBar.h"

QtImgInScrolBar::QtImgInScrolBar(ProcessedObj *first, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	for (int i{ 0 }; i < 32; ++i)
	{
		wid[i] = new QtImgWidgets(this);
		wid[i]->setImgName((first+i)->getProgramName());
		wid[i]->setImg((first + i)->getPixmap());
		wid[i]->setId(i);
		ui.horizontalLayout->addWidget(wid[i]);
		connect(wid[i], SIGNAL(mousePres(int)), this, SLOT(slot_actived(int)));
	}
	//slot_actived(0);
	setAttribute(Qt::WA_DeleteOnClose);
}

QtImgInScrolBar::~QtImgInScrolBar()
{
}

void QtImgInScrolBar::mousePressEvent(QMouseEvent *evnt)
{

}

void QtImgInScrolBar::update_qtImgWid(int idWid, ProcessedObj* activObj)
{
	wid[idWid]->setImgName((activObj)->getProgramName());
	wid[idWid]->setImg((activObj)->getPixmap());
}

void QtImgInScrolBar::set_ImgInQtImgWid(QPixmap newImg)
{
	wid[0]->setImg(newImg);
	wid[0]->setStyleSheet("border : 1px solid red;");
}

void QtImgInScrolBar::slot_actived(int id)
{
	for (int i{ 0 }; i < 32; ++i)
	{
		if (i != id)
			wid[i]->setStyleSheet("");
		else
		{
			wid[i]->setStyleSheet("border : 1px solid red;");
			emit change_activImg(i, wid[i]->getImgName());
			activ_wid = i;
		}
	}
}