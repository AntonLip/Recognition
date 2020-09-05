#include "QtImgWidgets.h"

QtImgWidgets::QtImgWidgets(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

QtImgWidgets::~QtImgWidgets()
{
}

void QtImgWidgets::setImgName(QString name)
{
	ui.label_nameImg->setText(name);
}

QString QtImgWidgets::getImgName()
{
	return ui.label_nameImg->text();
}

int QtImgWidgets::getId()
{
	return id;
}

void QtImgWidgets::setId(int id_in)
{
	id = id_in;
}

void QtImgWidgets::mousePressEvent(QMouseEvent *evnt)
{
	emit mousePres(id);
}

void QtImgWidgets::setImg(QPixmap newImg)
{
	QPixmap scaledPixmap;
	QSize scaledSize{ui.label_forImg->width(),ui.label_forImg->height()};
	scaledPixmap = newImg.scaled(scaledSize, Qt::KeepAspectRatioByExpanding);
	ui.label_forImg->setPixmap(scaledPixmap);
}
