#include "QtGuiSetupSensor.h"


QtGuiSetupSensor::QtGuiSetupSensor(QWidget *parent)
	: QtSetupSimulator(parent),
	maxFrameSize(QSizeF(4872.0, 3248.0))
{
	ui.setupUi(this);
	setUpGui();
	firstStepEnable = true;
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(false);
	connect(QtSetupSimulator::ui.pushButton_step1, SIGNAL(clicked()), this, SLOT(slot_pushStep1()));
	connect(QtSetupSimulator::ui.pushButton_step2, SIGNAL(clicked()), this, SLOT(slot_pushStep2()));
	connect(QtSetupSimulator::ui.pushButton_step3, SIGNAL(clicked()), this, SLOT(slot_pushStep3()));
	connect(QtSetupSimulator::ui.pushButton_step4, SIGNAL(clicked()), this, SLOT(slot_pushStep4()));
	connect(ui.setRoiWid, SIGNAL(CoordItemChange(QPointF&)), this, SLOT(slot_setOffset(QPointF&)));		    //при изменении положения РОИ меняются значения спинбоксов
	connect(ui.setRoiWid, SIGNAL(ItemFromWidgetSizeChange(QPointF&)), this, SLOT(slot_setSizeItemInSpinBox(QPointF&)));		//при изменении width ,height ROI изменяется значение в спинбоксах
	connect(this, SIGNAL(sl_buttonChangeSizeClicked(double)), ui.setRoiWid, SLOT(st_buttonChangeSizeClicked(double)));
	connect(ui.SpinB_binningHor, SIGNAL(valueChanged(int)), this, SLOT(slot_changeBinning(int)));		//binning horizontal
	connect(ui.SpinB_binningVer, SIGNAL(valueChanged(int)), this, SLOT(slot_changeBinning(int)));		//binning vertical
	connect(ui.PB_setRoi,SIGNAL(clicked()),this,SLOT(slot_pushSetRoi()));
	connect(ui.PB_full,SIGNAL(clicked()),this,SLOT(slot_pushFull()));
	connect(ui.PB_oneQuarter,SIGNAL(clicked()),this,SLOT(slot_pushOneQuarter()));
	connect(ui.PB_oneEighth,SIGNAL(clicked()),this,SLOT(slot_pushOneEighth()));
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

void QtGuiSetupSensor::slot_updateSensorObject(ProcessedObj* sensorObj)
{
	sensorObject = sensorObj;
	if (!masterIsActivObject)
	{
		QtSetupSimulator::ui.widget_getMasterImg->updateProcessObj(sensorObj);
	}
}

void QtGuiSetupSensor::slot_pushStep1()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(false);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(sensorObject);
	masterIsActivObject = false;
}

void QtGuiSetupSensor::slot_pushStep2()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(true);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(&masterObjct);
	masterIsActivObject = true;
}

void QtGuiSetupSensor::slot_pushStep3()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(true);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(&masterObjct);
	masterIsActivObject = true;
}

void QtGuiSetupSensor::slot_setOffset(QPointF& point)
{
	ui.SpinB_ofsetY->setValue(point.y() * (maxFrameSize.height() / ui.SpinB_binningVer->value() / ui.setRoiWid->size().height()));
	ui.SpinB_ofsetX->setValue(point.x() * (maxFrameSize.width() / ui.SpinB_binningHor->value() / ui.setRoiWid->size().width()));
}

void QtGuiSetupSensor::slot_setSizeItemInSpinBox(QPointF& itemSize)
{
	ui.SpinB_height->setValue(itemSize.y() * (maxFrameSize.height() / ui.SpinB_binningVer->value() / 256.0));
	ui.SpinB_width->setValue(itemSize.x() * (4872.0 / ui.SpinB_binningHor->value() / 256.0));
}

void QtGuiSetupSensor::slot_changeBinning(int value)
{
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_ofsetY->setValue(0);
	//ui.widget->resize(350, 200);
	double K = this->getKoefficient(value);
	K = K + 0;

	//m_kW = 4872 / ui.SpinB_binningVer->value() / 256;
	//m_kH = 3248 / ui.SpinB_binningHor->value() / 256;

	if (ui.SpinB_binningHor->value() - ui.SpinB_binningVer->value() < 0) //		H - W
	{
		//ui.widget->setGeometry(10, 10, 300.0 * K, 250 );
		ui.setRoiWid->setFixedHeight(256 * K);  //H

	}
	else if (ui.SpinB_binningHor->value() - ui.SpinB_binningVer->value() > 0)
	{
		//.widget->setGeometry(10, 10, 300 , 250 * K);
		ui.setRoiWid->setFixedWidth(256 * K);  //W
	}
	else
	{
		ui.setRoiWid->setFixedWidth(256);  //W
		ui.setRoiWid->setFixedHeight(256);;  //H
	}

	emit sl_buttonChangeSizeClicked(1);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningHor->value());
	ui.SpinB_width->setValue(maxFrameSize.width() / ui.SpinB_binningVer->value());
}

void QtGuiSetupSensor::slot_pushFull()
{
	ui.PB_full->setDown(true);
	ui.PB_oneEighth->setDown(false);//1/4
	ui.PB_oneQuarter->setDown(false);//1/8

	//ui.spinBox_5->setValue(ui.widget->height() * (3248 / ui.spinBox_2->value() / 250));
	//ui.spinBox_6->setValue(ui.widget->width() * (4872 / ui.spinBox->value() / 300));


	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value());
	ui.SpinB_width->setValue(maxFrameSize.width() / ui.SpinB_binningHor->value());

	emit sl_buttonChangeSizeClicked(1);
}

void QtGuiSetupSensor::slot_pushOneQuarter()
{
	ui.PB_full->setDown(false);
	ui.PB_oneQuarter->setDown(true);//1/4
	ui.PB_oneEighth->setDown(false);//1/8

	//ui.spinBox_5->setValue(ui.widget->height()/4 * (3248 / ui.spinBox_2->value() / 250));
	//ui.spinBox_6->setValue(ui.widget->width()/4 * (4872 / ui.spinBox->value() / 300));

	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value() / 4);
	ui.SpinB_width->setValue((maxFrameSize.width() / ui.SpinB_binningHor->value() / 4));

	emit sl_buttonChangeSizeClicked(1.0 / 4);
}

void QtGuiSetupSensor::slot_pushOneEighth()
{
	ui.PB_full->setDown(false);
	ui.PB_oneQuarter->setDown(false);//1/4
	ui.PB_oneEighth->setDown(true);//1/8

	/*ui.spinBox_5->setValue(ui.widget->height() / 8 * (3248 / ui.spinBox_2->value() / 250));
	ui.spinBox_6->setValue(ui.widget->width() / 8 * (4872 / ui.spinBox->value() / 300));*/
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value() / 8);
	ui.SpinB_width->setValue(maxFrameSize.width() / ui.SpinB_binningHor->value() / 8);

	emit sl_buttonChangeSizeClicked(1.0 / 8);
}

void QtGuiSetupSensor::slot_pushSetRoi()
{
	LOG.logMessege("Start changing camera settings", _INFO_);
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
	VmbInt64_t oldNPLS{ nPLS };
	pFeature->GetValue(nPLS);													//Запрос значения размера полезной нагрузки


	for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - вектор указателей на кадры, frames.begin()- первый кадр, frames.end()- последний кадр. Цикл прохождения по каждому кадру
	{
		if (oldNPLS!=nPLS)
			(*iter).reset(new Frame(nPLS));											//сброс предыдущих настроек. Указываем новый размер для ,буффера кадра ( теперь он будет равен величине nPLS)
		//obs = 
		(*iter)->RegisterObserver(IFrameObserverPtr(new FrameObserver(camera, videoDisplay,sensorObject)));//Зарегистрировать наблюдателя camera(уже ссылается на нашу камеру,которую мы присвоили по ID)
		camera->AnnounceFrame(*iter);											//Предоставляем кадр из camera API
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
	LOG.logMessege("Camera settings set", _INFO_);
}

void QtGuiSetupSensor::slot_pushContinous()
{
	ui.PB_off->setDown(false);
	ui.PB_once->setDown(false);
	ui.PB_continuous->setDown(true);

	camera->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Continuous";
	pFeature->SetValue(temp);
}

void QtGuiSetupSensor::slot_pushOnce()
{
	ui.PB_off->setDown(false);
	ui.PB_once->setDown(true);
	ui.PB_continuous->setDown(false);

	camera->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Once";
	pFeature->SetValue(temp);
}

void QtGuiSetupSensor::slot_pushOff()
{
	ui.PB_off->setDown(true);
	ui.PB_once->setDown(false);
	ui.PB_continuous->setDown(false);

	camera->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Off";
	pFeature->SetValue(temp);
}

void QtGuiSetupSensor::slot_dataFromWorkWithSensor(ProcessedObj* sensorObj, ProcessedObj* masterObj, CameraPtr& cams, int index, QtGuiDisplay* videoDisplay_)
{
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(sensorObj);
	masterObjct = *masterObj;
	sensorObject = sensorObj;
	masterIsActivObject = false;
	camera = cams;
	videoDisplay = videoDisplay_;
	connect(ui.spinB_trigerDelay, SIGNAL(valueChanged(int)), videoDisplay, SLOT(slot_updateTrigerDelay(int)));
}