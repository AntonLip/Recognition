#include "QtProgramCopyProcesObj.h"

QtProgramCopyProcesObj::QtProgramCopyProcesObj(ProcessedObj *firstObj, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	viewForFrom = new QListView(ui.comboBox_copyFrom);
	viewForFrom->setIconSize(QSize(100, 100));
	viewForFrom->setStyleSheet("QListView::item{ minimumwidth: 600px;height: 100px}");
	viewForTo = new QListView(ui.comboBox_copyFrom);
	viewForTo->setIconSize(QSize(100, 100));
	viewForTo->setStyleSheet("QListView::item{ minimumwidth: 600px;height: 100px}");
	modelForFrom = new QStandardItemModel();
	modelForTo = new QStandardItemModel();
	ui.comboBox_copyFrom->setView(viewForFrom);
	ui.comboBox_copyFrom->setModel(modelForFrom);
	ui.comboBox_copyTo->setView(viewForTo);
	ui.comboBox_copyTo->setModel(modelForTo);
	for (int i{ 0 }; i < 32; i++)
	{
		ui.comboBox_copyFrom->addItem((firstObj + i)->getProgramName());
		ui.comboBox_copyFrom->setItemIcon(i, (firstObj + i)->getPixmap());
		ui.comboBox_copyTo->addItem((firstObj + i)->getProgramName());
		ui.comboBox_copyTo->setItemIcon(i, (firstObj + i)->getPixmap());
	}
	firstObject = firstObj;
	connect(ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(slot_copyImg()));
	connect(ui.pushButton_close, SIGNAL(clicked()), this, SLOT(slot_closeWid()));
	setAttribute(Qt::WA_DeleteOnClose);
}

QtProgramCopyProcesObj::~QtProgramCopyProcesObj()
{
}

void QtProgramCopyProcesObj::slot_copyImg()
{
	ProcessedObj* fromObj;
	fromObj = (firstObject + ui.comboBox_copyFrom->currentIndex());
	(firstObject + ui.comboBox_copyTo->currentIndex())->SetObjParams(fromObj->getFileName(), fromObj->getDirName(), 
		fromObj->getMat(), fromObj->getPixmap(), !fromObj->imgIsLoaded());
	ui.comboBox_copyTo->setItemIcon(ui.comboBox_copyTo->currentIndex(), fromObj->getPixmap());
	ui.comboBox_copyFrom->setItemIcon(ui.comboBox_copyTo->currentIndex(), fromObj->getPixmap());
	emit objIsCopy(ui.comboBox_copyTo->currentIndex());
}

void QtProgramCopyProcesObj::closeEvent(QCloseEvent* event)
{
	emit gui_close();
}

void QtProgramCopyProcesObj::slot_closeWid()
{
	this->close();
}
