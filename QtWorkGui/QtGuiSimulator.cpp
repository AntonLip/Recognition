#include "QtGuiSimulator.h"

void QtGuiSimulator::readVideo(cv::Mat *newFrameMat, QPixmap *newFramePixmap)
{
	loadObj[activLoadObj].SetObjParams("", "", *newFrameMat, *newFramePixmap, false);
}

QtGuiSimulator::QtGuiSimulator(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.linEdit_fileName, SIGNAL(textChanged(QString)), ui.widget_DisplayImg, SLOT(slot_reNameImg(QString)));
	connect(ui.pushButtn_Save, SIGNAL(clicked()), ui.widget_DisplayImg, SLOT(slot_saveImg()));
	connect(ui.pushButton_SetupSimltr, SIGNAL(clicked()), this, SLOT(slot_openSetupSimulator()));
	connect(ui.widget_DisplayImg, SIGNAL(changeActivProcesArea(int)), this, SLOT(slot_changeActivProcArea(int)));
	connect(ui.pushButton_SensorSimltr, SIGNAL(clicked()), this, SLOT(slot_openSensorSim()));
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
}

void QtGuiSimulator::dataFromMainMenu(cv::Mat tempImg_out, QString fileName_in)
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
