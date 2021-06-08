#include "QtConnect.h"
#include <qvariant.h>
#include <string.h>
#include <qdebug.h>

QtConnect::QtConnect(QWidget *parent)
	: QWidget(parent),
	cameras{},
	simulatorMenu{nullptr}
{
	LOG.logMessege("QtConnect began to emerge", _DEBUG_);
	ui.setupUi(this);
	this->setWindowTitle("Connect Menu");
	system.Startup();
	system.GetCameras(cameras);
	if (cameras.size() >= 0) ///////////change 0 on 1 afetr program will buil(SAV)!!!!!!
	{
		LOG.logMessege("Camera founded", _DEBUG_);
		this->show();
		std::string strIp;
		//Заносим в комбобокс доступные камеры (их МАС адреса)
		for (CameraPtrVector::iterator iter = cameras.begin(); cameras.end() != iter; ++iter)
		{
			(*iter)->GetID(strIp);
			ui.comboBox->addItem(QString::fromStdString(strIp));
		}
		connect(ui.pushButton_connect, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
	}
	else
	{
		LOG.logMessege("Camera not founded", _DEBUG_);
		QMessageBox::critical(nullptr, QObject::tr("Warning"), QObject::tr("Camera not founded"));
	}
	LOG.logMessege("QtConnect emerge", _DEBUG_);
}

QtConnect::~QtConnect()
{
	LOG.logMessege("QtConnect deleted", _INFO_);
}

void QtConnect::on_pushButton_clicked()
{
	LOG.logMessege("Camera selected, crate and open simulatorMenu", _INFO_);
	try
	{
		simulatorMenu = new QtGuiWorkWithCamera();
	}
	catch (...)
	{
		LOG.logMessege("simulatorMenu with camer creat error", _ERROR_);
	}
	connect(this, SIGNAL(moveCameraInformation(CameraPtr)), simulatorMenu, SLOT(slot_getCameraInformation(CameraPtr)));
	connect(simulatorMenu, SIGNAL(workWithCamera_close()), this, SLOT(slot_shutdownCamera()));
	simulatorMenu->show();
	emit closeMainForm();
	emit moveCameraInformation(cameras[ui.comboBox->currentIndex()]);
	this->close();
	//вставить вызов окна GEWidget;
}

void QtConnect::slot_shutdownCamera()
{
	LOG.logMessege("Shutdown camera", _INFO_);
	system.Shutdown();
}
