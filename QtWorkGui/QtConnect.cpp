#include "QtConnect.h"
#include <qvariant.h>
#include <string.h>
#include <qdebug.h>

QtConnect::QtConnect(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("Connect Menu");
	simulatorMenu = new QtGuiSimulator();
	system.Startup();
	system.GetCameras(cameras);

	std::string strIp;
	QString ipAddres;

	//Заносим в комбобокс доступные камеры (их МАС адреса)
	for (CameraPtrVector::iterator iter = cameras.begin(); cameras.end() != iter; ++iter)
	{		
		(*iter)->GetID(strIp) ;
		ipAddres = QString::fromStdString(strIp);
		ui.comboBox->addItem(ipAddres);
	}
	//system.Shutdown(); //процесс останавливаем в QGuiSimulator

	connect(ui.pushButton_connect, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
	connect(this, SIGNAL(moveCameraInformation(CameraPtrVector&, int)), simulatorMenu, SLOT(slot_getCameraInformation(CameraPtrVector&, int)));
}

QtConnect::~QtConnect()
{
	system.Shutdown();
}

//pushButton_connect
void QtConnect::on_pushButton_clicked()
{
	simulatorMenu->show();
	emit moveCameraInformation(cameras, ui.comboBox->currentIndex());
	this->close();
	//qDebug() << ui.comboBox->currentIndex();
	//вставить вызов окна GEWidget;
}
