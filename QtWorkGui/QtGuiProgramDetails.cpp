#include "QtGuiProgramDetails.h"

QtGuiProgramDetails::QtGuiProgramDetails(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	firstProcesObj = nullptr;
	activ_ProcesObj = 0;
	connect(ui.pushButtn_Import, SIGNAL(clicked()), this, SLOT(slot_importImg()));
	connect(ui.pushButtn_Copy, SIGNAL(clicked()), this, SLOT(slot_copyImg()));
	connect(ui.lineEdit_ProgrmNam, SIGNAL(textChanged(QString)), this, SLOT(slot_renameProgName(QString)));
	setAttribute(Qt::WA_DeleteOnClose);
	ui.my_widget->setEanbleActivededRoi(false);
}

QtGuiProgramDetails::~QtGuiProgramDetails()
{
	firstProcesObj = nullptr;
	delete firstProcesObj;
}

void QtGuiProgramDetails::slot_changeActivImg(int idImg, QString ProgName)
{
	activ_ProcesObj = idImg;
	(firstProcesObj + idImg)->setProgramName(ProgName);
	ui.my_widget->setActivProcessObj((firstProcesObj + idImg));
	ui.lineEdit_ProgrmNam->setText(ProgName);
}

void QtGuiProgramDetails::slot_importImg()
{
	QString qstr_bufer{ QFileDialog::getOpenFileName(this, "Images", "D:/", tr("Images files (*.png *.jpg *.bmp)")) };
	QPixmap pixmapBufer;
	pixmapBufer.load(qstr_bufer);
	cv::Mat img_bufer;
	img_bufer = cv::imread(qstr_bufer.toStdString());
	if (!img_bufer.empty())// checking that image has loaded 
	{
		std::size_t found = qstr_bufer.toStdString().find_last_of("/\\");
		(firstProcesObj + activ_ProcesObj)->SetObjParams(QString::fromStdString(qstr_bufer.toStdString().substr(found + 1)), 
			QString::fromStdString(qstr_bufer.toStdString().substr(0, found)), img_bufer,pixmapBufer , false);
		ui.my_widget->setActivProcessObj((firstProcesObj + activ_ProcesObj));
		scrolImg->update_qtImgWid(activ_ProcesObj, firstProcesObj + activ_ProcesObj);
		emit add_Images(activ_ProcesObj);
	}
	else
	{
		QMessageBox::critical(nullptr, QObject::tr("Warning"), QObject::tr("Image not loaded")); //massage about error download
	}
}

void QtGuiProgramDetails::slot_copyImg()
{
		copyProcesObj = new QtProgramCopyProcesObj(firstProcesObj);
		copyProcesObj->show();
		connect(copyProcesObj, SIGNAL(objIsCopy(int)), this, SLOT(slot_updateImg(int)));
}

void QtGuiProgramDetails::slot_updateImg(int updateObj)
{
	scrolImg->update_qtImgWid(updateObj, firstProcesObj + updateObj);
	emit add_Images(updateObj);
}

void QtGuiProgramDetails::slot_renameProgName(QString newProgName)
{
	(firstProcesObj + activ_ProcesObj)->setProgramName(newProgName);
	slot_updateImg(activ_ProcesObj);
}

void QtGuiProgramDetails::slot_dataFromGuiSimulator(ProcessedObj* first)
{
	firstProcesObj = first;
	activ_ProcesObj = 0;
	scrolImg = new QtImgInScrolBar(firstProcesObj,this);
	ui.scrollArea_->setWidget(scrolImg);
	ui.my_widget->setActivProcessObj(firstProcesObj);
	connect(scrolImg, SIGNAL(change_activImg(int, QString)), this, SLOT(slot_changeActivImg(int, QString)));
	scrolImg->slot_actived(0);
}