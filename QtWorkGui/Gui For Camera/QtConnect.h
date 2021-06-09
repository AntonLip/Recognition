#pragma once

#include <QWidget>
#include "ui_QtConnect.h"
#include <VimbaCPP.h>
#include <qstring.h>
#include "QtGuiWorkWithCamera.h"
#include "Loger/simplLoger.h"

//using namespace AVT;
//using namespace VmbAPI;

class QtConnect : public QWidget
{
	Q_OBJECT

public:
	QtConnect(QWidget *parent = Q_NULLPTR);
	~QtConnect();

public slots:
	void on_pushButton_clicked();

private:
	Ui::QtConnect ui;
	AVT::VmbAPI::VimbaSystem& system = AVT::VmbAPI::VimbaSystem::GetInstance();
	AVT::VmbAPI::CameraPtrVector cameras;
	QtGuiWorkWithCamera* simulatorMenu;
signals:
	void moveCameraInformation(AVT::VmbAPI::CameraPtr activSensor);
	void closeMainForm();
private slots:
	void slot_shutdownCamera();
};
