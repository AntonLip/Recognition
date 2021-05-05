#include "QtGUISensorSim.h"

QtGUISensorSim::QtGUISensorSim(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QtGUISensorSim::~QtGUISensorSim()
{
}

void QtGUISensorSim::slot_dataFromGuiSimulator(ProcessedObj& data)
{
	mainProcesObj = data;

	ui.wid_forTestImg->setActivProcessObj(&data,false,0);
	//ui.wid_forTestImg->setActiv(false);
	ui.wid_forTestImg->setChangesProcessedArears(false);
}