#include "QtGuiWorkWithCamera.h"

QtGuiWorkWithCamera::QtGuiWorkWithCamera(QWidget* parent)
	: QtGuiSimulator(parent),
	sensorLife("sensor life", "", cv::Mat(), QPixmap(), true),
	isPlay(false)
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

void QtGuiWorkWithCamera::readVideo(cv::Mat* newFrameMat, QPixmap* newFramePixmap)
{
	LOG.logMessege("set frame in QtGuiWorkWithCamera", _DEBUG_);
	loadObj[activLoadObj]=ProcessedObject("", "", *newFrameMat, *newFramePixmap, loadObj[activLoadObj].getProgramName(), false);
	//loadObj[activLoadObj].SetObjParams("", "", *newFrameMat, *newFramePixmap, false);
}

void QtGuiWorkWithCamera::setupGui()
{
	QtGuiSimulator::ui.horizontalLayout_4->insertWidget(0, ui.PB_play);
	QtGuiSimulator::ui.horizontalLayout_4->insertWidget(1, ui.PB_parametrs);
	QtGuiSimulator::ui.pushButton_SetupSimltr->hide();
	QtGuiSimulator::ui.verticalLayout->insertWidget(0, ui.PB_sensorSetup);
}

void QtGuiWorkWithCamera::closeEvent(QCloseEvent* event)
{
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
	connect(this, SIGNAL(dataToSetingSensor(ProcessedObjectSensor*, ProcessedObject*, CameraPtr&, int,QtGuiDisplay*)), sensorSetup, SLOT(slot_dataFromWorkWithSensor(ProcessedObjectSensor*, ProcessedObject*, CameraPtr&, int,QtGuiDisplay*)));
	connect(this, SIGNAL(updateFrameInSetupSensor(ProcessedObjectSensor*)), sensorSetup, SLOT(slot_updateSensorObject(ProcessedObjectSensor*)));
	connect(QtGuiSimulator::ui.widget_DisplayImg, SIGNAL(signal_updateFrame()), this, SLOT(slot_updateFrameInSetupSensor()));
	connect(sensorSetup, SIGNAL(dataToGUISim(ProcessedObject*)), this, SLOT(slot_dataFromSetupSim(ProcessedObject*)));
	emit dataToSetingSensor(&sensorLife, &loadObj[activLoadObj], camera, QtGuiSimulator::ui.widget_DisplayImg->getDelayUpdateFrame(), QtGuiSimulator::ui.widget_DisplayImg);
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

void QtGuiWorkWithCamera::slot_getCameraInformation(CameraPtr newSensor)
{
	LOG.logMessege("start conect with in QtGuiWorkWithCamera", _INFO_);
	try {

		if (Str == "AcquisitionStop")
		{
			camera = newSensor;															//������ �� ������ ������ �����������
			camera->Open(VmbAccessModeFull);											//��������� ������ � ������ "������ ��� ������ � ������". ����������� ���� ����� ��� ��������� ������� ������ � ��������� �����������

			camera->GetFeatureByName("PayloadSize", pFeature);							//�������� ������� �� ����� "������ �������� ��������"(������ ����� ������). ���������� ������� ���������� � pFeature  Feature-��������������, �������
			pFeature->GetValue(nPLS);													//������ �������� ������� �������� ��������

			for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - ������ ���������� �� �����, frames.begin()- ������ ����, frames.end()- ��������� ����. ���� ����������� �� ������� �����
			{
				(*iter).reset(new Frame(nPLS));											//����� ���������� ��������. ��������� ����� ������ ��� ,������� ����� ( ������ �� ����� ����� �������� nPLS)
				(*iter)->RegisterObserver(IFrameObserverPtr(new FrameObserver(camera, QtGuiSimulator::ui.widget_DisplayImg, &sensorLife)));
				camera->AnnounceFrame(*iter);
				//������������� ���� �� camera API
			}
			makePhoto = false;
			// Start the capture engine (API)											������ ��������� ������� ������
			camera->StartCapture();
			for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)
			{
				// Put frame into the frame queue										��������� ���� � ������� ������
				camera->QueueFrame(*iter);
			}
			// Start the acquisition engine (camera)									��������� �������� ����� ������ (������)
			camera->GetFeatureByName("AcquisitionStart", pFeature);						//AcquisitionStart ������ ��������� �����������
			pFeature->RunCommand();
			Str = "AcquisitionStart";
		}

	}
	catch (...)
	{
		LOG.logMessege("frame read error", _ERROR_);
	}
	LOG.logMessege("Camera connected", _INFO_);
	QtGuiSimulator::ui.widget_DisplayImg->setActivProcessObj(loadObj[activLoadObj]);
}