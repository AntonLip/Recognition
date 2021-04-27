#include "QtWorkGui.h"

QtWorkGui::QtWorkGui(QWidget *parent)
    : QMainWindow(parent)
{
	
    ui.setupUi(this);
	try {
		simulatorMenu = new QtGuiSimulator();
	}
	catch (...)
	{
		LOG.logMessege("simulatorMenu creation error", _ERROR_);
	}
	
	QObject::connect(ui.pushButton_conect, SIGNAL(clicked()), this, SLOT(conect_slot()));
	QObject::connect(ui.pushButton_simulator, SIGNAL(clicked()), this, SLOT(openSimulator_slot()));
	QObject::connect(this, SIGNAL(getDataToSimulator(cv::Mat, QString)), simulatorMenu, SLOT(dataFromMainMenu(cv::Mat, QString)));
	setAttribute(Qt::WA_DeleteOnClose, true);
	LOG.logMessege("QtWorkGui create ", _DEBUG_);
}

void QtWorkGui::conect_slot()
{
	LOG.logMessege("start connect camer", _INFO_);
	try {
		connectMenu = new QtConnect();
	}
	catch (...)
	{
		LOG.logMessege("connectMenu creation error", _ERROR_);
	}
	QObject::connect(connectMenu, SIGNAL(closeMainForm()), this, SLOT(slot_dataFromCameraConect()));
	//connectMenu->show();
}

QtWorkGui::~QtWorkGui()
{
	LOG.logMessege("QtWorkGui destructer", _INFO_);
}

void QtWorkGui::openSimulator_slot()
{
	LOG.logMessege("start Simulator", _INFO_);
	QString qstr_bufer{ QFileDialog::getOpenFileName(this, "Images", "D:/", tr("Images files (*.png *.jpg *.bmp)")) };
	cv::Mat img_bufer;
	img_bufer = cv::imread(qstr_bufer.toStdString());
	if (!img_bufer.empty())// checking that image has loaded 
	{
		LOG.logMessege("image load", _DEBUG_);
		simulatorMenu->show();
		emit getDataToSimulator(img_bufer, qstr_bufer);
		this->close();
	}
	else
	{
		LOG.logMessege("image not loaded", _DEBUG_);
		QMessageBox::critical(nullptr, QObject::tr("Warning"), QObject::tr("Image not loaded")); //massage about error download
	}
	LOG.logMessege("end open Simulator", _DEBUG_);
}

void QtWorkGui::slot_dataFromCameraConect()
{
	this->close();
}

