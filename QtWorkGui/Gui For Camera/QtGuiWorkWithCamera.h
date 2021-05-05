#pragma once

#include <QWidget>
#include "ui_QtGuiWorkWithCamera.h"
#include "Gui For Simulator/Gui Simulator/QtGuiSimulator.h"
#include "Gui For Simulator/Gui Setup Simulator/QtSetupSimulator.h"
#include "qstandarditemmodel.h"
#include "Work With Camera/FrameObserver.h"
#include "Gui For Camera/Gui Setup Camera/QtGuiSetupSensor.h"

class QtGuiWorkWithCamera : public QtGuiSimulator
{
	Q_OBJECT

public:
	QtGuiWorkWithCamera(QWidget *parent = Q_NULLPTR);
	~QtGuiWorkWithCamera();

private:
	Ui::QtGuiWorkWithCamera ui;
	CameraPtrVector cameras;
	std::string Str = "AcquisitionStop"; // проверка Play/Stop
	CameraPtr camera;
	FeaturePtr pFeature; // Generic feature pointer
	VmbInt64_t nPLS;// Payload size value
	FramePtrVector frames{ 3 }; // Frame array
	QPixmap img;
	bool makePhoto = true;
	int m_index = 0;
	VimbaSystem& system = VimbaSystem::GetInstance();
	void readVideo(cv::Mat* newFrameMat, QPixmap* newFramePixmap);
	QtGuiSetupSensor* sensorSetup;
	void setupGui();
	ProcessedObj cameraLife;
	void closeEvent(QCloseEvent* event);
	bool isPlay;

private slots:
	void slot_getCameraInformation(CameraPtrVector& cams, int index);
	void slot_play();
	void slot_stop();
	void slot_openSetupCamera();
	void slot_updateFrameInSetupSensor();
	void slot_updateFrame();
	void slot_setNewActivObj(int newActivObject);
	void slot_dataFromSetupSim(ProcessedObj* new_pocessObject);
signals:
	void dataToSetingSensor(ProcessedObj* sensorObj,ProcessedObj* masterObject, CameraPtr& cams, int index, QtGuiDisplay *videoDisplay);
	void updateFrameInSetupSensor(ProcessedObj* sensorObj);
	void workWithCamera_close();
};
