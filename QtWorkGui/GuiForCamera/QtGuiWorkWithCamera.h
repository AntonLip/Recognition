#pragma once

#include <QWidget>
#include "ui_QtGuiWorkWithCamera.h"
#include "GuiForSimulator/GuiSimulator/QtGuiSimulator.h"
#include "GuiForSimulator/GuiSetupSimulator/QtSetupSimulator.h"
#include "qstandarditemmodel.h"
#include "WorkWithCamera/FrameObserver.h"
#include "GuiForCamera/GuiSetupCamera/QtGuiSetupSensor.h"
#include "ProcessingObject/ProcessedObjectSensor.h"

class QtGuiWorkWithCamera : public QtGuiSimulator
{
	Q_OBJECT

public:
	QtGuiWorkWithCamera(QWidget *parent = Q_NULLPTR);
	~QtGuiWorkWithCamera();

private:
	Ui::QtGuiWorkWithCamera ui;
	std::string acquisitionMode; // проверка Play/Stop
	QtGuiSetupSensor* sensorSetup;
	ProcessedObjectSensor sensorLife;
	bool isPlay;
	

	void setupGui();
	void closeEvent(QCloseEvent* event);
	//void readVideo(cv::Mat* newFrameMat, QPixmap* newFramePixmap);

private slots:
	void slot_getCameraInformation(AVT::VmbAPI::CameraPtr sensor);
	void slot_play();
	void slot_stop();
	void slot_openSetupCamera();
	void slot_updateFrameInSetupSensor();
	void slot_updateFrame();
	void slot_setNewActivObj(int newActivObject);
	void slot_dataFromSetupSim(ProcessedObject* new_pocessObject);
signals:
	void dataToSetingSensor(ProcessedObjectSensor* sensorObj,ProcessedObject* masterObject, QtGuiDisplay *videoDisplay);
	void updateFrameInSetupSensor(ProcessedObjectSensor* sensorObj);
	void workWithCamera_close();
};
