#include "GE_Widget.h"

GE_Widget::GE_Widget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	ui.tab->setEnabled(false);
	ui.label->setPixmap(QPixmap::fromImage(QImage("logo.png")));

	//ui.scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//ui.scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.widget->setFixedHeight(256);
	ui.widget->setFixedWidth(256);

	ui.spinBox_5->setValue(3248 / ui.spinBox_2->value() / 4);//64 к 256
	ui.spinBox_6->setValue(4872 / ui.spinBox->value() / 4);//64 к 256

	ui.label->installEventFilter(this); //запускаем фильтр событий

	connect(ui.widget, SIGNAL(CoordItemChange(QPointF&)), this, SLOT(setOffset(QPointF&)));		    //при изменении положения РОИ меняются значения спинбоксов
	connect(ui.widget, SIGNAL(ItemFromWidgetSizeChange(QPointF&)), this, SLOT(SetSizeItemInSpinBox(QPointF&)));		//при изменении width ,height ROI изменяется значение в спинбоксах
	connect(this, SIGNAL(sl_buttonChangeSizeClicked(double)), ui.widget, SLOT(st_buttonChangeSizeClicked(double)));

	//connect(ui.spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(st_SpinBoxChangeOff_Y_this(int)));		//offsetY когда с помощью кнопок меняем положение ROI
	//connect(ui.spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(st_SpinBoxChangeOff_X_this(int)));		//offsetX ROI
	//connect(ui.spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(st_ItemHeightChange_this(int)));		//при изменении height ROI в спинбоксах изменяется значение итема
	//connect(ui.spinBox_6, SIGNAL(valueChanged(int)), this, SLOT(st_ItemWidthChange_this(int)));		//при изменении width ROI в спинбоксах изменяется значение итема

	//connect(this, SIGNAL(sl_SpinBoxChangeOff_Y_this(int ,int )), ui.widget, SLOT(st_SpinBoxChangeOff_Y(int ,int)));		//offsetY когда с помощью кнопок меняем положение ROI
	//connect(this, SIGNAL(sl_SpinBoxChangeOff_X_this(int ,int )), ui.widget, SLOT(st_SpinBoxChangeOff_X(int ,int)));		//offsetX ROI
	//connect(this, SIGNAL(sl_ItemHeightChange_this(int ,int)), ui.widget, SLOT(st_ItemHeightChange(int , int)));		//при изменении height ROI в спинбоксах изменяется значение итема
	//connect(this, SIGNAL(sl_ItemWidthChange_this(int ,int)), ui.widget, SLOT(st_ItemWidthChange(int , int)));		//при изменении width ROI в спинбоксах изменяется значение итема

	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(st_ChangeBinning(int)));		//binning horizontal
	connect(ui.spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(st_ChangeBinning(int)));		//binning vertical

	//QImage myImage = QImage("D:/test.png");
	//ui.label->setPixmap(QPixmap::fromImage(myImage)); //вывод потока в лэйбл



	// Start the API, get and open cameras										Запускаем API, получаем и открываем камеру
	//system.Startup();
													//получаем список подключенных камер
	//system.GetCameraByID("169.254.197.209", camera);							//обнаружение камеры по IP, обнаруженную камеру возвращаем в camera
	//try {
		system.GetCameras(cameras);//получаем список подключенных камер
		/*
		if (cameras.size() == 0)
		{
			throw "Cameras not found";
		}
		*/
		try {

			camera = *cameras.begin();//первую из списка камеру присваиваем
		}
		catch (...)
		{
			myLoger.logMessege("cr");
			//myLoger.logMessege(a.what());
		}

		camera->Open(VmbAccessModeFull);											//открываем камеру в режиме "доступ для чтения и записи". Используйте этот режим для настройки функций камеры и получения изображений

		/******************************/

		//GetExposureAutoTargetFeature(feature, camera);
		//VmbInt64_t value;
		//GetExposureAutoTarget(value, camera);
		//SetExposureAutoTarget(50000, camera);

		/***ПРОВЕРИТЬ*****низ******ПРОВЕРИТЬ****ПРОВЕРИТЬ********ПРОВЕРИТЬ*********/
		camera->GetFeatureByName("PixelFormat", pFeature);
		char* temp = ui.comboBox->currentText().toLocal8Bit().data();//перевод в символьную переменную значения из комбобокса
		pFeature->SetValue(temp);  //RGB8Packed, YUV411Packed, BayerRG8, …

		/***********************************/
		//binning разрешения в tab2
		camera->GetFeatureByName("BinningHorizontal", pFeature);
		pFeature->SetValue(ui.spinBox->value());

		camera->GetFeatureByName("BinningVertical", pFeature);
		pFeature->SetValue(ui.spinBox_2->value());

		camera->GetFeatureByName("Height", pFeature);
		pFeature->SetValue(ui.spinBox_5->value());

		camera->GetFeatureByName("Width", pFeature);
		int tmp = ui.spinBox_6->value();
		while (tmp % 4 != 0)
		{
			tmp++;
		}
		pFeature->SetValue(tmp);

		camera->GetFeatureByName("OffsetX", pFeature);
		pFeature->SetValue(ui.spinBox_4->value());

		camera->GetFeatureByName("OffsetY", pFeature);
		pFeature->SetValue(ui.spinBox_3->value());
		/****************************************/


		// Get the image size for the required buffer								Получите размер изображения для выбора необходимого буфера
		// Allocate memory for frame buffer											Выделите память для буфера,который будет хранить кадр
		// Register frame observer/callback for each frame							Зарегистрируйте наблюдатель кадров / обратный вызов для каждого кадра
		// Announce frame to the API												Предоставьте кадр API


		camera->GetFeatureByName("PayloadSize", pFeature);							//Получить функцию по имени "Размер полезной нагрузки"(Размер кадра камеры). Полученную функцию возвращаем в pFeature  Feature-характеристика, функция
		pFeature->GetValue(nPLS);													//Запрос значения размера полезной нагрузки


		for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - вектор указателей на кадры, frames.begin()- первый кадр, frames.end()- последний кадр. Цикл прохождения по каждому кадру
		{
			(*iter).reset(new Frame(nPLS));											//сброс предыдущих настроек. Указываем новый размер для ,буффера кадра ( теперь он будет равен величине nPLS)
			//obs = 
			(*iter)->RegisterObserver(IFrameObserverPtr(new FrameObserver(camera, ui, img, makePhoto)));//Зарегистрировать наблюдателя camera(уже ссылается на нашу камеру,которую мы присвоили по ID)
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
	
	
}

GE_Widget::~GE_Widget()
{

	// Stop the capture engine (API)
	// Flush the frame queue 
	// Revoke all frames from the API 

	camera->EndCapture();
	camera->FlushQueue();
	//camera->RevokeAllFrames();

	//}
	camera->Close();
	//system.Shutdown(); // Always pair sys.Startup and sys.Shutdown
}

double GE_Widget::getKoefficient(int value)
{
	return 1.0 / (1 + abs(ui.spinBox->value() - ui.spinBox_2->value()));
}


void GE_Widget::st_ChangeBinning(int value)
{
	ui.spinBox_4->setValue(0);
	ui.spinBox_3->setValue(0);
	//ui.widget->resize(350, 200);
	double K = this->getKoefficient(value);
	K = K + 0;

	m_kW = 4872 / ui.spinBox_2->value() / 256;
	m_kH = 3248 / ui.spinBox->value() / 256;

	if (ui.spinBox->value() - ui.spinBox_2->value() < 0) //		H - W
	{
		//ui.widget->setGeometry(10, 10, 300.0 * K, 250 );
		ui.widget->setFixedHeight(256 * K);  //H

	}
	else if (ui.spinBox->value() - ui.spinBox_2->value() > 0)
	{
		//.widget->setGeometry(10, 10, 300 , 250 * K);
		ui.widget->setFixedWidth(256 * K);  //W
	}
	else
	{
		ui.widget->setFixedWidth(256);  //W
		ui.widget->setFixedHeight(256);;  //H
	}

	emit sl_buttonChangeSizeClicked(1);
	ui.spinBox_5->setValue(3248 / ui.spinBox->value());
	ui.spinBox_6->setValue(4872 / ui.spinBox_2->value());
}

bool GE_Widget::eventFilter(QObject* obj, QEvent* event)  //филтр событий для выцепливания нужного события связанного с нужным нам объектом
{
	if (obj == ui.label)//если событие пришло от сцены(нужный нам объект)
	{

		//смотрим,является ли пришедшее событие движением курсора(нужное нам событие)
		if (event->type() == QEvent::Wheel)
		{
			QWheelEvent* wheelEv = static_cast<QWheelEvent*> (event);
			wheelEvent(wheelEv);

			QPoint numDegrees = wheelEv->angleDelta() / 8;


			if (!numDegrees.isNull())
			{
				QPoint numSteps = numDegrees / 15;
				if (numSteps.y() < 0)
					scaledImages(0.8);
				else {
					scaledImages(1.25);
				}
				//scaledImages(1.25)(numSteps);
			}
			//ui.scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
			//ui.scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
			wheelEv->accept();

		}
	}

	return QWidget::eventFilter(obj, event);
}



void GE_Widget::scaledImages(double factor)
{

	ui.label->setFixedWidth(factor * ui.label->width());
	ui.label->setFixedHeight(factor * ui.label->height());
	//ui.label->setGeometry(0, 0, factor * ui.label->width(), factor * ui.label->height());

}

void GE_Widget::SetSizeItemInSpinBox(QPointF& itemSize)
{
	ui.spinBox_5->setValue(itemSize.y() * (3248 / ui.spinBox_2->value() / 256));
	ui.spinBox_6->setValue(itemSize.x() * (4872 / ui.spinBox->value() / 256));
}


void GE_Widget::setOffset(QPointF& point)
{
	//qDebug() << point.y() * (3248.0 / ui.spinBox_2->value() / 250);
	ui.spinBox_3->setValue(point.y() * (3248.0 / ui.spinBox_2->value() / 256));
	ui.spinBox_4->setValue(point.x() * (4872 / ui.spinBox->value() / 256));
}


void GE_Widget::on_pushButton_clicked() //play
{

	ui.tab->setEnabled(true);
	ui.tab_2->setEnabled(false);
	//ui.label->setScaledContents(true); 
	camera->EndCapture();
	camera->FlushQueue();

	/***********************************/
	//binning разрешения в tab2
	camera->GetFeatureByName("BinningHorizontal", pFeature);
	pFeature->SetValue(ui.spinBox->value());

	camera->GetFeatureByName("BinningVertical", pFeature);
	pFeature->SetValue(ui.spinBox_2->value());

	camera->GetFeatureByName("Height", pFeature);
	pFeature->SetValue(ui.spinBox_5->value());

	camera->GetFeatureByName("Width", pFeature);
	int tmp = ui.spinBox_6->value();
	while (tmp % 4 != 0)
	{
		tmp++;
	}
	pFeature->SetValue(tmp);

	camera->GetFeatureByName("OffsetX", pFeature);
	pFeature->SetValue(ui.spinBox_4->value());

	camera->GetFeatureByName("OffsetY", pFeature);
	pFeature->SetValue(ui.spinBox_3->value());
	/****************************************/


	// Get the image size for the required buffer								Получите размер изображения для выбора необходимого буфера
	// Allocate memory for frame buffer											Выделите память для буфера,который будет хранить кадр
	// Register frame observer/callback for each frame							Зарегистрируйте наблюдатель кадров / обратный вызов для каждого кадра
	// Announce frame to the API												Предоставьте кадр API


	camera->GetFeatureByName("PayloadSize", pFeature);							//Получить функцию по имени "Размер полезной нагрузки"(Размер кадра камеры). Полученную функцию возвращаем в pFeature  Feature-характеристика, функция
	pFeature->GetValue(nPLS);													//Запрос значения размера полезной нагрузки


	for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - вектор указателей на кадры, frames.begin()- первый кадр, frames.end()- последний кадр. Цикл прохождения по каждому кадру
	{
		(*iter).reset(new Frame(nPLS));											//сброс предыдущих настроек. Указываем новый размер для ,буффера кадра ( теперь он будет равен величине nPLS)
		//obs = 
		(*iter)->RegisterObserver(IFrameObserverPtr(new FrameObserver(camera, ui, img, makePhoto)));//Зарегистрировать наблюдателя camera(уже ссылается на нашу камеру,которую мы присвоили по ID)
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


}

//stop
void GE_Widget::on_pushButton_2_clicked() //stop
{

	ui.tab_2->setEnabled(true);	//делает tab2 недоступным для редактирования во время работы камеры

	// Stop the acquisition engine (camera)
	camera->GetFeatureByName("AcquisitionStop", pFeature);
	pFeature->RunCommand();

	
}

//expousure
void GE_Widget::on_pushButton_6_clicked()
{
	ui.pushButton_8->setDown(false);
	ui.pushButton_7->setDown(false);
	ui.pushButton_6->setDown(true);

	camera->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Continuous";
	pFeature->SetValue(temp);
}

//expousure
void GE_Widget::on_pushButton_7_clicked()
{
	ui.pushButton_8->setDown(false);
	ui.pushButton_7->setDown(true);
	ui.pushButton_6->setDown(false);

	camera->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Once";
	pFeature->SetValue(temp);
}

//expousure
void GE_Widget::on_pushButton_8_clicked()
{
	ui.pushButton_8->setDown(true);
	ui.pushButton_7->setDown(false);
	ui.pushButton_6->setDown(false);

	camera->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Off";
	pFeature->SetValue(temp);
}

//buttonfull
void GE_Widget::on_pushButton_3_clicked() //full
{
	ui.pushButton_3->setDown(true);
	ui.pushButton_4->setDown(false);//1/4
	ui.pushButton_5->setDown(false);//1/8

	//ui.spinBox_5->setValue(ui.widget->height() * (3248 / ui.spinBox_2->value() / 250));
	//ui.spinBox_6->setValue(ui.widget->width() * (4872 / ui.spinBox->value() / 300));
	ui.spinBox_3->setValue(0);
	ui.spinBox_4->setValue(0);
	ui.spinBox_5->setValue(3248 / ui.spinBox_2->value());
	ui.spinBox_6->setValue(4872 / ui.spinBox->value());

	emit sl_buttonChangeSizeClicked(1);
}

//button 1/4
void GE_Widget::on_pushButton_4_clicked() // 1/4
{
	ui.pushButton_3->setDown(false);
	ui.pushButton_4->setDown(true);//1/4
	ui.pushButton_5->setDown(false);//1/8

	//ui.spinBox_5->setValue(ui.widget->height()/4 * (3248 / ui.spinBox_2->value() / 250));
	//ui.spinBox_6->setValue(ui.widget->width()/4 * (4872 / ui.spinBox->value() / 300));
	ui.spinBox_3->setValue(0);
	ui.spinBox_4->setValue(0);
	ui.spinBox_5->setValue(3248 / ui.spinBox_2->value() / 4);
	ui.spinBox_6->setValue((4872 / ui.spinBox->value() / 4));

	emit sl_buttonChangeSizeClicked(1.0 / 4);
}

//button 1/8
void GE_Widget::on_pushButton_5_clicked() // 1/8
{
	ui.pushButton_3->setDown(false);
	ui.pushButton_4->setDown(false);//1/4
	ui.pushButton_5->setDown(true);//1/8

	/*ui.spinBox_5->setValue(ui.widget->height() / 8 * (3248 / ui.spinBox_2->value() / 250));
	ui.spinBox_6->setValue(ui.widget->width() / 8 * (4872 / ui.spinBox->value() / 300));*/
	ui.spinBox_3->setValue(0);
	ui.spinBox_4->setValue(0);
	ui.spinBox_5->setValue(3248 / ui.spinBox_2->value() / 8);
	ui.spinBox_6->setValue(4872 / ui.spinBox->value() / 8);

	emit sl_buttonChangeSizeClicked(1.0 / 8);


}

void GE_Widget::on_pushButton_9_clicked()
{
	makePhoto = true;
	//ui.widget->setSceneBackground(QPixmap(img));
	//ui.label->setPixmap(img);

}

VmbErrorType GE_Widget::GetExposureAutoTarget(VmbInt64_t& value, CameraPtr& camera)
{
	if (m_ExposureAutoTargetFeature.get() == NULL)
	{
		VmbErrorType result;
		result = camera->GetFeatureByName("ExposureAutoTarget", m_ExposureAutoTargetFeature);
		if (result != VmbErrorSuccess)
		{
			m_ExposureAutoTargetFeature.reset();
			return result;
		}
	}
	feature = m_ExposureAutoTargetFeature;
	return VmbErrorSuccess;
}

VmbErrorType GE_Widget::SetExposureAutoTarget(VmbInt64_t value, CameraPtr& camera)
{
	VmbErrorType result;
	AVT::VmbAPI::FeaturePtr pFeature;
	result = GetExposureAutoTargetFeature(pFeature, camera);
	if (result != VmbErrorSuccess)
		return result;
	result = pFeature->SetValue(value);
	return result;

}

VmbErrorType GE_Widget::GetExposureAutoTargetFeature(FeaturePtr& feature, CameraPtr& camera)
{
	if (m_ExposureAutoTargetFeature.get() == NULL)
	{
		VmbErrorType result;
		result = camera->GetFeatureByName("ExposureAutoTarget", m_ExposureAutoTargetFeature);
		if (result != VmbErrorSuccess)
		{
			m_ExposureAutoTargetFeature.reset();
			return result;
		}
	}
	feature = m_ExposureAutoTargetFeature;
	return VmbErrorSuccess;
};

