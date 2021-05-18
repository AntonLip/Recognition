#include "QtWidProcesArea.h"

void QtWidProcesArea::mousePressEvent(QMouseEvent* event)
{
	if (this->rect().contains(event->pos()))
	{
		emit setNewActivArea(idWid);
	}
}

QtWidProcesArea::QtWidProcesArea(QString newName, bool isSingelThres, int f_thres, int s_thres, int id, QWidget* parent)
	: QWidget(parent), idWid(id)
{
	ui.setupUi(this);
	setProcesName(newName);
	setSliderPos(isSingelThres, f_thres, s_thres);
	ui.widget_slider->getSlider()->setActivSlider(false);
	setAttribute(Qt::WA_DeleteOnClose);
	connect(ui.widget_slider, SIGNAL(clicSlider()), this, SLOT(slot_clicInslider()));
}

QtWidProcesArea::~QtWidProcesArea()
{
}

void QtWidProcesArea::setProcesName(QString newName)
{
	ui.label_proceName->setText(newName);
}

void QtWidProcesArea::setSliderPos(bool isSingelThres, int f_thres, int s_thres)
{
	if (isSingelThres)
	{
		ui.widget_slider->setOneSlider(true);
		ui.widget_slider->setRenge(0, 100);
		ui.widget_slider->getSlider()->setUpperValue(s_thres);
	}
	else
	{
		ui.widget_slider->setOneSlider(false);
		if (s_thres > 200)
		{
			ui.widget_slider->setRenge(0, 999);
		}
		else
		{
			ui.widget_slider->setRenge(0, 200);
		}
		ui.widget_slider->getSlider()->setUpperValue(s_thres);
		ui.widget_slider->getSlider()->setLowerValue(f_thres);
	}
}

void QtWidProcesArea::setId(int newId)
{
	idWid = newId;
}

void QtWidProcesArea::slot_clicInslider()
{
	emit setNewActivArea(idWid);
}