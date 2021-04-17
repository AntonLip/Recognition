#pragma once

#include <QMainWindow>
#include "ui_QtGuiSimulator.h"
#include "qfiledialog.h"
#include "qlistview.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv/cv.h>
#include "qstandarditemmodel.h"
#include "FrameObserver.h"

#include "ProcessedObj.h"
#include "QtSetupSimulator.h"
#include "QtGuiProgramDetails.h"
#include "QtGUISensorSim.h"

class QtGuiSimulator : public QMainWindow
{
	Q_OBJECT
	std::vector<ProcessedObj> loadObj;
	int activLoadObj;
	QListView *view;
	QStandardItemModel *model;
	QtGuiProgramDetails *Programdetail;
	QtSetupSimulator* SetupSimulator;
	QtGUISensorSim* SensorSimulator;

public:
	QtGuiSimulator(QWidget *parent = Q_NULLPTR);
	~QtGuiSimulator();

private:
	Ui::QtGuiSimulator ui;
	CameraPtrVector cameras;
	std::string Str = "AcquisitionStop"; // проверка Play/Stop
	CameraPtr camera;
	FeaturePtr pFeature; // Generic feature pointer
	VmbInt64_t nPLS;// Payload size value
	FramePtrVector frames{ 3 }; // Frame array
	QPixmap img;
	bool makePhoto = true;
	int m_index=0;
	VimbaSystem& system = VimbaSystem::GetInstance();
	void readVideo(cv::Mat* newFrameMat, QPixmap* newFramePixmap);
	
private slots:
	void dataFromMainMenu(cv::Mat tempImg_out, QString fileName_in);
	void slot_SetActivObj(int newActivObj);
	void slot_openProgramDetail();
	void slot_updateComboBox(int activObj);
	void slot_openSetupSimulator();
	void slot_dataFromSetupSim(ProcessedObj* changedObj);
	void slot_changeActivProcArea(int newActiv);
	void slot_openSensorSim();
	void slot_getCameraInformation(CameraPtrVector&, int );
	void play();
	void slot_stop();
signals:
	void dataToProgramDeyls(ProcessedObj *objts);
	void dataToSetingSim(ProcessedObj* objts);
	void dataToSensorSim(ProcessedObj& objts);
};




