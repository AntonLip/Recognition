#include "QtSetupSimulator.h"

QtSetupSimulator::QtSetupSimulator(QWidget *parent)
	: QWidget(parent),
	firstStepEnable(false)
{
	ui.setupUi(this);
	changes = false;
	isClose = false;
	closeAddWindow = false;
	horSliderHaveTwoSlider = false;
	delActivProcesArea = false;
	editActivArea = false;
	editProcesArea = false;
	activProcesArea = 0;
	ui.pushButton_setCorect->setCheckable(true);
	connect(ui.pushButton_step1, SIGNAL(clicked()), this, SLOT(slot_pushStep1()));
	connect(ui.pushButton_step2, SIGNAL(clicked()), this, SLOT(slot_pushStep2()));
	connect(ui.pushButton_step3, SIGNAL(clicked()), this, SLOT(slot_pushStep3()));
	connect(ui.pushButton_step4, SIGNAL(clicked()), this, SLOT(slot_pushStep4()));
	connect(ui.pushButton_nextAndFinsh, SIGNAL(clicked()), this, SLOT(slot_pushNext()));
	connect(ui.pushButton_back, SIGNAL(clicked()), this, SLOT(slot_pushBack()));
	connect(ui.pushButton_canel, SIGNAL(clicked()), this, SLOT(slot_pushCanel()));
	connect(ui.pushButton_setCorect, SIGNAL(clicked()), this, SLOT(slot_setBrightnesCorrectArea()));
	connect(ui.pushButton_delCorect, SIGNAL(clicked()), this, SLOT(slot_pushDelBrighArea()));
	connect(ui.PButn_fPlus, SIGNAL(clicked(bool)), this, SLOT(slot_PBPlusF()));
	connect(ui.PButn_sPlus, SIGNAL(clicked(bool)), this, SLOT(slot_PBPlusS()));
	connect(ui.PButn_fMinus, SIGNAL(clicked(bool)), this, SLOT(slot_PBMinusF()));
	connect(ui.PButn_sMinus, SIGNAL(clicked(bool)), this, SLOT(slot_PBMinusS()));
	connect(ui.pushButton_editTool, SIGNAL(clicked()), this, SLOT(slot_editProceArea()));
	connect(ui.pushButton_CopyTool, SIGNAL(clicked()), this, SLOT(slot_copyProceArea()));
	connect(ui.RButn_rect, SIGNAL(toggled(bool)), this, SLOT(slot_chengeAreaType()));
	connect(ui.RButn_circle, SIGNAL(toggled(bool)), this, SLOT(slot_chengeAreaType()));
	connect(ui.RButn_entire, SIGNAL(toggled(bool)), this, SLOT(slot_chengeAreaType()));
	connect(ui.pushButton_delTool, SIGNAL(clicked()), this, SLOT(slot_pushDelActivProcArea()));
	connect(ui.widget_getMasterImg, SIGNAL(brightnesCorrectRectSet(bool)), this, SLOT(slot_BrightnesCorrectIsSet(bool)));
	connect(ui.pushButton_addTool, SIGNAL(clicked()), this, SLOT(slot_pushAddTool()));
	connect(this, SIGNAL(brightnesCorrectAreaDel()), ui.widget_getMasterImg, SLOT(slot_brighAreaDel()));
	connect(ui.widget_getMasterImg, SIGNAL(clic_pb()), this, SLOT(slot_setCorect()));
	connect(this, SIGNAL(clic_pb()), this, SLOT(slot_setCorect()));
	connect(ui.tabWid_setMasterImg, SIGNAL(currentChanged(int)), this, SLOT(slot_curntChngInTab(int)));
	connect(ui.PButn_OKAddProces, SIGNAL(clicked()), this, SLOT(slot_OKAddTool()));
	connect(ui.checkBox, SIGNAL(stateChanged(int)), this, SLOT(slot_changeChecBox(int)));
	connect(ui.comboBox_Scal, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_changeComboBoxScal(int)));
	connect(ui.widget_getMasterImg, SIGNAL(changeActivProcesArea(int)), this, SLOT(slot_setActivProcesArea(int)));
	connect(ui.PButn_canelAddProces, SIGNAL(clicked()), this, SLOT(slot_closeAddTool()));
	connect(ui.widget_slider, SIGNAL(changeRange()), this, SLOT(slot_changeTresh()));
	connect(ui.lineEdit_procesUserName, SIGNAL(textChanged(QString)), this, SLOT(slot_changeUserNameArea(QString)));
	connect(ui.PButn_angelRest, SIGNAL(clicked()), this, SLOT(slot_resetAngelRect()));
	connect(this, SIGNAL(resetRectAngel(int)), ui.widget_getMasterImg, SLOT(slot_resetAngel(int)));
	connect(ui.stackWid_steps, SIGNAL(currentChanged(int)), this, SLOT(slot_changeWidSteps(int)));
	connect(ui.tabWid_setMasterImg, SIGNAL(currentChanged(int)), this, SLOT(slot_changeWidSteps(int)));
	connect(ui.widget_getMasterImg, SIGNAL(getActivProcessArea()), this, SLOT(slot_getActivProcesAreaTowidgetMasterImg()));
	setAttribute(Qt::WA_DeleteOnClose);
}

QtSetupSimulator::~QtSetupSimulator()
{
}

void QtSetupSimulator::slot_setActivProcesArea(int activ)
{
	activProcesArea = activ;
	for (int i{ 1 }; i < masterObjct.getProcesArears()[0].size(); ++i)
	{
		if (i == activ)
		{
			masterObjct.getProcesArears()[0][i].setActiv(true);
			widProcAreaList[i-1]->setStyleSheet("color: red;");
		}
		else
		{
			masterObjct.getProcesArears()[0][i].setActiv(false);
			widProcAreaList[i-1 ]->setStyleSheet("");
		}
	}
	ui.widget_getMasterImg->updateImg();
}

void QtSetupSimulator::slot_pushDelActivProcArea()
{
	dialog = new QtMyDialog("Are you sure you want to delete this is tool?", this);
	dialog->show();
	delActivProcesArea = true;
	connect(dialog, SIGNAL(answer(bool)), this, SLOT(slot_dataFromDialog(bool)));
}

void QtSetupSimulator::slot_chengeAreaType()
{
	if (!editActivArea)
	{
		if (ui.RButn_rect->isChecked())
		{
			if (masterObjct.getProcesArears()[0][activProcesArea].getAreaType() != 0)
			{
				masterObjct.getProcesArears()[0][activProcesArea].setAreaType(0);
				ui.widget_getMasterImg->changeAreaType(0, masterObjct.getProcesArears()[0][activProcesArea]);
				ui.widget_getMasterImg->updateImg();
			}
			ui.PButn_angelRest->setEnabled(true);
		}
		else if (ui.RButn_circle->isChecked())
		{
			if (masterObjct.getProcesArears()[0][activProcesArea].getAreaType() != 1)
			{
				masterObjct.getProcesArears()[0][activProcesArea].setAreaType(1);
				ui.widget_getMasterImg->changeAreaType(1, masterObjct.getProcesArears()[0][activProcesArea]);
				ui.widget_getMasterImg->updateImg();
			}
			ui.PButn_angelRest->setEnabled(false);
		}
		else if (ui.RButn_entire->isChecked())
		{
			if (masterObjct.getProcesArears()[0][activProcesArea].getAreaType() != 2)
			{
				masterObjct.getProcesArears()[0][activProcesArea].setAreaType(2);
				ui.widget_getMasterImg->updateImg();
			}
		}	
	}
}

void QtSetupSimulator::slot_changeUserNameArea(QString newName)
{
	masterObjct.getProcesArears()[0][activProcesArea].setUserName(newName);
}

void QtSetupSimulator::slot_editProceArea()
{	
	editActivArea = true;
	editProcesArea = true;
	oldActivArea = activProcesArea;
	masterObjct.getProcesArears()->push_back(masterObjct.getProcesArears()[0][activProcesArea]);
	masterObjct.getProcesArears()[0][activProcesArea].setActiv(false);
	masterObjct.getProcesArears()[0][activProcesArea].setDraw(false);
	activProcesArea = masterObjct.getProcesArears()->size() - 1;
	this->setGUIParamsAddArea(masterObjct.getProcesArears()[0][activProcesArea].getProcesseedType());
	ui.stackWid_customTools->setCurrentIndex(1);
	ui.lineEdit_procesUserName->setText(masterObjct.getProcesArears()[0][activProcesArea].getUserName());
	if (masterObjct.getProcesArears()[0][activProcesArea].singelIsActivTresh())
	{
		ui.checkBox->setChecked(false);
		ui.widget_slider->setRenge(0, 100);
		ui.widget_slider->getSlider()->setUpperValue(masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresS());
	}
	else
	{
		ui.checkBox->setChecked(true);
		if (masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresS() > 200)
		{
			ui.comboBox_Scal->setCurrentIndex(1);
		}
		else
		{
			ui.comboBox_Scal->setCurrentIndex(0);
		}
		ui.widget_slider->getSlider()->setUpperValue(masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresS());
		ui.widget_slider->getSlider()->setLowerValue(masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresF());
	}
	if (masterObjct.getProcesArears()[0][activProcesArea].getAreaType() == 0)
	{
		ui.RButn_rect->setChecked(true);
	}
	else if (masterObjct.getProcesArears()[0][activProcesArea].getAreaType() == 1)
	{
		ui.RButn_circle->setChecked(true);
	}
	else
	{
		ui.RButn_entire->setChecked(true);
	}
	ui.pushButton_step1->setEnabled(false);
	ui.pushButton_step2->setEnabled(false);
	ui.pushButton_step3->setEnabled(false);
	ui.pushButton_step4->setEnabled(false);
	ui.pushButton_back->setEnabled(false);
	ui.pushButton_nextAndFinsh->setEnabled(false);
	ui.widget_getMasterImg->setChangeActivArea(false);
	ui.widget_getMasterImg->setChangesProcessedArears(true);
	ui.widget_getMasterImg->updateImg();
	editActivArea = false;
}

void QtSetupSimulator::slot_copyProceArea()
{
	masterObjct.getProcesArears()->push_back(masterObjct.getProcesArears()[0][activProcesArea]);
	masterObjct.getProcesArears()[0][activProcesArea].setActiv(false);
	activProcesArea = masterObjct.getProcesArears()->size() - 1;
	widProcArea = new QtWidProcesArea(QString(masterObjct.getProcesArears()[0][activProcesArea].getSystemName() + " " + masterObjct.getProcesArears()[0][activProcesArea].getUserName()), masterObjct.getProcesArears()[0][activProcesArea].singelIsActivTresh(), masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresF(), masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresS(), activProcesArea, ui.scrollArea_procesArears);
	connect(widProcArea, SIGNAL(setNewActivArea(int)), this, SLOT(slot_setActivProcesArea(int)));
	ui.verticalLayout_scrolProcesArea->addWidget(widProcArea);
	for (int i{ 0 }; i < widProcAreaList.size(); ++i)
	{
		widProcAreaList[i]->setStyleSheet("");
	}
	//widProcArea->setStyleSheet("color: red;");
	widProcAreaList.push_back(widProcArea);
	ui.widget_getMasterImg->updateImg();
}

void QtSetupSimulator::slot_changeWidSteps(int step)
{
	if (ui.stackWid_steps->currentIndex() == 1)
		activProcesArea = 0;
	else if (masterObjct.getProcesArears()->size() > 1)
		activProcesArea = 1;
	if (ui.stackWid_steps->currentIndex() != 1 || ui.tabWid_setMasterImg->currentIndex() != 1)
	{
		masterObjct.getProcesArears()[0][0].setActiv(false);
		masterObjct.getProcesArears()[0][0].setDraw(false);
		ui.widget_getMasterImg->changeImgFormat(0);
		ui.widget_getMasterImg->updateImg();
	}
	else if (ui.stackWid_steps->currentIndex() == 1 && ui.tabWid_setMasterImg->currentIndex() == 1)
	{
		masterObjct.getProcesArears()[0][0].setActiv(true);
		masterObjct.getProcesArears()[0][0].setDraw(true);
		ui.widget_getMasterImg->changeImgFormat(1);
		ui.widget_getMasterImg->updateImg();
	}
}

void QtSetupSimulator::slot_resetAngelRect()
{
	emit resetRectAngel(activProcesArea);
}

void QtSetupSimulator::slot_getActivProcesAreaTowidgetMasterImg()
{
	ui.widget_getMasterImg->setActivProcesArea(activProcesArea);
}


void QtSetupSimulator::setGUIWid(int newActivStep)
{
	activStep = newActivStep;
	ui.stackWid_steps->setCurrentIndex(activStep-1);
	if (activStep != 4)
		ui.pushButton_nextAndFinsh->setText("to step " + QString::number(activStep + 1) + " ->");
	else
		ui.pushButton_nextAndFinsh->setText("finish");
	ui.label_getActivStep->setText("step " + QString::number(activStep));
	if (activStep == 1)
	{
		ui.pushButton_back->setEnabled(false);
		ui.widget_getMasterImg->setActiv(firstStepEnable);
	}
	else
	{
		ui.pushButton_back->setEnabled(true);
		if(!ui.widget_getMasterImg->isActiv())
			ui.widget_getMasterImg->setActiv(true);
	}
	if (activStep == 2)
	{
		masterObjct.getProcesArears()[0][0].setDraw(true);
		
	}
	else
	{
		masterObjct.getProcesArears()[0][0].setDraw(false);
	}
	if (activStep == 3)
	{
		
		if (masterObjct.getProcesArears()->size() <= 1)
		{
			ui.pushButton_CopyTool->setEnabled(false);
			ui.pushButton_delTool->setEnabled(false);
			ui.pushButton_editTool->setEnabled(false);
			ui.pushButton_nextAndFinsh->setEnabled(false);
			ui.pushButton_step4->setEnabled(false);
		}
		else
		{
			ui.pushButton_CopyTool->setEnabled(true);
			ui.pushButton_delTool->setEnabled(true);
			ui.pushButton_editTool->setEnabled(true);
			ui.pushButton_nextAndFinsh->setEnabled(true);
			ui.pushButton_step4->setEnabled(true);
			for (int i{ 1 }; i < masterObjct.getProcesArears()->size(); i++)
			{
				masterObjct.getProcesArears()[0][i].setDraw(true);
			}
		}
	}
	else
	{
		for (int i{ 1 }; i < masterObjct.getProcesArears()->size(); i++)
		{
			masterObjct.getProcesArears()[0][i].setDraw(false);
		}
	}
	if (masterObjct.getProcesArears()->size() <= 1)
	{
		ui.pushButton_step4->setEnabled(false);
	}
	ui.widget_getMasterImg->updateImg();
	emit clic_pb();
}

void QtSetupSimulator::setGUIParamsAddArea(int typeProcesArea)
{
	ui.RButn_entire->show();
	ui.PButn_mask->show();
	ui.comboBox_Scal->show();
	ui.label_scal->show();
	ui.checkBox->show();
	ui.groupBox_searecgReg->show();
	ui.label_search->show();
	ui.label_senserivity->show();
	ui.comboBox_senserivity->show();
	ui.label_inSeting->show();
	ui.groupBox_windShape->show();
	ui.label_shape->show();
	ui.PButn_angelRest->show();
	setOneSlider(false);
	
	if (typeProcesArea == 1 || typeProcesArea == 4)
	{
		ui.RButn_entire->hide();
		ui.PButn_mask->hide();
		setOneSlider(true);
		ui.comboBox_Scal->hide();
		ui.label_scal->hide();
		ui.checkBox->hide();
		ui.widget_slider->getSlider()->setRange(0, 100);
		ui.label_selectShape->setText("Select the window shape and searh region.");
		ui.groupBox_seting->setTitle("Fine Tune Outline"); 
		ui.PButn_removeOutline->setText("Remove Outline");
	}
	else
	if (typeProcesArea == 2)
	{
		ui.groupBox_searecgReg->hide();
		ui.label_search->hide();
		ui.label_selectShape->setText("Select the window shape.");
		ui.groupBox_seting->setTitle("Brihtgtness Extraction");
		ui.label_senserivity->hide();
		ui.comboBox_senserivity->hide();
		ui.label_inSeting->hide();
		ui.PButn_removeOutline->setText("Setup");
	}
	else
	if (typeProcesArea == 3)
	{
		ui.groupBox_searecgReg->hide();
		ui.label_search->hide();
		ui.label_selectShape->setText("Select the window shape.");
		ui.groupBox_seting->setTitle("Sensitivity Setting");
		ui.label_senserivity->hide();
		ui.comboBox_senserivity->hide();
		ui.PButn_removeOutline->setText("Sensitivity Setting");
		ui.label_inSeting->hide();
	}
	else
	if (typeProcesArea == 5 || typeProcesArea == 6 || typeProcesArea == 7 || typeProcesArea == 8 || typeProcesArea == 9)
	{
		ui.groupBox_searecgReg->hide();
		ui.groupBox_windShape->hide();
		ui.label_shape->hide();
		ui.label_search->hide();
		ui.label_selectShape->setText("Select the window shape.");
		ui.groupBox_seting->setTitle("Sensitivity Setting");
		ui.label_senserivity->hide();
		ui.comboBox_senserivity->hide();
		ui.PButn_removeOutline->setText("Edge Setting");
		ui.label_inSeting->hide();
		if (typeProcesArea == 6)
		{
			ui.PButn_angelRest->hide();
		}
		else
		if (typeProcesArea == 8)
		{
			ui.checkBox->hide();
		}
	}
	else
	if (typeProcesArea == 5)
	{

	}
}

void QtSetupSimulator::closeEvent(QCloseEvent* event)
{
	if (!isClose)
	{
		isClose = true;
		event->ignore();
		dialog = new QtMyDialog("Are you sure you want to close setup simulator window?", this);
		dialog->show();
		connect(dialog, SIGNAL(answer(bool)), this, SLOT(slot_dataFromDialog(bool)));
		emit clic_pb();
	}
	else
	{
		this->close();
	}	
}

void QtSetupSimulator::addProceseArea()
{

}

void QtSetupSimulator::mousePressEvent(QMouseEvent* event)
{
	if (!ui.widget_getMasterImg->getLabelRect().contains(event->pos()))
	{
		ui.widget_getMasterImg->addBrightnesCorrectRect(false);
		ui.pushButton_setCorect->setChecked(false); 
	}
}

void QtSetupSimulator::setOneSlider(bool oneSlider_)
{
	oneSlider = oneSlider_;
	if (oneSlider_)
	{
		ui.PButn_sMinus->hide();
		ui.PButn_sPlus->hide();
		ui.comboBox_Scal->setEnabled(false);
		ui.label_scal->setEnabled(false);
		ui.widget_slider->setRenge(0, 100);
		masterObjct.getProcesArears()[0][activProcesArea].setActivTres(true);
	}
	else
	{
		ui.PButn_sMinus->show();
		ui.PButn_sPlus->show();
		ui.comboBox_Scal->setEnabled(true);
		ui.label_scal->setEnabled(true);
		slot_changeComboBoxScal(ui.comboBox_Scal->currentIndex());
		masterObjct.getProcesArears()[0][activProcesArea].setActivTres(false);
	}
	ui.widget_slider->setOneSlider(oneSlider_);
}

void QtSetupSimulator::slot_pushStep1()
{
	setGUIWid(1);
	ui.widget_getMasterImg->setChangesProcessedArears(false);
}

void QtSetupSimulator::slot_pushStep2()
{
	setGUIWid(2);
	ui.widget_getMasterImg->setEanbleActivededRoi(false);
	ui.widget_getMasterImg->setChangesProcessedArears(true);
}

void QtSetupSimulator::slot_pushStep3()
{
	setGUIWid(3);
	ui.widget_getMasterImg->setEanbleActivededRoi(true);
	ui.widget_getMasterImg->setChangesProcessedArears(false);
}

void QtSetupSimulator::slot_pushStep4()
{
	setGUIWid(4);
	ui.widget_getMasterImg->setEanbleActivededRoi(false);
	ui.widget_getMasterImg->setChangesProcessedArears(false);
}

void QtSetupSimulator::slot_dataFromGUISim(ProcessedObj* newMasterObj)
{
	masterObjct = *newMasterObj;
	ui.widget_getMasterImg->setActivProcessObj(&masterObjct);
	setGUIWid(1);
	if (masterObjct.getProcesArears()->size() > 1)
	{
		ui.stackWid_customTools->setCurrentIndex(0);
		ui.pushButton_CopyTool->setEnabled(true);
		ui.pushButton_delTool->setEnabled(true);
		ui.pushButton_editTool->setEnabled(true);
		ui.pushButton_nextAndFinsh->setEnabled(true);
		ui.pushButton_step4->setEnabled(true);
		ui.widget_getMasterImg->setChangesProcessedArears(false);
		ui.widget_getMasterImg->setChangeActivArea(true);
		for (int i{ 1 }; i < masterObjct.getProcesArears()->size(); ++i)
		{
			widProcArea = new QtWidProcesArea(masterObjct.getProcesArears()[0][i].getSystemName() + " " + masterObjct.getProcesArears()[0][i].getUserName(), masterObjct.getProcesArears()[0][i].singelIsActivTresh(), masterObjct.getProcesArears()[0][i].getDoubelTresF(), masterObjct.getProcesArears()[0][i].getDoubelTresS(), i, ui.scrollArea_procesArears);
			connect(widProcArea, SIGNAL(setNewActivArea(int)), this, SLOT(slot_setActivProcesArea(int)));
			ui.verticalLayout_scrolProcesArea->addWidget(widProcArea);
			widProcAreaList.push_back(widProcArea);
			widProcAreaList[i-1]->setStyleSheet("");
			if (masterObjct.getProcesArears()[0][i].isActiv())
			{
				activProcesArea = i;
				widProcAreaList[i - 1]->setStyleSheet("color: red;");
			}
		}
		ui.widget_getMasterImg->updateImg();
	}
}

void QtSetupSimulator::slot_dataFromDialog(bool answer)
{
	if (!answer)
	{
		changes = false;
		isClose = false;
		brighCoreectDel = false;
		closeAddWindow = false;
		delActivProcesArea = false;
	}
		
	if (answer)
	{
		if (isClose&&changes)
		{
			emit dataToGUISim(&masterObjct);
			this->close();
		}
		else
		if (isClose)
		{
			this->close();
		}
		else
		if (brighCoreectDel)
		{
			brighCoreectDel = false;
			ui.pushButton_delCorect->setEnabled(false);
			ui.pushButton_setCorect->setEnabled(true);
			emit brightnesCorrectAreaDel();
		}
		if (closeAddWindow && !editProcesArea)
		{
			closeAddWindow = false;
			ui.stackWid_customTools->setCurrentIndex(0);
			if (masterObjct.getProcesArears()[0].size() > 1)
			{
				masterObjct.getProcesArears()[0].pop_back();
				if (masterObjct.getProcesArears()[0].size() > 1)
				{
					ui.pushButton_step4->setEnabled(true);
					ui.pushButton_nextAndFinsh->setEnabled(true);
				}
				else
				{
				}
				if (activProcesArea != 1)
					--activProcesArea;
				slot_setActivProcesArea(activProcesArea);
			}
			ui.widget_getMasterImg->setChangesProcessedArears(false);
			ui.widget_getMasterImg->updateImg();
			ui.pushButton_step1->setEnabled(true);
			ui.pushButton_step2->setEnabled(true);
			ui.pushButton_step3->setEnabled(true);
			ui.pushButton_back->setEnabled(true);
		}
		else if (closeAddWindow && editProcesArea)
		{
			closeAddWindow = false;
			editProcesArea = false;
			ui.stackWid_customTools->setCurrentIndex(0);
			activProcesArea = oldActivArea;
			masterObjct.getProcesArears()->pop_back();
			masterObjct.getProcesArears()[0][activProcesArea].setActiv(true);
			masterObjct.getProcesArears()[0][activProcesArea].setDraw(true);
			ui.widget_getMasterImg->setChangesProcessedArears(false);
			ui.widget_getMasterImg->setChangeActivArea(true);
			slot_setActivProcesArea(activProcesArea);
			ui.pushButton_step1->setEnabled(true);
			ui.pushButton_step2->setEnabled(true);
			ui.pushButton_step3->setEnabled(true);
			ui.pushButton_step4->setEnabled(true);
			ui.pushButton_back->setEnabled(true);
			ui.pushButton_nextAndFinsh->setEnabled(true);
		}
		else if (!closeAddWindow && editProcesArea)
		{
			editProcesArea = false;
			ui.stackWid_customTools->setCurrentIndex(0);
			masterObjct.getProcesArears()[0][oldActivArea] = masterObjct.getProcesArears()[0][activProcesArea];
			masterObjct.getProcesArears()->pop_back();
			activProcesArea = oldActivArea;
			masterObjct.getProcesArears()[0][activProcesArea].setActiv(true);
			masterObjct.getProcesArears()[0][activProcesArea].setDraw(true);
			ui.widget_getMasterImg->setChangesProcessedArears(false);
			ui.widget_getMasterImg->setChangeActivArea(true);
			slot_setActivProcesArea(activProcesArea);
			widProcAreaList[activProcesArea - 1]->setProcesName(masterObjct.getProcesArears()[0][activProcesArea].getSystemName() + " " + masterObjct.getProcesArears()[0][activProcesArea].getUserName());
			widProcAreaList[activProcesArea - 1]->setSliderPos(masterObjct.getProcesArears()[0][activProcesArea].singelIsActivTresh(), masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresF(), masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresS());
			ui.pushButton_step1->setEnabled(true);
			ui.pushButton_step2->setEnabled(true);
			ui.pushButton_step3->setEnabled(true);
			ui.pushButton_step4->setEnabled(true);
			ui.pushButton_back->setEnabled(true);
			ui.pushButton_nextAndFinsh->setEnabled(true);
		}
		if (delActivProcesArea)
		{
			delActivProcesArea = false;
			widProcAreaList[activProcesArea - 1]->deleteLater();
			widProcAreaList.erase(widProcAreaList.begin() + activProcesArea - 1);
			masterObjct.getProcesArears()[0].erase(masterObjct.getProcesArears()->begin() + activProcesArea);
			for (int i{ 0 }; i < widProcAreaList.size(); i++)
			{
				widProcAreaList[i]->setId(i + 1);
			}
			if (masterObjct.getProcesArears()->size() > 1)
			{
				if (activProcesArea != 1)
					--activProcesArea;
				slot_setActivProcesArea(activProcesArea);
			}

			else
			{
				ui.pushButton_CopyTool->setEnabled(false);
				ui.pushButton_delTool->setEnabled(false);
				ui.pushButton_editTool->setEnabled(false);
				ui.pushButton_nextAndFinsh->setEnabled(false);
				ui.pushButton_step4->setEnabled(false);
				ui.widget_getMasterImg->updateImg();
			}
		}
	}
}

void QtSetupSimulator::slot_dataFromAddTool(int procesedType, int areaType)
{	
	addTool->close();
	delete addTool;
	addTool = nullptr;
	ui.stackWid_customTools->setCurrentIndex(1);
	ui.widget_getMasterImg->setChangeActivArea(false);
	ui.widget_getMasterImg->setChangesProcessedArears(true);
	if (procesedType != 6)
		ui.widget_getMasterImg->add_rect(procesedType);
	else
		ui.widget_getMasterImg->add_circle();
	activProcesArea = masterObjct.getProcesArears()->size() - 1;
	setGUIParamsAddArea(procesedType);
	masterObjct.getProcesArears()[0][activProcesArea].setSystemName(masterObjct.getProcesArears()[0][activProcesArea].getProcesName() + ": "+ QString::number(activProcesArea));
	ui.label_procesProgName->setText(masterObjct.getProcesArears()[0][activProcesArea].getSystemName());
	for (int i{ 0 }; i < masterObjct.getProcesArears()[0].size() - 1; ++i)
	{
		masterObjct.getProcesArears()[0][i].setActiv(false);
	}
	ui.RButn_rect->setChecked(true);
	ui.RButn_entire_2->setChecked(true);
	//ui.widget_getMasterImg->updateImg();
	ui.pushButton_step1->setEnabled(false);
	ui.pushButton_step2->setEnabled(false);
	ui.pushButton_step3->setEnabled(false);
	ui.pushButton_step4->setEnabled(false);
	ui.pushButton_back->setEnabled(false);
	ui.pushButton_nextAndFinsh->setEnabled(false);
	ui.lineEdit_procesUserName->setText(masterObjct.getProcesArears()[0][activProcesArea].getUserName());
	ui.widget_getMasterImg->updateImg();
}

void QtSetupSimulator::slot_setBrightnesCorrectArea()
{
	activProcesArea = 0;
	ui.widget_getMasterImg->add_rect(0);
	ui.pushButton_delCorect->setEnabled(true);
	ui.pushButton_setCorect->setEnabled(false);
	//ui.widget_getMasterImg->addBrightnesCorrectRect(true);
	//ui.pushButton_setCorect->setChecked(true);
}

void QtSetupSimulator::slot_BrightnesCorrectIsSet(bool isSet)
{
	/*if (isSet)
	{
		ui.pushButton_delCorect->setEnabled(true);
		ui.pushButton_setCorect->setChecked(false);
	}
	else
	{
		ui.pushButton_delCorect->setEnabled(false);
	}*/
}

void QtSetupSimulator::slot_pushDelBrighArea()
{
	dialog = new QtMyDialog("Are you sure you want to delete brightnes correct?", this);
	dialog->show();
	connect(dialog, SIGNAL(answer(bool)), this, SLOT(slot_dataFromDialog(bool)));
	brighCoreectDel = true;
}

void QtSetupSimulator::slot_setCorect()
{
	ui.widget_getMasterImg->addBrightnesCorrectRect(false);
	ui.pushButton_setCorect->setChecked(false);
}

void QtSetupSimulator::slot_curntChngInTab(int)
{
	emit clic_pb();
}

void QtSetupSimulator::slot_closeAddTool()
{
	if (!editProcesArea)
	{
		dialog = new QtMyDialog("Are you sure you want to close add tool window?", this);
		dialog->show();
		closeAddWindow = true;
	}
	else
	{
		dialog = new QtMyDialog("Are you sure you want to canel change?", this);
		dialog->show();
		closeAddWindow = true;
	}
	connect(dialog, SIGNAL(answer(bool)), this, SLOT(slot_dataFromDialog(bool)));
}

void QtSetupSimulator::slot_OKAddTool()
{
	if (!editProcesArea)
	{
		ui.stackWid_customTools->setCurrentIndex(0);
		//masterObjct.getProcesArears()[0][activProcesArea].setActiv(false);
		ui.pushButton_CopyTool->setEnabled(true);
		ui.pushButton_delTool->setEnabled(true);
		ui.pushButton_editTool->setEnabled(true);
		ui.pushButton_nextAndFinsh->setEnabled(true);
		ui.pushButton_step4->setEnabled(true);
		ui.widget_getMasterImg->setChangesProcessedArears(false);
		ui.widget_getMasterImg->setChangeActivArea(true);
		widProcArea = new QtWidProcesArea(QString(masterObjct.getProcesArears()[0][activProcesArea].getSystemName() + " " + masterObjct.getProcesArears()[0][activProcesArea].getUserName()), masterObjct.getProcesArears()[0][activProcesArea].singelIsActivTresh(), masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresF(), masterObjct.getProcesArears()[0][activProcesArea].getDoubelTresS(), activProcesArea, ui.scrollArea_procesArears);
		connect(widProcArea, SIGNAL(setNewActivArea(int)), this, SLOT(slot_setActivProcesArea(int)));
		ui.verticalLayout_scrolProcesArea->addWidget(widProcArea);
		for (int i{ 0 }; i < widProcAreaList.size(); ++i)
		{
			widProcAreaList[i]->setStyleSheet("");
		}
		widProcArea->setStyleSheet("color: red;");
		widProcAreaList.push_back(widProcArea);
		ui.widget_getMasterImg->updateImg();
		ui.pushButton_step1->setEnabled(true);
		ui.pushButton_step2->setEnabled(true);
		ui.pushButton_step3->setEnabled(true);
		ui.pushButton_back->setEnabled(true);
	}
	else
	{
		dialog = new QtMyDialog("Are you sure you want to save change?", this);
		dialog->show();
		connect(dialog, SIGNAL(answer(bool)), this, SLOT(slot_dataFromDialog(bool)));
	}
}

void QtSetupSimulator::slot_chandeActivArea()
{
	//if(ui.stackWid_customTools->currentIndex())
}

void QtSetupSimulator::slot_PBPlusF()
{
	ui.widget_slider->getSlider()->setUpperValue(ui.widget_slider->getSlider()->upperValue()+1);
}

void QtSetupSimulator::slot_PBPlusS()
{
	ui.widget_slider->getSlider()->setLowerValue(ui.widget_slider->getSlider()->lowerValue() + 1);
}

void QtSetupSimulator::slot_PBMinusF()
{
	ui.widget_slider->getSlider()->setUpperValue(ui.widget_slider->getSlider()->upperValue() - 1);
}

void QtSetupSimulator::slot_PBMinusS()
{
	ui.widget_slider->getSlider()->setLowerValue(ui.widget_slider->getSlider()->lowerValue() - 1);
}

void QtSetupSimulator::slot_changeChecBox(int activPos)
{
	if (activPos == 0)
	{
		setOneSlider(true);
	}
	else if (activPos == 2)
	{
		setOneSlider(false);
	}
}

void QtSetupSimulator::slot_changeComboBoxScal(int activScal)
{
	if (activScal == 0)
	{
		ui.widget_slider->setRenge(0, 200);
	}
	if (activScal == 1)
	{
		ui.widget_slider->setRenge(0, 999);
	}
}

void QtSetupSimulator::slot_changeTresh()
{
	if (masterObjct.getProcesArears()[0][activProcesArea].singelIsActivTresh() && !editActivArea)
	{
		masterObjct.getProcesArears()[0][activProcesArea].setDoubelTreshS(ui.widget_slider->getSlider()->upperValue());
	}
	else if(!editActivArea)
	{
		masterObjct.getProcesArears()[0][activProcesArea].setDoubelTreshF(ui.widget_slider->getSlider()->lowerValue());
		masterObjct.getProcesArears()[0][activProcesArea].setDoubelTreshS(ui.widget_slider->getSlider()->upperValue());
	}
}

void QtSetupSimulator::slot_pushNext()
{
	if (activStep == 4)
	{
		changes = true;
		isClose = true;
		dialog = new QtMyDialog("Are you sure you want to make changes?", this);
		dialog->show(); 
		connect(dialog, SIGNAL(answer(bool)), this, SLOT(slot_dataFromDialog(bool)));
		int i;
		i = 0;
	}
	else 
	{
		++activStep;
		setGUIWid(activStep);
	}
	
}

void QtSetupSimulator::slot_pushBack()
{
	--activStep;
	setGUIWid(activStep);
}

void QtSetupSimulator::slot_pushCanel()
{
	this->close();
}

void QtSetupSimulator::slot_pushAddTool()
{
	addTool = new QtAddToolGUI();
	addTool->show();
	connect(addTool, SIGNAL(dataToSetup(int, int)), this, SLOT(slot_dataFromAddTool(int, int)));
}