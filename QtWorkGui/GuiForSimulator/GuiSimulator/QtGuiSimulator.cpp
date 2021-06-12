#include "QtGuiSimulator.h"


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

	model = new QStandardItemModel();
	ui.comboBox_program->setView(view);
	ui.comboBox_program->setModel(model);
	ui.comboBox_program->setCurrentIndex(0);
	QPixmap nulPixmap;
	activLoadObj = 0;
	nulPixmap.load("NoImg.png");
	for (int i{ 0 }; i < 32; i++)
	{
		loadObj.push_back(ProcessedObject("", "", cv::Mat(), nulPixmap, "PN" + QString::number(i), true));
		ui.comboBox_program->addItem("PN" + QString::number(i));
		ui.comboBox_program->setItemIcon(i, nulPixmap);
	}
}

QtGuiSimulator::~QtGuiSimulator()
{

}

void QtGuiSimulator::dataFromMainMenu(cv::Mat tempImg_out, QString fileName_in)
{
	std::size_t found = fileName_in.toStdString().find_last_of("/\\");
	loadObj[0].setFileName(QString::fromStdString(fileName_in.toStdString().substr(found + 1)));
	loadObj[0].setDirName(QString::fromStdString(fileName_in.toStdString().substr(0, found)));
	loadObj[0].updateMat(tempImg_out, QPixmap(fileName_in));
	loadObj[0].setFlagImageIsNull(false);
	ui.widget_DisplayImg->setActivProcessObj(loadObj[0]);
	ui.linEdit_fileName->setText(loadObj[activLoadObj].getFileName());
	ui.comboBox_program->setItemIcon(activLoadObj, QPixmap(fileName_in));
	connect(ui.comboBox_program, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_SetActivObj(int)));
}

void QtGuiSimulator::slot_SetActivObj(int newActivObj)
{
	activLoadObj = newActivObj;
	ui.widget_DisplayImg->setActivProcessObj(loadObj[activLoadObj]);
	ui.linEdit_fileName->setText(loadObj[activLoadObj].getFileName());
}

void QtGuiSimulator::slot_openProgramDetail()
{	
	Programdetail = new QtGuiProgramDetails();
	Programdetail->show();
	connect(this, SIGNAL(dataToProgramDeyls(ProcessedObject*)), Programdetail, SLOT(slot_dataFromGuiSimulator(ProcessedObject*)));
	connect(Programdetail, SIGNAL(add_Images(int)), this, SLOT(slot_updateComboBox(int)));
	connect(Programdetail, SIGNAL(close_GUIProgDet()), this, SLOT(slot_closeProgDet()));
	emit dataToProgramDeyls(&loadObj[0]);
}

void QtGuiSimulator::slot_updateComboBox(int activObj)
{
	ui.comboBox_program->setItemIcon(activObj, loadObj[activObj].getCorrectPixmap());
	ui.comboBox_program->setItemText(activObj, loadObj[activObj].getProgramName());
	if (ui.comboBox_program->currentIndex() == activObj)
		slot_SetActivObj(activObj);
}

void QtGuiSimulator::slot_openSetupSimulator()
{
	try
	{
		SetupSimulator = new QtSetupSimulator();
	}
	catch(...)
	{
		LOG.logMessege("SetupSimulator creation error",_ERROR_);
	}
	SetupSimulator->show();
	connect(this, SIGNAL(dataToSetingSim(ProcessedObject&)), SetupSimulator, SLOT(slot_dataFromGUISim(ProcessedObject&)));
	connect(SetupSimulator, SIGNAL(dataToGUISim(ProcessedObject*)), this, SLOT(slot_dataFromSetupSim(ProcessedObject*)));
	emit dataToSetingSim(loadObj[activLoadObj]);
}

void QtGuiSimulator::slot_dataFromSetupSim(ProcessedObject* changedObj)
{
	for (int i{ 0 }; i < changedObj->getProcesArears()->size(); ++i)
	{
		changedObj->getProcesArears()[0][i].setDraw(true);
		//ui.widget_DisplayImg->processedAreaScale(changedObj->getProcesArears()[0][i]);
	}
	loadObj[activLoadObj] = *changedObj;
	ui.widget_DisplayImg->updateProcessObj(loadObj[activLoadObj]);
	ui.linEdit_fileName->setText(loadObj[activLoadObj].getFileName());
	ui.comboBox_program->setItemIcon(activLoadObj, loadObj[activLoadObj].getOriginalPixmap());
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
	SensorSimulator->show();
	connect(this, SIGNAL(dataToSensorSim(ProcessedObject&)), SensorSimulator, SLOT(slot_dataFromGuiSimulator(ProcessedObject&)));
	emit dataToSensorSim(loadObj[activLoadObj]);
}

