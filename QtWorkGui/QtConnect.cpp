#include "QtConnect.h"
#include <qvariant.h>
#include <string.h>
#include <qdebug.h>

QtConnect::QtConnect(QWidget *parent)
	: QWidget(parent)
{
	LOG.logMessege("QtConnect began to emerge", _DEBUG_);
	ui.setupUi(this);
	this->setWindowTitle("Connect Menu");
	system.Startup();
	system.GetCameras(cameras);
	if (cameras.size() >= 0)
	{
		LOG.logMessege("Camera founded", _DEBUG_);
		this->show();
		std::string strIp;
		QString ipAddres;
		//������� � ��������� ��������� ������ (�� ��� ������)
		for (CameraPtrVector::iterator iter = cameras.begin(); cameras.end() != iter; ++iter)
		{
			(*iter)->GetID(strIp);
			ipAddres = QString::fromStdString(strIp);
			ui.comboBox->addItem(ipAddres);
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
	LOG.logMessege("QtConnect deleted", _DEBUG_);
	system.Shutdown();
}

void QtConnect::on_pushButton_clicked()
{
	LOG.logMessege("Camera selected, crate and open simulatorMenu", _DEBUG_);
	try
	{
		simulatorMenu = new QtGuiWorkWithCamera();
	}
	catch (...)
	{
		LOG.logMessege("simulatorMenu with camer creat error", _ERROR_);
	}
	connect(this, SIGNAL(moveCameraInformation(CameraPtrVector&, int)), simulatorMenu, SLOT(slot_getCameraInformation(CameraPtrVector&, int)));
	simulatorMenu->show();
	emit closeMainForm();
	emit moveCameraInformation(cameras, ui.comboBox->currentIndex());
	this->close();
	//�������� ����� ���� GEWidget;
}
