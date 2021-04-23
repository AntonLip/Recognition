#pragma once

#include <QWidget>
#include "ui_QtGuiWorkWithCamera.h"
#include "QtGuiSimulator.h"
#include "QtGuiSetupSensor.h"
#include "qstandarditemmodel.h"
#include "FrameObserver.h"

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
	bool isPlay;

private slots:
	void slot_getCameraInformation(CameraPtrVector& cams, int index);
	void slot_play();
	void slot_stop();
	void slot_openSetupCamera();
	void slot_updateFrameInSetupSensor();
	void slot_updateFrame();
	void slot_setNewActivObj(int newActivObject);
signals:
	void dataToSetingSensor(ProcessedObj* sensorObj,ProcessedObj* masterObject, CameraPtrVector& cams, int index);
	void updateFrameInSetupSensor(ProcessedObj* sensorObj);
};
