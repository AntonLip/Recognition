#include "QtGUISensorSim.h"

QtGUISensorSim::QtGUISensorSim(QWidget *parent)
	: QWidget(parent),
	masterObject{ nullptr },
	testingObjects{ },
	activTestObject{ 0 }
{
	ui.setupUi(this);
	ui.horizontalLayout_4->setAlignment(Qt::AlignLeft);
	connect(ui.comboBox_loadImege, SIGNAL(activated(int)), this, SLOT(slot_loadImageFromLocalMachine(int)));
}

QtGUISensorSim::~QtGUISensorSim()
{
}

void QtGUISensorSim::slot_loadImageFromLocalMachine(int loadType)
{
	if (loadType == 0)
	{
		int buferActivOblect{ activTestObject };
		activTestObject = testingObjects.size();
		testingObjects.push_back(ProcessedObject());
		if (!testingObjects[activTestObject].loadImage())
		{
			testingObjects[activTestObject].setProgramName("test " + QString::number(activTestObject));
			ui.wid_forTestImg->setActivProcessObj(testingObjects[activTestObject], false, 0);
			imgWidgetsVector.push_back(new QtImgWidgetsForTesting());
			imgWidgetsSpaser.push_back(new QSpacerItem(10, 10));
			ui.horizontalLayout_4->insertWidget(0, imgWidgetsVector[activTestObject]);
			ui.horizontalLayout_4->insertSpacerItem(0, imgWidgetsSpaser[activTestObject]);

			imgWidgetsVector[activTestObject]->show();
			imgWidgetsVector[activTestObject]->setImg(testingObjects[activTestObject].getOriginalPixmap());
			imgWidgetsVector[activTestObject]->setImgName(testingObjects[activTestObject].getProgramName());
			imgWidgetsVector[activTestObject]->setId(activTestObject);
			connect(imgWidgetsVector[activTestObject], SIGNAL(mousePres(int)), this, SLOT(slot_newActivObject(int)));
			imgWidgetsVector[buferActivOblect]->setStyleSheet("");
			imgWidgetsVector[activTestObject]->setStyleSheet("border : 1px solid red;");
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
	
	activTestObject = newActiv;
}

void QtGUISensorSim::slot_dataFromGuiSimulator(ProcessedObject& data)
{
	masterObject = &data;

	if(testingObjects.size() >= 1)
		ui.wid_forTestImg->setActivProcessObj(testingObjects[0],false,0);
	else
		ui.wid_forTestImg->setActivProcessObj(ProcessedObject(), false, 0);
	//ui.wid_forTestImg->setActiv(false);
	ui.wid_forTestImg->setChangesProcessedArears(false);
	ui.wid_forTestImg->setEnableWidtsGrouBox(false);
}