#include "QtGuiWorkWithCamera.h"

QtGuiWorkWithCamera::QtGuiWorkWithCamera(QWidget *parent)
	: QtGuiSimulator(parent),
	PB_play(nullptr),
	PB_parametrs(nullptr)
{
	LOG.logMessege("QtGuiWorkWithCamera constructor started",_DEBUG_);
	ui.setupUi(this);
	PB_play = new QPushButton(this);
	PB_parametrs = new QPushButton(this);
	PB_play->setMaximumSize(QSize(40, 40));
	PB_play->setMinimumSize(QSize(40, 40));
	PB_parametrs->setMaximumSize(QSize(40, 40));
	PB_parametrs->setMinimumSize(QSize(40, 40));
	PB_play->setIcon(QIcon("icon/play.png"));
	PB_play->setIconSize(QSize(40, 40));
	PB_parametrs->setIcon(QIcon("icon/parametrs.png"));
	PB_parametrs->setIconSize(QSize(40, 40));
	QtGuiSimulator::ui.horizontalLayout_4->insertWidget(0, PB_play);
	QtGuiSimulator::ui.horizontalLayout_4->insertWidget(1, PB_parametrs);
	PB_play->show();
	PB_parametrs->show();
	connect(PB_play, SIGNAL(clicked()), this, SLOT(slot_play()));
	connect(PB_parametrs, SIGNAL(clicked()), this, SLOT(slot_stop()));
}

QtGuiWorkWithCamera::~QtGuiWorkWithCamera()
{
	LOG.logMessege("QtGuiWorkWithCamera destruct started", _DEBUG_);
	camera->RevokeAllFrames();
	camera->Close();
	system.Shutdown(); // Always pair sys.Startup and sys.Shutdown
	LOG.logMessege("QtGuiWorkWithCamera destruct fineshed", _DEBUG_);
}

void QtGuiWorkWithCamera::readVideo(cv::Mat* newFrameMat, QPixmap* newFramePixmap)
{
	LOG.logMessege("set frame in QtGuiWorkWithCamera", _DEBUG_);
	loadObj[activLoadObj].SetObjParams("", "", *newFrameMat, *newFramePixmap, false);
}

void QtGuiWorkWithCamera::slot_play()
{
	LOG.logMessege("start video in QtGuiWorkWithCamera", _INFO_);
	try {
		if (Str == "AcquisitionStop")
		{
			//ui.stackedWidget->setCurrentIndex(1);
			//system.Startup();  // ������� ��������� � QtConnect
			//system.GetCameras(cameras);

			camera = cameras[m_index];													//������ �� ������ ������ �����������
			camera->Open(VmbAccessModeFull);											//��������� ������ � ������ "������ ��� ������ � ������". ����������� ���� ����� ��� ��������� ������� ������ � ��������� �����������

			/***********************************
			////binning ���������� � tab2
			//camera->GetFeatureByName("BinningHorizontal", pFeature);
			//pFeature->SetValue(6);
			//camera->GetFeatureByName("BinningVertical", pFeature);
			//pFeature->SetValue(6);
			//camera->GetFeatureByName("Height", pFeature);
			//pFeature->SetValue(541);
			//camera->GetFeatureByName("Width", pFeature);
			//pFeature->SetValue(812);
			//camera->GetFeatureByName("OffsetX", pFeature);
			//pFeature->SetValue(0);
			//camera->GetFeatureByName("OffsetY", pFeature);
			//pFeature->SetValue(0);
			****************************************/

			camera->GetFeatureByName("PayloadSize", pFeature);							//�������� ������� �� ����� "������ �������� ��������"(������ ����� ������). ���������� ������� ���������� � pFeature  Feature-��������������, �������
			pFeature->GetValue(nPLS);													//������ �������� ������� �������� ��������

			//cv::Mat df(0, 0, CV_8UC1);
			for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - ������ ���������� �� �����, frames.begin()- ������ ����, frames.end()- ��������� ����. ���� ����������� �� ������� �����
			{
				(*iter).reset(new Frame(nPLS));											//����� ���������� ��������. ��������� ����� ������ ��� ,������� ����� ( ������ �� ����� ����� �������� nPLS)
				//obs = 

				//(*iter)->RegisterObserver(IFrameObserverPtr(new FirstFrameObserver(camera, &ui, &df)));//���������������� ����������� camera(��� ��������� �� ���� ������,������� �� ��������� �� ID)
				(*iter)->RegisterObserver(IFrameObserverPtr(new FrameObserver(camera, QtGuiSimulator::ui, img, makePhoto, &loadObj[0])));
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
}

void QtGuiWorkWithCamera::slot_stop()
{
	pFeature->GetName(Str);
	if (Str == "AcquisitionStart")
	{
		// Stop the acquisition engine (camera)
		camera->GetFeatureByName("AcquisitionStop", pFeature);
		pFeature->RunCommand();

		// Stop the capture engine (API)
		// Flush the frame queue 
		// Revoke all frames from the API 
		camera->EndCapture();
		camera->FlushQueue();
		Str = "AcquisitionStop";
	}
}

void QtGuiWorkWithCamera::slot_getCameraInformation(CameraPtrVector& cams, int index)
{
	cameras = cams;
	m_index = index;
}