#include "QtGuiSetupSensor.h"


QtGuiSetupSensor::QtGuiSetupSensor(QWidget* parent)
	: QtSetupSimulator(parent),
	maxFrameSize{ QSizeF(4872.0, 3248.0) },
	chagheROI{ false },
	updateCameraParams{ false },
	oldFrameDelay{ 0 }
{
	ui.setupUi(this);
	setUpGui();
	firstStepEnable = true;
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(false);
	connect(QtSetupSimulator::ui.pushButton_step1, SIGNAL(clicked()), this, SLOT(slot_pushStep1()));
	connect(QtSetupSimulator::ui.pushButton_step2, SIGNAL(clicked()), this, SLOT(slot_pushStep2()));
	connect(QtSetupSimulator::ui.pushButton_step3, SIGNAL(clicked()), this, SLOT(slot_pushStep3()));
	connect(QtSetupSimulator::ui.pushButton_step4, SIGNAL(clicked()), this, SLOT(slot_pushStep4()));
	connect(ui.setRoiWid, SIGNAL(CoordItemChange(QRectF&)), this, SLOT(slot_setOffset(QRectF&)));		    //при изменении положения РОИ меняются значения спинбоксов
	connect(ui.setRoiWid, SIGNAL(ItemFromWidgetSizeChange(QSizeF&)), this, SLOT(slot_setSizeItemInSpinBox(QSizeF&)));		//при изменении width ,height ROI изменяется значение в спинбоксах
	connect(this, SIGNAL(sl_buttonChangeSizeClicked(double)), ui.setRoiWid, SLOT(st_buttonChangeSizeClicked(double)));
	connect(ui.SpinB_binningHor, SIGNAL(valueChanged(int)), this, SLOT(slot_changeBinning(int)));		//binning horizontal
	connect(ui.SpinB_binningVer, SIGNAL(valueChanged(int)), this, SLOT(slot_changeBinning(int)));		//binning vertical
	connect(ui.PB_setRoi,SIGNAL(clicked()),this,SLOT(slot_pushSetRoi()));
	connect(ui.PB_full,SIGNAL(clicked()),this,SLOT(slot_pushFull()));
	connect(ui.PB_oneQuarter,SIGNAL(clicked()),this,SLOT(slot_pushOneQuarter()));
	connect(ui.PB_oneEighth,SIGNAL(clicked()),this,SLOT(slot_pushOneEighth()));
	connect(ui.PB_continuous,SIGNAL(clicked()),this,SLOT(slot_pushContinous()));
	connect(ui.PB_once,SIGNAL(clicked()),this,SLOT(slot_pushOnce()));
	connect(ui.PB_off,SIGNAL(clicked()),this,SLOT(slot_pushOff()));
	connect(ui.SpinB_ofsetX,SIGNAL(valueChanged(int)),this,SLOT(slot_cahgeOfsetX(int)));
	connect(ui.SpinB_ofsetY,SIGNAL(valueChanged(int)),this,SLOT(slot_cahgeOfsetY(int)));
	connect(ui.SpinB_height,SIGNAL(valueChanged(int)),this,SLOT(slot_cahgeHeigth(int)));
	connect(ui.SpinB_width,SIGNAL(valueChanged(int)),this,SLOT(slot_cahgeWidth(int)));
	connect(this, SIGNAL(signal_getNewOffsetX(int)), ui.setRoiWid, SLOT(slot_setNewOffsetX(int)));
	connect(this, SIGNAL(signal_getNewOffsetY(int)), ui.setRoiWid, SLOT(slot_setNewOffsetY(int)));
	connect(this, SIGNAL(signal_getNewHeigth(int)), ui.setRoiWid, SLOT(slot_setNewHeigth(int)));
	connect(this, SIGNAL(signal_getNewWidth(int)), ui.setRoiWid, SLOT(slot_setNewWidth(int)));

	connect(ui.horSlider_exprosureSeconds, SIGNAL(valueChanged(int)), this, SLOT(slot_changeExprosureSeconds(int)));
	connect(ui.horSlider_exprosureMilSeconds, SIGNAL(valueChanged(int)), this, SLOT(slot_changeExprosureMilSeconds(int)));
	connect(ui.horSlider_exprosureMicSeconds, SIGNAL(valueChanged(int)), this, SLOT(slot_changeExprosureMicSeconds(int)));
	connect(ui.horSlider_exprosureSeconds, SIGNAL(valueChanged(int)), this, SLOT(slot_changeExprosure()));
	connect(ui.horSlider_exprosureMilSeconds, SIGNAL(valueChanged(int)), this, SLOT(slot_changeExprosure()));
	connect(ui.horSlider_exprosureMicSeconds, SIGNAL(valueChanged(int)), this, SLOT(slot_changeExprosure()));
	//connect(ui.spinB_trigerDelay, SIGNAL(valueChanged(int)), QtSetupSimulator::ui.widget_getMasterImg, SLOT(slot_updateTrigerDelay(int)));

}

QtGuiSetupSensor::~QtGuiSetupSensor()
{

}



double QtGuiSetupSensor::getKoefficient(int value)
{
	return 1.0 / (1 + abs(ui.SpinB_binningHor->value() - ui.SpinB_binningVer->value()));
}

void QtGuiSetupSensor::setUpGui()
{
	HL_forFirstStep = new QHBoxLayout();
	QtSetupSimulator::ui.page_step1->setLayout(HL_forFirstStep);
	HL_forFirstStep->addWidget(ui.setupSensorParams);
}

void QtGuiSetupSensor::setCameraParamsInGui()
{
	VmbInt64_t buferForIntParams{ 0 };
	AVT::VmbAPI::FeaturePtr pFeature;
	AVT::VmbAPI::CameraPtr camera{ sensorObject->getCameraPtr() };
	camera->GetFeatureByName("BinningHorizontal", pFeature);
	pFeature->GetValue(buferForIntParams);
	ui.SpinB_binningHor->setValue(static_cast<int>(buferForIntParams));

	camera->GetFeatureByName("BinningVertical", pFeature);
	pFeature->GetValue(buferForIntParams);
	ui.SpinB_binningVer->setValue(static_cast<int>(buferForIntParams));

	camera->GetFeatureByName("Height", pFeature);
	pFeature->GetValue(buferForIntParams);
	ui.SpinB_height->setValue(static_cast<int>(buferForIntParams));

	camera->GetFeatureByName("Width", pFeature);
	pFeature->GetValue(buferForIntParams);
	ui.SpinB_width->setValue(static_cast<int>(buferForIntParams));

	camera->GetFeatureByName("OffsetX", pFeature);
	pFeature->GetValue(buferForIntParams);
	ui.SpinB_ofsetX->setValue(static_cast<int>(buferForIntParams));

	camera->GetFeatureByName("OffsetY", pFeature);
	pFeature->GetValue(buferForIntParams);
	ui.SpinB_ofsetY->setValue(static_cast<int>(buferForIntParams));

	setExprosureValue();

	std::string buferForStringParams{};
	camera->GetFeatureByName("ExposureAuto", pFeature);
	pFeature->GetValue(buferForStringParams);
	if (buferForStringParams == "Continuous")
	{
		ui.PB_off->setDown(false);
		ui.PB_once->setDown(false);
		ui.PB_continuous->setDown(true);
		ui.LE_exprosureMilSeconds->setEnabled(false);
		ui.LE_exprosureMicSecods->setEnabled(false);
		ui.LE_exprosureSeconds->setEnabled(false);
		ui.horSlider_exprosureMicSeconds->setEnabled(false);
		ui.horSlider_exprosureMilSeconds->setEnabled(false);
		ui.horSlider_exprosureSeconds->setEnabled(false);
	}
	else if (buferForStringParams == "Once")
	{
		ui.PB_off->setDown(false);
		ui.PB_once->setDown(true);
		ui.PB_continuous->setDown(false);
		ui.LE_exprosureMilSeconds->setEnabled(false);
		ui.LE_exprosureMicSecods->setEnabled(false);
		ui.LE_exprosureSeconds->setEnabled(false);
		ui.horSlider_exprosureMicSeconds->setEnabled(false);
		ui.horSlider_exprosureMilSeconds->setEnabled(false);
		ui.horSlider_exprosureSeconds->setEnabled(false);
	}
	else if (buferForStringParams == "Off")
	{
		ui.PB_off->setDown(true);
		ui.PB_once->setDown(false);
		ui.PB_continuous->setDown(false);

		ui.LE_exprosureMilSeconds->setEnabled(true);
		ui.LE_exprosureMicSecods->setEnabled(true);
		ui.LE_exprosureSeconds->setEnabled(true);
		ui.horSlider_exprosureMicSeconds->setEnabled(true);
		ui.horSlider_exprosureMilSeconds->setEnabled(true);
		ui.horSlider_exprosureSeconds->setEnabled(true);
	}
}


void QtGuiSetupSensor::slot_updateSensorObject(ProcessedObjectSensor* sensorObj)
{
	sensorObject->updateMat(sensorObj->getOriginalMat(),sensorObj->getCorrectPixmap());
	setExprosureValue();
	if (!masterIsActivObject)
	{
		
		QtSetupSimulator::ui.widget_getMasterImg->updateProcessObj(*sensorObj); 
	}
}

void QtGuiSetupSensor::slot_pushStep1()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(false);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(*sensorObject);
	masterIsActivObject = false;
}

void QtGuiSetupSensor::slot_pushStep2()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(true);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(masterObjct);
	masterIsActivObject = true;
}

void QtGuiSetupSensor::slot_pushStep3()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(true);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(masterObjct);
	masterIsActivObject = true;
}

void QtGuiSetupSensor::slot_cahgeOfsetX(int newOffsetX)
{
	if (chagheROI)
	{
		ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() - newOffsetX);
		emit signal_getNewOffsetX(newOffsetX / (maxFrameSize.width() / ui.SpinB_binningHor->value() / ui.setRoiWid->size().width()));
	}
}

void QtGuiSetupSensor::slot_cahgeOfsetY(int newOffsetY)
{
	if (chagheROI)
	{
		ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() - newOffsetY);
		emit signal_getNewOffsetY(newOffsetY / (maxFrameSize.height() / ui.SpinB_binningVer->value() / ui.setRoiWid->size().height()));
	}
}

void QtGuiSetupSensor::slot_cahgeHeigth(int newHeigth)
{
	if (chagheROI)
	{
		ui.SpinB_ofsetY->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() - newHeigth);
		emit signal_getNewHeigth(newHeigth / (maxFrameSize.height() / ui.SpinB_binningVer->value() / ui.setRoiWid->size().height()));
	}
}

void QtGuiSetupSensor::slot_cahgeWidth(int newWidth)
{
	if (chagheROI)
	{
		ui.SpinB_ofsetX->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() - newWidth);
		emit signal_getNewWidth(newWidth / (maxFrameSize.width() / ui.SpinB_binningHor->value() / ui.setRoiWid->size().width()));
	}
}

void QtGuiSetupSensor::slot_setOffset(QRectF& point)
{
	chagheROI = false;
	ui.SpinB_ofsetY->setValue(point.y() * (maxFrameSize.height() / ui.SpinB_binningVer->value() / ui.setRoiWid->size().height()));
	ui.SpinB_ofsetX->setValue(point.x() * (maxFrameSize.width() / ui.SpinB_binningHor->value() / ui.setRoiWid->size().width()));
	ui.SpinB_height->setValue(point.height() * (maxFrameSize.height() / ui.SpinB_binningVer->value() / ui.setRoiWid->size().height()));
	ui.SpinB_width->setValue(point.width() * (maxFrameSize.width() / ui.SpinB_binningHor->value() / ui.setRoiWid->size().width()));

	ui.SpinB_ofsetY->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() - point.height());
	ui.SpinB_ofsetX->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() - point.width());
	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() - point.y());
	ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() - point.x());

	if (ui.SpinB_width->maximum() >= maxFrameSize.width() / ui.SpinB_binningHor->value())
		ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value());
	if (ui.SpinB_ofsetY->maximum() < 0)
		ui.SpinB_ofsetY->setMaximum(0);
	if (ui.SpinB_ofsetX->maximum() < 0)
		ui.SpinB_ofsetX->setMaximum(0);	
	if (ui.SpinB_height->maximum() >= maxFrameSize.height() / ui.SpinB_binningVer->value())
		ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value());
	chagheROI = true;
}

void QtGuiSetupSensor::slot_setSizeItemInSpinBox(QSizeF& itemSize)
{
	ui.SpinB_height->setValue(itemSize.height() * (maxFrameSize.height() / ui.SpinB_binningVer->value() / maxFrameSize.height()));
	ui.SpinB_width->setValue(itemSize.width() * (maxFrameSize.width() / ui.SpinB_binningHor->value() / maxFrameSize.width()));
}

void QtGuiSetupSensor::slot_changeBinning(int value)
{
	
	double K = this->getKoefficient(value);
	K = K + 0;

	if (ui.SpinB_binningHor->value() - ui.SpinB_binningVer->value() < 0) //		H - W
	{
		ui.setRoiWid->setFixedHeight(256 * K);  //H

	}
	else if (ui.SpinB_binningHor->value() - ui.SpinB_binningVer->value() > 0)
	{
		ui.setRoiWid->setFixedWidth(256 * K);  //W
	}
	else
	{
		ui.setRoiWid->setFixedWidth(256);  //W
		ui.setRoiWid->setFixedHeight(256);;  //H
	}
	
	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value());
	ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value());	
	
	chagheROI = false;
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value());
	ui.SpinB_width->setValue(maxFrameSize.width() / ui.SpinB_binningHor->value());
	chagheROI = true;
	
	emit sl_buttonChangeSizeClicked(1);
}

void QtGuiSetupSensor::slot_pushFull()
{
	ui.PB_full->setDown(true);
	ui.PB_oneEighth->setDown(false);//1/4
	ui.PB_oneQuarter->setDown(false);//1/8

	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value());
	ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value());

	chagheROI = false;
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value());
	ui.SpinB_width->setValue(maxFrameSize.width() / ui.SpinB_binningHor->value());
	chagheROI = true;
	emit sl_buttonChangeSizeClicked(1);
}

void QtGuiSetupSensor::slot_pushOneQuarter()
{
	ui.PB_full->setDown(false);
	ui.PB_oneQuarter->setDown(true);//1/4
	ui.PB_oneEighth->setDown(false);//1/8

	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() / 4);
	ui.SpinB_width->setMaximum((maxFrameSize.width() / ui.SpinB_binningHor->value() / 4));
	chagheROI = false;
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value() / 4);
	ui.SpinB_width->setValue((maxFrameSize.width() / ui.SpinB_binningHor->value() / 4));
	chagheROI = true;
	emit sl_buttonChangeSizeClicked(1.0 / 4);
}

void QtGuiSetupSensor::slot_pushOneEighth()
{
	ui.PB_full->setDown(false);
	ui.PB_oneQuarter->setDown(false);//1/4
	ui.PB_oneEighth->setDown(true);//1/8


	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() / 8);
	ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() / 8);

	chagheROI = false;
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value() / 8);
	ui.SpinB_width->setValue(maxFrameSize.width() / ui.SpinB_binningHor->value() / 8);
	chagheROI = true;
	emit sl_buttonChangeSizeClicked(1.0 / 8);
}

void QtGuiSetupSensor::slot_pushSetRoi()
{

	LOG.logMessege("Start changing camera settings", _INFO_);
	//camera->SaveCameraSettings("camera.xml");
	AVT::VmbAPI::FeaturePtr pFeature;
	AVT::VmbAPI::CameraPtr camera{ sensorObject->getCameraPtr() };
	camera->GetFeatureByName("AcquisitionStop", pFeature);
	pFeature->RunCommand();

	camera->EndCapture();
	camera->FlushQueue();
	camera->RevokeAllFrames();
	/***********************************/
	//binning разрешения в tab2
	camera->GetFeatureByName("BinningHorizontal", pFeature);
	pFeature->SetValue(ui.SpinB_binningHor->value());

	camera->GetFeatureByName("BinningVertical", pFeature);
	pFeature->SetValue(ui.SpinB_binningVer->value());

	camera->GetFeatureByName("Height", pFeature);
	pFeature->SetValue(ui.SpinB_height->value());

	camera->GetFeatureByName("Width", pFeature);
	int tmp = ui.SpinB_width->value();
	while (tmp % 4 != 0)
	{
		tmp++;
	}
	pFeature->SetValue(tmp);

	camera->GetFeatureByName("OffsetX", pFeature);
	pFeature->SetValue(ui.SpinB_ofsetX->value());

	camera->GetFeatureByName("OffsetY", pFeature);
	pFeature->SetValue(ui.SpinB_ofsetY->value());
	/****************************************/


	// Get the image size for the required buffer								Получите размер изображения для выбора необходимого буфера
	// Allocate memory for frame buffer											Выделите память для буфера,который будет хранить кадр
	// Register frame observer/callback for each frame							Зарегистрируйте наблюдатель кадров / обратный вызов для каждого кадра
	// Announce frame to the API												Предоставьте кадр API


	camera->GetFeatureByName("PayloadSize", pFeature);							//Получить функцию по имени "Размер полезной нагрузки"(Размер кадра камеры). Полученную функцию возвращаем в pFeature  Feature-характеристика, функция
	VmbInt64_t nPLS;// Payload size value
	VmbInt64_t oldNPLS{ nPLS };
	pFeature->GetValue(nPLS);													//Запрос значения размера полезной нагрузки

	AVT::VmbAPI::FramePtrVector frames{ 3 }; // Frame array
	for (AVT::VmbAPI::FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - вектор указателей на кадры, frames.begin()- первый кадр, frames.end()- последний кадр. Цикл прохождения по каждому кадру
	{
		if (oldNPLS!=nPLS)
			(*iter).reset(new AVT::VmbAPI::Frame(nPLS));											//сброс предыдущих настроек. Указываем новый размер для ,буффера кадра ( теперь он будет равен величине nPLS)
		//obs = 
		(*iter)->RegisterObserver(AVT::VmbAPI::IFrameObserverPtr(new FrameObserver(camera, videoDisplay,sensorObject)));//Зарегистрировать наблюдателя camera(уже ссылается на нашу камеру,которую мы присвоили по ID)
		camera->AnnounceFrame(*iter);											//Предоставляем кадр из camera API
	}
	//makePhoto = false;
	// Start the capture engine (API)											Запуск механизма захвата кадров
	camera->StartCapture();
	for (AVT::VmbAPI::FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)
	{
		// Put frame into the frame queue										Поместить кадр в очередь кадров
		camera->QueueFrame(*iter);
	}
	// Start the acquisition engine (camera)									Запустите механизм сбора данных (камеру)
	camera->GetFeatureByName("AcquisitionStart", pFeature);						//AcquisitionStart начать получение изображения
	pFeature->RunCommand();
	LOG.logMessege("Camera settings set", _INFO_);
}

void QtGuiSetupSensor::slot_pushContinous()
{
	ui.PB_off->setDown(false);
	ui.PB_once->setDown(false);
	ui.PB_continuous->setDown(true);

	AVT::VmbAPI::FeaturePtr pFeature;
	sensorObject->getCameraPtr()->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Continuous";
	pFeature->SetValue(temp);

	ui.LE_exprosureMilSeconds->setEnabled(false);
	ui.LE_exprosureMicSecods->setEnabled(false);
	ui.LE_exprosureSeconds->setEnabled(false);
	ui.horSlider_exprosureMicSeconds->setEnabled(false);
	ui.horSlider_exprosureMilSeconds->setEnabled(false);
	ui.horSlider_exprosureSeconds->setEnabled(false);
}

void QtGuiSetupSensor::slot_pushOnce()
{
	ui.PB_off->setDown(false);
	ui.PB_once->setDown(true);
	ui.PB_continuous->setDown(false);

	AVT::VmbAPI::FeaturePtr pFeature;
	sensorObject->getCameraPtr()->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Once";
	pFeature->SetValue(temp);

	ui.LE_exprosureMilSeconds->setEnabled(false);
	ui.LE_exprosureMicSecods->setEnabled(false);
	ui.LE_exprosureSeconds->setEnabled(false);
	ui.horSlider_exprosureMicSeconds->setEnabled(false);
	ui.horSlider_exprosureMilSeconds->setEnabled(false);
	ui.horSlider_exprosureSeconds->setEnabled(false);
}

void QtGuiSetupSensor::slot_pushOff()
{
	ui.PB_off->setDown(true);
	ui.PB_once->setDown(false);
	ui.PB_continuous->setDown(false);

	AVT::VmbAPI::FeaturePtr pFeature;
	sensorObject->getCameraPtr()->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Off";
	pFeature->SetValue(temp);

	ui.LE_exprosureMilSeconds->setEnabled(true);
	ui.LE_exprosureMicSecods->setEnabled(true);
	ui.LE_exprosureSeconds->setEnabled(true);
	ui.horSlider_exprosureMicSeconds->setEnabled(true);
	ui.horSlider_exprosureMilSeconds->setEnabled(true);
	ui.horSlider_exprosureSeconds->setEnabled(true);
}

void QtGuiSetupSensor::slot_dataToGuiWorkWithCamera()
{
	updateCameraParams = true;
}

void QtGuiSetupSensor::slot_changeExprosureSeconds(int newValue)
{
	ui.LE_exprosureSeconds->setText(QString::number(newValue));
	if (newValue == 60)
	{
		ui.LE_exprosureMilSeconds->setEnabled(false);
		ui.LE_exprosureMicSecods->setEnabled(false);
		ui.horSlider_exprosureMicSeconds->setEnabled(false);
		ui.horSlider_exprosureMilSeconds->setEnabled(false);
	}
	else if (!ui.LE_exprosureMicSecods->isEnabled() && ui.LE_exprosureSeconds->isEnabled())
	{
		ui.LE_exprosureMilSeconds->setEnabled(true);
		ui.LE_exprosureMicSecods->setEnabled(true);
		ui.horSlider_exprosureMicSeconds->setEnabled(true);
		ui.horSlider_exprosureMilSeconds->setEnabled(true);
	}
}

void QtGuiSetupSensor::slot_changeExprosureMilSeconds(int newValue)
{
	ui.LE_exprosureMilSeconds->setText(QString::number(newValue));
}

void QtGuiSetupSensor::slot_changeExprosureMicSeconds(int newValue)
{
	ui.LE_exprosureMicSecods->setText(QString::number(newValue));
}

void QtGuiSetupSensor::slot_dataFromWorkWithSensor(ProcessedObjectSensor* sensorObj, ProcessedObject* masterObj, QtGuiDisplay* videoDisplay_)
{
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(*sensorObj);
	slot_dataFromGUISim(*masterObj);
	sensorObject = sensorObj;
	sensorObject->getCameraPtr()->SaveCameraSettings("oldCameraParams.xml");
	masterIsActivObject = false;
	videoDisplay = videoDisplay_;
	oldFrameDelay = sensorObj->getFrameDelay();
	ui.spinB_trigerDelay->setValue(sensorObject->getFrameDelay());
	setCameraParamsInGui();
	connect(ui.spinB_trigerDelay, SIGNAL(valueChanged(int)), videoDisplay, SLOT(slot_updateTrigerDelay(int)));
	connect(ui.PB_setRoi, SIGNAL(clicked()), videoDisplay, SLOT(slot_delUpdateImageTime()));
}

void QtGuiSetupSensor::closeEvent(QCloseEvent* event)
{
	if (isClose)
	{
		if (!changes)
		{
			sensorObject->getCameraPtr()->LoadCameraSettings("oldCameraParams.xml");
			sensorObject->setFrameDelay(oldFrameDelay);
		}
		this->close();
	}
	QtSetupSimulator::closeEvent(event);
}

void QtGuiSetupSensor::setExprosureValue()
{
	double buferForDoubleParams{ 0.0 };
	AVT::VmbAPI::FeaturePtr pFeature;
	sensorObject->getCameraPtr()->GetFeatureByName("ExposureTimeAbs", pFeature);
	pFeature->GetValue(buferForDoubleParams);
	ui.horSlider_exprosureSeconds->setValue(static_cast<int>(buferForDoubleParams) / 1000000);
	ui.horSlider_exprosureMilSeconds->setValue((static_cast<int>(buferForDoubleParams) % 1000000) / 1000);
	ui.horSlider_exprosureMicSeconds->setValue(static_cast<int>(buferForDoubleParams) % 1000000000);
}

void QtGuiSetupSensor::slot_changeExprosure()
{
	if (ui.horSlider_exprosureSeconds->value() != 60)
		ui.LE_exprosureSumm->setText(QString::number(ui.horSlider_exprosureSeconds->value() * 1000000 + ui.horSlider_exprosureMilSeconds->value() * 1000 + ui.horSlider_exprosureMicSeconds->value()));
	else
		ui.LE_exprosureSumm->setText(QString::number(ui.horSlider_exprosureSeconds->value() * 1000000));
	
	if (ui.horSlider_exprosureSeconds->isEnabled())
	{
		AVT::VmbAPI::FeaturePtr pFeature;
		sensorObject->getCameraPtr()->GetFeatureByName("ExposureTimeAbs", pFeature);
		pFeature->SetValue(ui.LE_exprosureSumm->text().toDouble());
	}
}
