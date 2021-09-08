#include "QtGUISensorSim.h"

QtGUISensorSim::QtGUISensorSim(QWidget *parent)
	: QWidget(parent),
	masterObject{ nullptr },
	testingObjects{ },
	activTestObject{ 0 },
	imgWidgetsVector{},
	imgWidgetsSpaser{},
	testArearsStatus{},
	activTestArear{ 0 }
{
	ui.setupUi(this);
	ui.horizontalLayout_4->setAlignment(Qt::AlignLeft);
	connect(ui.comboBox_loadImege, SIGNAL(activated(int)), this, SLOT(slot_loadImageFromLocalMachine(int)));
	connect(ui.wid_forTestImg, SIGNAL(changeActivProcesArea(int)), this, SLOT(slot_setActivProcesArea(int)));
}

QtGUISensorSim::~QtGUISensorSim()
{
}

void QtGUISensorSim::slot_loadImageFromLocalMachine(int loadType)
{
	LOG.logMessege("slot_loadImageFromLocalMachine started", LogLevel::_INFO_);
	if (loadType == 0)
	{
		int buferActivOblect{ activTestObject };
		activTestObject = testingObjects.size();
		testingObjects.push_back(ProcessedObject());
		if (!testingObjects[activTestObject].loadImage())
		{
			testingObjects[activTestObject].setProgramName("test " + QString::number(activTestObject));
			testingObjects[activTestObject].setProcessedArears(masterObject->getProcesArears());
			testingObjects[activTestObject].computeComparsion(masterObject->getProcesArears());
			ui.wid_forTestImg->setActivProcessObj(testingObjects[activTestObject], false, 0);
			imgWidgetsVector.push_back(new QtImgWidgetsForTesting());
			imgWidgetsSpaser.push_back(new QSpacerItem(10, 10));
			ui.horizontalLayout_4->insertSpacerItem(0, imgWidgetsSpaser[activTestObject]);
			ui.horizontalLayout_4->insertWidget(0, imgWidgetsVector[activTestObject]);

			imgWidgetsVector[activTestObject]->show();
			imgWidgetsVector[activTestObject]->setImg(testingObjects[activTestObject].getOriginalPixmap());
			imgWidgetsVector[activTestObject]->setImgName(testingObjects[activTestObject].getProgramName());
			imgWidgetsVector[activTestObject]->setId(activTestObject);
			connect(imgWidgetsVector[activTestObject], SIGNAL(mousePres(int)), this, SLOT(slot_newActivObject(int)));
			imgWidgetsVector[buferActivOblect]->setStyleSheet("");
			imgWidgetsVector[activTestObject]->setStyleSheet("border : 1px solid red;");
			LOG.logMessege("image loaded", LogLevel::_INFO_);
		}
		else
		{
			testingObjects.pop_back();
			activTestObject = buferActivOblect;
			QMessageBox::critical(nullptr, QObject::tr("Warning"), QObject::tr("Image not loaded")); //massage about error download
		}
	}
}

void QtGUISensorSim::slot_newActivObject(int newActiv)
{

	imgWidgetsVector[activTestObject]->setStyleSheet("");
	
	imgWidgetsVector[newActiv]->setStyleSheet("border : 1px solid red;");
	ui.wid_forTestImg->setActivProcessObj(testingObjects[newActiv], false, 0);
	testingObjects[newActiv].setProcessedArears(masterObject->getProcesArears());
	activTestObject = newActiv;
}

void QtGUISensorSim::slot_setActivProcesArea(int newActivArea)
{
	if (testingObjects.size() > 0)
	{
		testingObjects[activTestObject].getProcesArears()[0][activTestArear + 1].setActiv(false);
		testingObjects[activTestObject].getProcesArears()[0][newActivArea].setActiv(true);
		ui.wid_forTestImg->updateImg();
	}
	testArearsStatus[activTestArear]->setStyleSheet("");
	testArearsStatus[newActivArea - 1]->setStyleSheet("color: red;");

	activTestArear = newActivArea - 1;
}

void QtGUISensorSim::slot_dataFromGuiSimulator(ProcessedObject& data)
{
	masterObject = new ProcessedObject(data);

	if(testingObjects.size() >= 1)
		ui.wid_forTestImg->setActivProcessObj(testingObjects[0],false,0);
	else
		ui.wid_forTestImg->setActivProcessObj(ProcessedObject(), false, 0);

	ui.wid_forTestImg->setChangesProcessedArears(false);
	ui.wid_forTestImg->setEnableWidtsGrouBox(false);
	ui.wid_forTestImg->setChangeActivArea(true);
	if (data.getProcesArears()->size() > 1)
	{
		
		for (size_t i{ 1 }; i < data.getProcesArears()->size(); ++i)
		{
			testArearsStatus.push_back(new QtWidProcesAreaForTesting(data.getProcesArears()[0][i].getSystemName() + " " + data.getProcesArears()[0][i].getUserName(), 
																	data.getProcesArears()[0][i].singelIsActivTresh(), data.getProcesArears()[0][i].getDoubelTresF(), 
																	data.getProcesArears()[0][i].getDoubelTresS(), i, ui.scrollArea_forProcesArea));
			connect(testArearsStatus[i-1], SIGNAL(setNewActivArea(int)), this, SLOT(slot_setActivProcesArea(int)));
			ui.verticalLayout_forProcessArea->addWidget(testArearsStatus[i - 1]);
			//widProcAreaList[i - 1]->setStyleSheet("");
			//if (masterObjct.getProcesArears()[0][i].isActiv())
			//{
			//	activProcesArea = i;
			//	widProcAreaList[i - 1]->setStyleSheet("color: red;");
			//}
		}
		testArearsStatus[0]->setStyleSheet("color: red;");
		if (testingObjects.size() > 0)
		{
			testingObjects[activTestObject].getProcesArears()[0][1].setActiv(true);
			ui.wid_forTestImg->updateImg();
		}
	}
}

