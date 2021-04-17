#include "QtGuiSimulator.h"

QtGuiSimulator::QtGuiSimulator(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.pushButton_play->setVisible(false);
	ui.pushButton_parametrs->setVisible(false);
	connect(ui.linEdit_fileName, SIGNAL(textChanged(QString)), ui.widget_DisplayImg, SLOT(slot_reNameImg(QString)));
	connect(ui.pushButtn_Save, SIGNAL(clicked()), ui.widget_DisplayImg, SLOT(slot_saveImg()));
	connect(ui.pushButton_SetupSimltr, SIGNAL(clicked()), this, SLOT(slot_openSetupSimulator()));
	connect(ui.widget_DisplayImg, SIGNAL(changeActivProcesArea(int)), this, SLOT(slot_changeActivProcArea(int)));
	connect(ui.pushButton_SensorSimltr, SIGNAL(clicked()), this, SLOT(slot_openSensorSim()));
	connect(ui.pushButton_play, SIGNAL(clicked()), this, SLOT(play()));
	connect(ui.pushButton_parametrs, SIGNAL(clicked()), this, SLOT(slot_stop()));

	//connect(ui.comboBox_program, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_SetActivObj(int)));
	connect(ui.pushButtn_Detail, SIGNAL(clicked()), this, SLOT(slot_openProgramDetail()));
	//connect(this, SIGNAL(dataToProgramDeyls(ProcessedObj*)), Programdetail, SLOT(slot_dataFromGuiSimulator(ProcessedObj*)));
	view = new QListView(ui.comboBox_program);
	view->setMinimumWidth(400);
	view->setMinimumHeight(100);
	view->setIconSize(QSize(100, 100));
	//view->setStyleSheet("QListView::item{ minimumwidth: 600px;height: 50px}");
	model = new QStandardItemModel();
	ui.comboBox_program->setView(view);
	ui.comboBox_program->setModel(model);
	QPixmap nulPixmap;
	activLoadObj = 0;
	nulPixmap.load("NoImg.png");
	for (int i{ 0 }; i < 32; i++)
	{
		loadObj.push_back(ProcessedObj("", "", "PN" + QString::number(i), cv::Mat(), nulPixmap, true));
		ui.comboBox_program->addItem("PN" + QString::number(i));
		ui.comboBox_program->setItemIcon(i, nulPixmap);
	}

}

QtGuiSimulator::~QtGuiSimulator()
{
	camera->RevokeAllFrames();
	camera->Close();
	system.Shutdown(); // Always pair sys.Startup and sys.Shutdown
}

void QtGuiSimulator::dataFromMainMenu(cv::Mat tempImg_out, QString fileName_in) // вызывается после нажатия на кнопку во 2 меню
{
	/*QImage::Format format;
	if (tempImg_out.channels() == 3)
	{
		format = QImage::Format_RGB888;
	}
	else if (tempImg_out.channels() == 1)
	{
		format = QImage::Format_Grayscale8;
	}
	else if (tempImg_out.channels() == 4)
	{
		format = QImage::Format_RGBA8888;
	}*/
	std::size_t found = fileName_in.toStdString().find_last_of("/\\");
	//QImage myImage(tempImg_out.data, tempImg_out.cols, tempImg_out.rows, tempImg_out.step, format);
	loadObj[0].SetObjParams(QString::fromStdString(fileName_in.toStdString().substr(found + 1)), QString::fromStdString(fileName_in.toStdString().substr(0, found))
		, tempImg_out, QPixmap(fileName_in), false);
	activLoadObj = 0;
	ui.widget_DisplayImg->setActivProcessObj(&loadObj[0]);
	ui.linEdit_fileName->setText(loadObj[activLoadObj].getFileName());
	ui.comboBox_program->setItemIcon(activLoadObj, QPixmap(fileName_in));
	connect(ui.comboBox_program, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_SetActivObj(int)));
}

void QtGuiSimulator::readVideo(cv::Mat* newFrameMat, QPixmap* newFramePixmap)
{
	loadObj[activLoadObj].SetObjParams("", "", *newFrameMat, *newFramePixmap, false);
}

void QtGuiSimulator::slot_SetActivObj(int newActivObj)
{
	activLoadObj = newActivObj;
	ui.widget_DisplayImg->setActivProcessObj(&loadObj[activLoadObj]);
	ui.linEdit_fileName->setText(loadObj[activLoadObj].getFileName());
}

void QtGuiSimulator::slot_openProgramDetail()
{	
	Programdetail = new QtGuiProgramDetails();
	Programdetail->show();
	connect(this, SIGNAL(dataToProgramDeyls(ProcessedObj*)), Programdetail, SLOT(slot_dataFromGuiSimulator(ProcessedObj*)));
	connect(Programdetail, SIGNAL(add_Images(int)), this, SLOT(slot_updateComboBox(int)));
	connect(Programdetail, SIGNAL(close_GUIProgDet()), this, SLOT(slot_closeProgDet()));
	emit dataToProgramDeyls(&loadObj[0]);
	
}

void QtGuiSimulator::slot_updateComboBox(int activObj)
{
	ui.comboBox_program->setItemIcon(activObj, loadObj[activObj].getPixmap());
	ui.comboBox_program->setItemText(activObj, loadObj[activObj].getProgramName());
	if (ui.comboBox_program->currentIndex() == activObj)
		slot_SetActivObj(activObj);
}

void QtGuiSimulator::slot_openSetupSimulator()
{
	SetupSimulator = new QtSetupSimulator();
	SetupSimulator->show();
	connect(this, SIGNAL(dataToSetingSim(ProcessedObj*)), SetupSimulator, SLOT(slot_dataFromGUISim(ProcessedObj*)));
	connect(SetupSimulator, SIGNAL(dataToGUISim(ProcessedObj*)), this, SLOT(slot_dataFromSetupSim(ProcessedObj*)));
	emit dataToSetingSim(&loadObj[activLoadObj]);
}

void QtGuiSimulator::slot_dataFromSetupSim(ProcessedObj* changedObj)
{
	for (int i{ 0 }; i < changedObj->getProcesArears()->size(); ++i)
	{
		changedObj->getProcesArears()[0][i].setDraw(true);
		ui.widget_DisplayImg->processedAreaScale(changedObj->getProcesArears()[0][i]);
	}
	loadObj[activLoadObj] = *changedObj;
	ui.widget_DisplayImg->setChangeActivArea(true);
	ui.widget_DisplayImg->updateImg();
}

void QtGuiSimulator::slot_changeActivProcArea(int newActiv)
{
	for (int i{ 1 }; i < loadObj[activLoadObj].getProcesArears()[0].size(); ++i)
	{
		if (i == newActiv)
		{
			loadObj[activLoadObj].getProcesArears()[0][i].setActiv(true);
			
		}
		else
		{
			loadObj[activLoadObj].getProcesArears()[0][i].setActiv(false);
			
		}
	}
	ui.widget_DisplayImg->updateImg();
}

void QtGuiSimulator::slot_openSensorSim()
{
	SensorSimulator = new QtGUISensorSim();
	QString qstr_bufer{ QFileDialog::getOpenFileName(this, "Images", "D:/", tr("Images files (*.png *.jpg *.bmp)")) };
	cv::Mat img_bufer;
	img_bufer = cv::imread(qstr_bufer.toStdString());
	if (!img_bufer.empty())// checking that image has loaded 
	{
		loadObj[activLoadObj].addTestImg(qstr_bufer);
		SensorSimulator->show();
		connect(this, SIGNAL(dataToSensorSim(ProcessedObj&)), SensorSimulator, SLOT(slot_dataFromGuiSimulator(ProcessedObj&)));
		emit dataToSensorSim(loadObj[activLoadObj]);
		//this->close();
	}
	else
	{
		QMessageBox::critical(nullptr, QObject::tr("Warning"), QObject::tr("Image not loaded")); //massage about error download
	}
	//SensorSimulator->show();
	/*connect(this, SIGNAL(dataToSensorSim(ProcessedObj*)), SensorSimulator, SLOT(slot_dataFromGuiSimulator(ProcessedObj*)));
	emit dataToSensorSim(loadObj[activLoadObj]);*/
}

void QtGuiSimulator::slot_getCameraInformation(CameraPtrVector& cams, int index )
{
	ui.pushButton_play->setVisible(true);
	ui.pushButton_parametrs->setVisible(true);
	//ui.stackedWidget->setCurrentIndex(1);
	cameras = cams;
	m_index = index;
}

void QtGuiSimulator::play()
{
	if ( Str == "AcquisitionStop")
	{
		//ui.stackedWidget->setCurrentIndex(1);
		//system.Startup();  // Процесс запускаем в QtConnect
		//system.GetCameras(cameras);

		camera = cameras[m_index];													//первую из списка камеру присваиваем
		camera->Open(VmbAccessModeFull);											//открываем камеру в режиме "доступ для чтения и записи". Используйте этот режим для настройки функций камеры и получения изображений

		/***********************************/
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
		/****************************************/

		camera->GetFeatureByName("PayloadSize", pFeature);							//Получить функцию по имени "Размер полезной нагрузки"(Размер кадра камеры). Полученную функцию возвращаем в pFeature  Feature-характеристика, функция
		pFeature->GetValue(nPLS);													//Запрос значения размера полезной нагрузки

		//cv::Mat df(0, 0, CV_8UC1);
		for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - вектор указателей на кадры, frames.begin()- первый кадр, frames.end()- последний кадр. Цикл прохождения по каждому кадру
		{
			(*iter).reset(new Frame(nPLS));											//сброс предыдущих настроек. Указываем новый размер для ,буффера кадра ( теперь он будет равен величине nPLS)
			//obs = 

			//(*iter)->RegisterObserver(IFrameObserverPtr(new FirstFrameObserver(camera, &ui, &df)));//Зарегистрировать наблюдателя camera(уже ссылается на нашу камеру,которую мы присвоили по ID)
			(*iter)->RegisterObserver(IFrameObserverPtr(new FrameObserver(camera, ui, img, makePhoto, &loadObj[0])));
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

void QtGuiSimulator::slot_stop()
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
