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
			//system.Startup();  // Процесс запускаем в QtConnect
			//system.GetCameras(cameras);

			camera = cameras[m_index];													//первую из списка камеру присваиваем
			camera->Open(VmbAccessModeFull);											//открываем камеру в режиме "доступ для чтения и записи". Используйте этот режим для настройки функций камеры и получения изображений

			/***********************************
			////binning разрешения в tab2
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

			camera->GetFeatureByName("PayloadSize", pFeature);							//Получить функцию по имени "Размер полезной нагрузки"(Размер кадра камеры). Полученную функцию возвращаем в pFeature  Feature-характеристика, функция
			pFeature->GetValue(nPLS);													//Запрос значения размера полезной нагрузки

			//cv::Mat df(0, 0, CV_8UC1);
			for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - вектор указателей на кадры, frames.begin()- первый кадр, frames.end()- последний кадр. Цикл прохождения по каждому кадру
			{
				(*iter).reset(new Frame(nPLS));											//сброс предыдущих настроек. Указываем новый размер для ,буффера кадра ( теперь он будет равен величине nPLS)
				//obs = 

				//(*iter)->RegisterObserver(IFrameObserverPtr(new FirstFrameObserver(camera, &ui, &df)));//Зарегистрировать наблюдателя camera(уже ссылается на нашу камеру,которую мы присвоили по ID)
				(*iter)->RegisterObserver(IFrameObserverPtr(new FrameObserver(camera, QtGuiSimulator::ui, img, makePhoto, &loadObj[0])));
				camera->AnnounceFrame(*iter);
				//Предоставляем кадр из camera API
			}
			makePhoto = false;
			// Start the capture engine (API)											Запуск механизма захвата кадров
			camera->StartCapture();
			for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)
			{
				// Put frame into the frame queue										Поместить кадр в очередь кадров
				camera->QueueFrame(*iter);
			}
			// Start the acquisition engine (camera)									Запустите механизм сбора данных (камеру)
			camera->GetFeatureByName("AcquisitionStart", pFeature);						//AcquisitionStart начать получение изображения
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