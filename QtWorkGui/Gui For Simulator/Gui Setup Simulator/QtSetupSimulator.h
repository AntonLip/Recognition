#pragma once

#include <QWidget>
#include "ui_QtSetupSimulator.h"
#include "Dialog/QtMyDialog.h"
#include "QtAddToolGUI.h"
#include "QButtonGroup"
#include "QtWidProcesArea.h"
#include "Loger/simplLoger.h"
#include "qmessagebox.h"

class QtSetupSimulator : public QWidget
{
	Q_OBJECT
protected:
	QList<QtWidProcesArea*> widProcAreaList;
	ProcessedObj masterObjct;
	QtMyDialog* dialog;
	QtAddToolGUI* addTool;
	QtWidProcesArea* widProcArea;
	bool oneSlider;
	int activStep;
	int activProcesArea;
	int oldActivArea;
	bool changes;
	bool isClose;
	bool brighCoreectDel;
	bool closeAddWindow;
	bool horSliderHaveTwoSlider;
	bool delActivProcesArea;
	bool editActivArea;
	bool editProcesArea;
	bool firstStepEnable;
	void setGUIWid(int newActivStep);
	void setGUIParamsAddArea(int typeProcesArea);
	void closeEvent(QCloseEvent* event);
	void addProceseArea();

public:
	QtSetupSimulator(QWidget *parent = Q_NULLPTR);
	~QtSetupSimulator();
	
protected:
	Ui::QtSetupSimulator ui;
	void mousePressEvent(QMouseEvent* event);
	void setOneSlider(bool oneSlider);
protected slots:
	void slot_pushStep1();
	void slot_pushStep2();
	void slot_pushStep3();
	void slot_pushStep4();
	void slot_pushNext();
	void slot_pushBack();
	void slot_pushCanel();
	void slot_pushAddTool();
	void slot_dataFromGUISim(ProcessedObj *newMasterObj);
	void slot_dataFromDialog(bool answer);
	void slot_dataFromAddTool(int procesedType, int areaType);
	void slot_setBrightnesCorrectArea();
	void slot_BrightnesCorrectIsSet(bool isSet);
	void slot_pushDelBrighArea();
	void slot_setCorect();
	void slot_curntChngInTab(int);
	void slot_closeAddTool();
	void slot_OKAddTool();
	void slot_chandeActivArea();
	void slot_PBPlusF();
	void slot_PBPlusS();
	void slot_PBMinusF();
	void slot_PBMinusS();
	void slot_changeChecBox(int activPos);
	void slot_changeComboBoxScal(int activScal);
	void slot_changeTresh();
	void slot_setActivProcesArea(int activ);
	void slot_pushDelActivProcArea();
	void slot_chengeAreaType();
	void slot_changeUserNameArea(QString newName);
	void slot_editProceArea();
	void slot_copyProceArea();
	void slot_changeWidSteps(int step);
	void slot_resetAngelRect();
	void slot_getActivProcesAreaTowidgetMasterImg();
	void slot_registImageFromFile();
signals:
	void dataToGUISim(ProcessedObj* changedObj);
	void brightnesCorrectAreaDel();
	void clic_pb();
	void resetRectAngel(int activRect);
};
