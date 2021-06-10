#include "QtGUISensorSim.h"

QtGUISensorSim::QtGUISensorSim(QWidget *parent)
	: QWidget(parent),
	masterObject{ nullptr },
	testObjectVector{ ProcessedObject() },
	activTestObject{ 0 }
{
	ui.setupUi(this);
	connect(ui.comboBox_loadImege, SIGNAL(activated(int)), this, SLOT(slot_loadImageFromLocalMachine(int)));
}

QtGUISensorSim::~QtGUISensorSim()
{
}

void QtGUISensorSim::slot_loadImageFromLocalMachine(int loadType)
{
	if (loadType == 0)
	{
		if (!testObjectVector[0].loadImage())
		{
			ui.wid_forTestImg->setActivProcessObj(testObjectVector[0], false, 0);
		}
		else
		{
			QMessageBox::critical(nullptr, QObject::tr("Warning"), QObject::tr("Image not loaded")); //massage about error download
		}
	}
}

void QtGUISensorSim::slot_dataFromGuiSimulator(ProcessedObject& data)
{
	masterObject = &data;

	ui.wid_forTestImg->setActivProcessObj(testObjectVector[0],false,0);
	//ui.wid_forTestImg->setActiv(false);
	ui.wid_forTestImg->setChangesProcessedArears(false);
	ui.wid_forTestImg->setEnableWidtsGrouBox(false);
}