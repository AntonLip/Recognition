#include "QtGuiWorkWithCamera.h"

QtGuiWorkWithCamera::QtGuiWorkWithCamera(QWidget* parent)
	: QtGuiSimulator{ parent },
	acquisitionMode{ "AcquisitionStop" },
	sensorSetup{ nullptr },
	sensorLife{ "sensor life", "", cv::Mat(), QPixmap(), true },
	isPlay{ false }
{
	LOG.logMessege("QtGuiWorkWithCamera constructor started", _DEBUG_);
	ui.setupUi(this);
	setupGui();
	connect(ui.PB_play, SIGNAL(clicked()), this, SLOT(slot_play()));
	connect(ui.PB_parametrs, SIGNAL(clicked()), this, SLOT(slot_stop()));
	connect(ui.PB_sensorSetup, SIGNAL(clicked()), this, SLOT(slot_openSetupCamera()));
	connect(QtGuiSimulator::ui.widget_DisplayImg, SIGNAL(signal_updateFrame()), this, SLOT(slot_updateFrame()));
	connect(QtGuiSimulator::ui.comboBox_program, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_setNewActivObj(int)));
	setAttribute(Qt::WA_DeleteOnClose, true);
}

QtGuiWorkWithCamera::~QtGuiWorkWithCamera()
{
	LOG.logMessege("QtGuiWorkWithCamera destruct fineshed", _DEBUG_);
}

//void QtGuiWorkWithCamera::readVideo(cv::Mat* newFrameMat, QPixmap* newFramePixmap)
//{
//	LOG.logMessege("set frame in QtGuiWorkWithCamera", _DEBUG_);
//	loadObj[activLoadObj]=ProcessedObject("", "", *newFrameMat, *newFramePixmap, loadObj[activLoadObj].getProgramName(), false);
//	//loadObj[activLoadObj].SetObjParams("", "", *newFrameMat, *newFramePixmap, false);
//}

void QtGuiWorkWithCamera::setupGui()
{
	QtGuiSimulator::ui.horizontalLayout_4->insertWidget(0, ui.PB_play);
	QtGuiSimulator::ui.horizontalLayout_4->insertWidget(1, ui.PB_parametrs);
	QtGuiSimulator::ui.pushButton_SetupSimltr->hide();
	QtGuiSimulator::ui.verticalLayout->insertWidget(0, ui.PB_sensorSetup);
}

void QtGuiWorkWithCamera::closeEvent(QCloseEvent* event)
{
	AVT::VmbAPI::CameraPtr camera{ sensorLife.getCameraPtr() };
	AVT::VmbAPI::FeaturePtr pFeature;
	camera->GetFeatureByName("AcquisitionStop", pFeature);
	pFeature->RunCommand();
	camera->EndCapture();
	camera->FlushQueue();
	camera->RevokeAllFrames();
	camera->Close();
	emit workWithCamera_close();
	LOG.logMessege("close form work with sensor", _INFO_);
}

void QtGuiWorkWithCamera::slot_play()
{
	isPlay = true;
	QtGuiSimulator::ui.widget_DisplayImg->setActivProcessObj(sensorLife);
	QtGuiSimulator::ui.widget_DisplayImg->setProcessObjStatus(false);
	QtGuiSimulator::ui.linEdit_fileName->setText(sensorLife.getFileName());
}

void QtGuiWorkWithCamera::slot_stop()
{
	isPlay = false;
	QtGuiSimulator::ui.widget_DisplayImg->setActivProcessObj(loadObj[activLoadObj]);
	QtGuiSimulator::ui.widget_DisplayImg->setProcessObjStatus(true);
	QtGuiSimulator::ui.linEdit_fileName->setText(loadObj[activLoadObj].getFileName());
}

void QtGuiWorkWithCamera::slot_openSetupCamera()
{
	sensorSetup = new QtGuiSetupSensor();
	sensorSetup->show();
	connect(this, SIGNAL(dataToSetingSensor(ProcessedObjectSensor*, ProcessedObject*, QtGuiDisplay*)), sensorSetup, SLOT(slot_dataFromWorkWithSensor(ProcessedObjectSensor*, ProcessedObject*, QtGuiDisplay*)));
	connect(this, SIGNAL(updateFrameInSetupSensor(ProcessedObjectSensor*)), sensorSetup, SLOT(slot_updateSensorObject(ProcessedObjectSensor*)));
	connect(QtGuiSimulator::ui.widget_DisplayImg, SIGNAL(signal_updateFrame()), this, SLOT(slot_updateFrameInSetupSensor()));
	connect(sensorSetup, SIGNAL(dataToGUISim(ProcessedObject*)), this, SLOT(slot_dataFromSetupSim(ProcessedObject*)));
	emit dataToSetingSensor(&sensorLife, &loadObj[activLoadObj], QtGuiSimulator::ui.widget_DisplayImg);
}

void QtGuiWorkWithCamera::slot_updateFrameInSetupSensor()
{
	emit updateFrameInSetupSensor(&sensorLife);
}

void QtGuiWorkWithCamera::slot_updateFrame()
{
	if (isPlay)
	{
		QtGuiSimulator::ui.widget_DisplayImg->updateProcessObj(sensorLife);
	}
}

void QtGuiWorkWithCamera::slot_setNewActivObj(int newActivObject)
{
	activLoadObj = newActivObject;
	if (!isPlay)
	{
		QtGuiSimulator::ui.widget_DisplayImg->setActivProcessObj(loadObj[activLoadObj]);
	}
}

void QtGuiWorkWithCamera::slot_dataFromSetupSim(ProcessedObject* new_pocessObject)
{
	QtGuiSimulator::slot_dataFromSetupSim(new_pocessObject);
	//sensorLife.setProcessedArears(new_pocessObject->getProcesArears());
}

void QtGuiWorkWithCamera::slot_getCameraInformation(AVT::VmbAPI::CameraPtr newSensor)
{
	LOG.logMessege("start conect with in QtGuiWorkWithCamera", _INFO_);
	sensorLife.setCameraPtr(newSensor);
	try {
		if (acquisitionMode == "AcquisitionStop")
		{
			//camera = newSensor;														//������ �� ������ ������ �����������
			newSensor->Open(VmbAccessModeFull);											//��������� ������ � ������ "������ ��� ������ � ������". ����������� ���� ����� ��� ��������� ������� ������ � ��������� �����������
			AVT::VmbAPI::FeaturePtr pFeature;
			newSensor->GetFeatureByName("PayloadSize", pFeature);						//�������� ������� �� ����� "������ �������� ��������"(������ ����� ������). ���������� ������� ���������� � pFeature  Feature-��������������, �������
			VmbInt64_t nPLS;															// Payload size value
			pFeature->GetValue(nPLS);													//������ �������� ������� �������� ��������
			AVT::VmbAPI::FramePtrVector frames{ 3 };
			for (AVT::VmbAPI::FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - ������ ���������� �� �����, frames.begin()- ������ ����, frames.end()- ��������� ����. ���� ����������� �� ������� �����
			{
				(*iter).reset(new AVT::VmbAPI::Frame(nPLS));											//����� ���������� ��������. ��������� ����� ������ ��� ,������� ����� ( ������ �� ����� ����� �������� nPLS)
				(*iter)->RegisterObserver(AVT::VmbAPI::IFrameObserverPtr(new FrameObserver(newSensor, QtGuiSimulator::ui.widget_DisplayImg, &sensorLife)));
				newSensor->AnnounceFrame(*iter);
				//������������� ���� �� camera API
			}
			// Start the capture engine (API)											������ ��������� ������� ������
			newSensor->StartCapture();
			for (AVT::VmbAPI::FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)
			{
				// Put frame into the frame queue										��������� ���� � ������� ������
				newSensor->QueueFrame(*iter);
			}
			// Start the acquisition engine (camera)									��������� �������� ����� ������ (������)
			newSensor->GetFeatureByName("AcquisitionStart", pFeature);						//AcquisitionStart ������ ��������� �����������
			pFeature->RunCommand();
			acquisitionMode = "AcquisitionStart";
		}
	}
	catch (...)
	{
		LOG.logMessege("frame read error", _ERROR_);
	}
	LOG.logMessege("Camera connected", _INFO_);
	QtGuiSimulator::ui.widget_DisplayImg->setActivProcessObj(loadObj[activLoadObj]);
}