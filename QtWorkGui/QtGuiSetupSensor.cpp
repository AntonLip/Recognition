#include "QtGuiSetupSensor.h"


QtGuiSetupSensor::QtGuiSetupSensor(QWidget *parent)
	: QtSetupSimulator(parent)
{
	ui.setupUi(this);
	setUpGui();
	firstStepEnable = true;
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(false);
	connect(QtSetupSimulator::ui.pushButton_step1, SIGNAL(clicked()), this, SLOT(slot_pushStep1()));
	connect(QtSetupSimulator::ui.pushButton_step2, SIGNAL(clicked()), this, SLOT(slot_pushStep2()));
	connect(QtSetupSimulator::ui.pushButton_step3, SIGNAL(clicked()), this, SLOT(slot_pushStep3()));
	connect(QtSetupSimulator::ui.pushButton_step4, SIGNAL(clicked()), this, SLOT(slot_pushStep4()));
	connect(ui.setRoiWid, SIGNAL(CoordItemChange(QPointF&)), this, SLOT(slot_setOffset(QPointF&)));		    //при изменении положения РОИ меняются значения спинбоксов
	connect(ui.setRoiWid, SIGNAL(ItemFromWidgetSizeChange(QPointF&)), this, SLOT(slot_setSizeItemInSpinBox(QPointF&)));		//при изменении width ,height ROI изменяется значение в спинбоксах
	connect(this, SIGNAL(sl_buttonChangeSizeClicked(double)), ui.setRoiWid, SLOT(st_buttonChangeSizeClicked(double)));
	connect(ui.SpinB_binningHor, SIGNAL(valueChanged(int)), this, SLOT(slot_changeBinning(int)));		//binning horizontal
	connect(ui.SpinB_binningVer, SIGNAL(valueChanged(int)), this, SLOT(slot_changeBinning(int)));		//binning vertical
}

QtGuiSetupSensor::~QtGuiSetupSensor()
{

}



double QtGuiSetupSensor::getKoefficient(int value)
{
	return 1.0 / (1 + abs(ui.SpinB_binningHor->value() - ui.SpinB_binningVer->value()));
}

void QtGuiSetupSensor::setUpGui()
{
	HL_forFirstStep = new QHBoxLayout();
	QtSetupSimulator::ui.page_step1->setLayout(HL_forFirstStep);
	HL_forFirstStep->addWidget(ui.setupSensorParams);
}

void QtGuiSetupSensor::slot_updateSensorObject(ProcessedObj* sensorObj)
{
	sensorObject = sensorObj;
	if (!masterIsActivObject)
	{
		QtSetupSimulator::ui.widget_getMasterImg->updateProcessObj(sensorObj);
	}
}

void QtGuiSetupSensor::slot_pushStep1()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(false);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(sensorObject);
	masterIsActivObject = false;
}

void QtGuiSetupSensor::slot_pushStep2()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(true);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(&masterObjct);
	masterIsActivObject = true;
}

void QtGuiSetupSensor::slot_pushStep3()
{
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(true);
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(&masterObjct);
	masterIsActivObject = true;
}

void QtGuiSetupSensor::slot_setOffset(QPointF& point)
{
	ui.SpinB_ofsetY->setValue(point.y() * (3248.0 / ui.SpinB_binningVer->value() / 256));
	ui.SpinB_ofsetX->setValue(point.x() * (4872 / ui.SpinB_binningHor->value() / 256));
}

void QtGuiSetupSensor::slot_setSizeItemInSpinBox(QPointF& itemSize)
{
	ui.SpinB_height->setValue(itemSize.y() * (3248 / ui.SpinB_binningVer->value() / 256));
	ui.SpinB_width->setValue(itemSize.x() * (4872 / ui.SpinB_binningHor->value() / 256));
}

void QtGuiSetupSensor::slot_changeBinning(int value)
{
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_ofsetY->setValue(0);
	//ui.widget->resize(350, 200);
	double K = this->getKoefficient(value);
	K = K + 0;

	m_kW = 4872 / ui.SpinB_binningVer->value() / 256;
	m_kH = 3248 / ui.SpinB_binningHor->value() / 256;

	if (ui.SpinB_binningHor->value() - ui.SpinB_binningVer->value() < 0) //		H - W
	{
		//ui.widget->setGeometry(10, 10, 300.0 * K, 250 );
		ui.setRoiWid->setFixedHeight(256 * K);  //H

	}
	else if (ui.SpinB_binningHor->value() - ui.SpinB_binningVer->value() > 0)
	{
		//.widget->setGeometry(10, 10, 300 , 250 * K);
		ui.setRoiWid->setFixedWidth(256 * K);  //W
	}
	else
	{
		ui.setRoiWid->setFixedWidth(256);  //W
		ui.setRoiWid->setFixedHeight(256);;  //H
	}

	emit sl_buttonChangeSizeClicked(1);
	ui.SpinB_height->setValue(3248 / ui.SpinB_binningHor->value());
	ui.SpinB_width->setValue(4872 / ui.SpinB_binningVer->value());
}

void QtGuiSetupSensor::slot_pushFull()
{
	ui.PB_full->setDown(true);
	ui.PB_oneEighth->setDown(false);//1/4
	ui.PB_oneQuarter->setDown(false);//1/8

	//ui.spinBox_5->setValue(ui.widget->height() * (3248 / ui.spinBox_2->value() / 250));
	//ui.spinBox_6->setValue(ui.widget->width() * (4872 / ui.spinBox->value() / 300));


	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(3248 / ui.SpinB_binningVer->value());
	ui.SpinB_width->setValue(4872 / ui.SpinB_binningHor->value());

	emit sl_buttonChangeSizeClicked(1);
}

void QtGuiSetupSensor::slot_pushOneQuarter()
{
	ui.PB_full->setDown(false);
	ui.PB_oneQuarter->setDown(true);//1/4
	ui.PB_oneEighth->setDown(false);//1/8

	//ui.spinBox_5->setValue(ui.widget->height()/4 * (3248 / ui.spinBox_2->value() / 250));
	//ui.spinBox_6->setValue(ui.widget->width()/4 * (4872 / ui.spinBox->value() / 300));

	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(3248 / ui.SpinB_binningVer->value() / 4);
	ui.SpinB_width->setValue((4872 / ui.SpinB_binningHor->value() / 4));

	emit sl_buttonChangeSizeClicked(1.0 / 4);
}

void QtGuiSetupSensor::slot_pushOneEighth()
{
	ui.PB_full->setDown(false);
	ui.PB_oneQuarter->setDown(false);//1/4
	ui.PB_oneEighth->setDown(true);//1/8

	/*ui.spinBox_5->setValue(ui.widget->height() / 8 * (3248 / ui.spinBox_2->value() / 250));
	ui.spinBox_6->setValue(ui.widget->width() / 8 * (4872 / ui.spinBox->value() / 300));*/
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(3248 / ui.SpinB_binningVer->value() / 8);
	ui.SpinB_width->setValue(4872 / ui.SpinB_binningHor->value() / 8);

	emit sl_buttonChangeSizeClicked(1.0 / 8);
}

void QtGuiSetupSensor::slot_pushContinous()
{
	ui.PB_off->setDown(false);
	ui.PB_once->setDown(false);
	ui.PB_continuous->setDown(true);

	camera->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Continuous";
	pFeature->SetValue(temp);
}

void QtGuiSetupSensor::slot_pushOnce()
{
	ui.PB_off->setDown(false);
	ui.PB_once->setDown(true);
	ui.PB_continuous->setDown(false);

	camera->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Once";
	pFeature->SetValue(temp);
}

void QtGuiSetupSensor::slot_pushOff()
{
	ui.PB_off->setDown(true);
	ui.PB_once->setDown(false);
	ui.PB_continuous->setDown(false);

	camera->GetFeatureByName("ExposureAuto", pFeature);
	char* temp = "Off";
	pFeature->SetValue(temp);
}

void QtGuiSetupSensor::slot_dataFromWorkWithSensor(ProcessedObj* sensorObj, ProcessedObj* masterObj, CameraPtrVector& cams, int index)
{
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(sensorObj);
	masterObjct = *masterObj;
	sensorObject = sensorObj;
	masterIsActivObject = false;
	cameras = cams;
}