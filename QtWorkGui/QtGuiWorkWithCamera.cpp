#include "QtGuiWorkWithCamera.h"

QtGuiWorkWithCamera::QtGuiWorkWithCamera(QWidget* parent)
	: QtGuiSimulator(parent),
	cameraLife("sensor life", "", "sensor", cv::Mat(), QPixmap(), false),
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
	QtGuiSimulator::ui.widget_DisplayImg->setActivProcessObj(&loadObj[activLoadObj]);
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

void QtGuiWorkWithCamera::setupGui()
{
	QtGuiSimulator::ui.horizontalLayout_4->insertWidget(0, ui.PB_play);
	QtGuiSimulator::ui.horizontalLayout_4->insertWidget(1, ui.PB_parametrs);
	QtGuiSimulator::ui.pushButton_SetupSimltr->hide();
	QtGuiSimulator::ui.verticalLayout->insertWidget(0, ui.PB_sensorSetup);
}

void QtGuiWorkWithCamera::slot_play()
{
	isPlay = true;
	QtGuiSimulator::ui.widget_DisplayImg->setActivProcessObj(&cameraLife);
	QtGuiSimulator::ui.widget_DisplayImg->setProcessObjStatus(false);
	QtGuiSimulator::ui.linEdit_fileName->setText(cameraLife.getFileName());
}

void QtGuiWorkWithCamera::slot_stop()
{
	//pFeature->GetName(Str);
	//if (Str == "AcquisitionStart")
	//{
	//	// Stop the acquisition engine (camera)
	//	camera->GetFeatureByName("AcquisitionStop", pFeature);
	//	pFeature->RunCommand();

	//	// Stop the capture engine (API)
	//	// Flush the frame queue 
	//	// Revoke all frames from the API 
	//	camera->EndCapture();
	//	camera->FlushQueue();
	//	Str = "AcquisitionStop";
	//}
	isPlay = false;
	QtGuiSimulator::ui.widget_DisplayImg->setActivProcessObj(&loadObj[activLoadObj]);
	QtGuiSimulator::ui.widget_DisplayImg->setProcessObjStatus(true);
	QtGuiSimulator::ui.linEdit_fileName->setText(loadObj[activLoadObj].getFileName());
}

void QtGuiWorkWithCamera::slot_openSetupCamera()
{
	sensorSetup = new QtGuiSetupSensor();
	sensorSetup->show();
	connect(this, SIGNAL(dataToSetingSensor(ProcessedObj*, CameraPtrVector&, int)), sensorSetup, SLOT(slot_dataFromWorkWithSensor(ProcessedObj*, CameraPtrVector&, int)));
	connect(QtGuiSimulator::ui.widget_DisplayImg, SIGNAL(signal_updateFrame()), this, SLOT(slot_updateFrameInSetupSensor()));
	emit dataToSetingSensor(QtGuiSimulator::ui.widget_DisplayImg->getActivObject(), cameras, m_index);
	
}

void QtGuiWorkWithCamera::slot_updateFrameInSetupSensor()
{
	emit dataToSetingSensor(&cameraLife, cameras, m_index);
}

void QtGuiWorkWithCamera::slot_updateFrame()
{
	if (isPlay)
		QtGuiSimulator::ui.widget_DisplayImg->updateProcessObj(&cameraLife);
}

void QtGuiWorkWithCamera::slot_setNewActivObj(int newActivObject)
{
	activLoadObj = newActivObject;
	if (!isPlay)
	{
		QtGuiSimulator::ui.widget_DisplayImg->setActivProcessObj(&loadObj[activLoadObj]);
	}
}

void QtGuiWorkWithCamera::slot_getCameraInformation(CameraPtrVector& cams, int index)
{
	cameras = cams;
	m_index = index;
	LOG.logMessege("start conect with in QtGuiWorkWithCamera", _INFO_);
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
				(*iter)->RegisterObserver(IFrameObserverPtr(new FrameObserver(camera, QtGuiSimulator::ui.widget_DisplayImg, img, makePhoto, &cameraLife)));
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
	LOG.logMessege("Camera connected", _INFO_);
}