#include "QtGuiSetupSensor.h"


QtGuiSetupSensor::QtGuiSetupSensor(QWidget* parent)
	: QtSetupSimulator(parent),
	maxFrameSize(QSizeF(4872.0, 3248.0)),
	chagheROI(false)
{
	ui.setupUi(this);
	setUpGui();
	firstStepEnable = true;
	QtSetupSimulator::ui.widget_getMasterImg->setProcessObjStatus(false);
	connect(QtSetupSimulator::ui.pushButton_step1, SIGNAL(clicked()), this, SLOT(slot_pushStep1()));
	connect(QtSetupSimulator::ui.pushButton_step2, SIGNAL(clicked()), this, SLOT(slot_pushStep2()));
	connect(QtSetupSimulator::ui.pushButton_step3, SIGNAL(clicked()), this, SLOT(slot_pushStep3()));
	connect(QtSetupSimulator::ui.pushButton_step4, SIGNAL(clicked()), this, SLOT(slot_pushStep4()));
	connect(ui.setRoiWid, SIGNAL(CoordItemChange(QRectF&)), this, SLOT(slot_setOffset(QRectF&)));		    //��� ��������� ��������� ��� �������� �������� ����������
	connect(ui.setRoiWid, SIGNAL(ItemFromWidgetSizeChange(QSizeF&)), this, SLOT(slot_setSizeItemInSpinBox(QSizeF&)));		//��� ��������� width ,height ROI ���������� �������� � ����������
	connect(this, SIGNAL(sl_buttonChangeSizeClicked(double)), ui.setRoiWid, SLOT(st_buttonChangeSizeClicked(double)));
	connect(ui.SpinB_binningHor, SIGNAL(valueChanged(int)), this, SLOT(slot_changeBinning(int)));		//binning horizontal
	connect(ui.SpinB_binningVer, SIGNAL(valueChanged(int)), this, SLOT(slot_changeBinning(int)));		//binning vertical
	connect(ui.PB_setRoi,SIGNAL(clicked()),this,SLOT(slot_pushSetRoi()));
	connect(ui.PB_full,SIGNAL(clicked()),this,SLOT(slot_pushFull()));
	connect(ui.PB_oneQuarter,SIGNAL(clicked()),this,SLOT(slot_pushOneQuarter()));
	connect(ui.PB_oneEighth,SIGNAL(clicked()),this,SLOT(slot_pushOneEighth()));
	connect(ui.PB_continuous,SIGNAL(clicked()),this,SLOT(slot_pushContinous()));
	connect(ui.PB_once,SIGNAL(clicked()),this,SLOT(slot_pushOnce()));
	connect(ui.PB_off,SIGNAL(clicked()),this,SLOT(slot_pushOff()));
	connect(ui.SpinB_ofsetX,SIGNAL(valueChanged(int)),this,SLOT(slot_cahgeOfsetX(int)));
	connect(ui.SpinB_ofsetY,SIGNAL(valueChanged(int)),this,SLOT(slot_cahgeOfsetY(int)));
	connect(ui.SpinB_height,SIGNAL(valueChanged(int)),this,SLOT(slot_cahgeHeigth(int)));
	connect(ui.SpinB_width,SIGNAL(valueChanged(int)),this,SLOT(slot_cahgeWidth(int)));
	connect(this, SIGNAL(signal_getNewOffsetX(int)), ui.setRoiWid, SLOT(slot_setNewOffsetX(int)));
	connect(this, SIGNAL(signal_getNewOffsetY(int)), ui.setRoiWid, SLOT(slot_setNewOffsetY(int)));
	connect(this, SIGNAL(signal_getNewHeigth(int)), ui.setRoiWid, SLOT(slot_setNewHeigth(int)));
	connect(this, SIGNAL(signal_getNewWidth(int)), ui.setRoiWid, SLOT(slot_setNewWidth(int)));
	//connect(ui.spinB_trigerDelay, SIGNAL(valueChanged(int)), QtSetupSimulator::ui.widget_getMasterImg, SLOT(slot_updateTrigerDelay(int)));

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

void QtGuiSetupSensor::setCameraParamsInGui()
{
	VmbInt64_t buferForAnyParams{ 0 };
	camera->GetFeatureByName("BinningHorizontal", pFeature);
	pFeature->GetValue(buferForAnyParams);
	ui.SpinB_binningHor->setValue(static_cast<int>(buferForAnyParams));

	camera->GetFeatureByName("BinningVertical", pFeature);
	pFeature->GetValue(buferForAnyParams);
	ui.SpinB_binningVer->setValue(static_cast<int>(buferForAnyParams));

	camera->GetFeatureByName("Height", pFeature);
	pFeature->GetValue(buferForAnyParams);
	ui.SpinB_height->setValue(static_cast<int>(buferForAnyParams));

	camera->GetFeatureByName("Width", pFeature);
	pFeature->GetValue(buferForAnyParams);
	ui.SpinB_width->setValue(static_cast<int>(buferForAnyParams));

	camera->GetFeatureByName("OffsetX", pFeature);
	pFeature->GetValue(buferForAnyParams);
	ui.SpinB_ofsetX->setValue(static_cast<int>(buferForAnyParams));

	camera->GetFeatureByName("OffsetY", pFeature);
	pFeature->GetValue(buferForAnyParams);
	ui.SpinB_ofsetY->setValue(static_cast<int>(buferForAnyParams));
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

void QtGuiSetupSensor::slot_cahgeOfsetX(int newOffsetX)
{
	if (chagheROI)
	{
		ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() - newOffsetX);
		emit signal_getNewOffsetX(newOffsetX / (maxFrameSize.width() / ui.SpinB_binningHor->value() / ui.setRoiWid->size().width()));
	}
}

void QtGuiSetupSensor::slot_cahgeOfsetY(int newOffsetY)
{
	if (chagheROI)
	{
		ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() - newOffsetY);
		int a{};
		emit signal_getNewOffsetY(newOffsetY / (maxFrameSize.height() / ui.SpinB_binningVer->value() / ui.setRoiWid->size().height()));
	}
}

void QtGuiSetupSensor::slot_cahgeHeigth(int newHeigth)
{
	if (chagheROI)
	{
		ui.SpinB_ofsetY->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() - newHeigth);
		emit signal_getNewHeigth(newHeigth / (maxFrameSize.height() / ui.SpinB_binningVer->value() / ui.setRoiWid->size().height()));
	}
}

void QtGuiSetupSensor::slot_cahgeWidth(int newWidth)
{
	if (chagheROI)
	{
		ui.SpinB_ofsetX->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() - newWidth);
		emit signal_getNewWidth(newWidth / (maxFrameSize.width() / ui.SpinB_binningHor->value() / ui.setRoiWid->size().width()));
	}
}

void QtGuiSetupSensor::slot_setOffset(QRectF& point)
{
	chagheROI = false;
	ui.SpinB_ofsetY->setValue(point.y() * (maxFrameSize.height() / ui.SpinB_binningVer->value() / ui.setRoiWid->size().height()));
	ui.SpinB_ofsetX->setValue(point.x() * (maxFrameSize.width() / ui.SpinB_binningHor->value() / ui.setRoiWid->size().width()));
	ui.SpinB_height->setValue(point.height() * (maxFrameSize.height() / ui.SpinB_binningVer->value() / ui.setRoiWid->size().height()));
	ui.SpinB_width->setValue(point.width() * (maxFrameSize.width() / ui.SpinB_binningHor->value() / ui.setRoiWid->size().width()));

	ui.SpinB_ofsetY->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() - point.height());
	ui.SpinB_ofsetX->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() - point.width());
	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() - point.y());
	ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() - point.x());

	if (ui.SpinB_width->maximum() >= maxFrameSize.width() / ui.SpinB_binningHor->value())
		ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value());
	if (ui.SpinB_ofsetY->maximum() < 0)
		ui.SpinB_ofsetY->setMaximum(0);
	if (ui.SpinB_ofsetX->maximum() < 0)
		ui.SpinB_ofsetX->setMaximum(0);	
	if (ui.SpinB_height->maximum() >= maxFrameSize.height() / ui.SpinB_binningVer->value())
		ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value());
	chagheROI = true;
}

void QtGuiSetupSensor::slot_setSizeItemInSpinBox(QSizeF& itemSize)
{
	ui.SpinB_height->setValue(itemSize.height() * (maxFrameSize.height() / ui.SpinB_binningVer->value() / maxFrameSize.height()));
	ui.SpinB_width->setValue(itemSize.width() * (maxFrameSize.width() / ui.SpinB_binningHor->value() / maxFrameSize.width()));
}

void QtGuiSetupSensor::slot_changeBinning(int value)
{
	
	double K = this->getKoefficient(value);
	K = K + 0;

	//m_kW = 4872 / ui.SpinB_binningVer->value() / 256;
	//m_kH = 3248 / ui.SpinB_binningHor->value() / 256;

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
	
	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value());
	ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value());	
	
	chagheROI = false;
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value());
	ui.SpinB_width->setValue(maxFrameSize.width() / ui.SpinB_binningHor->value());
	chagheROI = true;
	
	emit sl_buttonChangeSizeClicked(1);
}

void QtGuiSetupSensor::slot_pushFull()
{
	ui.PB_full->setDown(true);
	ui.PB_oneEighth->setDown(false);//1/4
	ui.PB_oneQuarter->setDown(false);//1/8

	//ui.spinBox_5->setValue(ui.widget->height() * (3248 / ui.spinBox_2->value() / 250));
	//ui.spinBox_6->setValue(ui.widget->width() * (4872 / ui.spinBox->value() / 300));

	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value());
	ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value());

	chagheROI = false;
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value());
	ui.SpinB_width->setValue(maxFrameSize.width() / ui.SpinB_binningHor->value());
	chagheROI = true;
	emit sl_buttonChangeSizeClicked(1);
}

void QtGuiSetupSensor::slot_pushOneQuarter()
{
	ui.PB_full->setDown(false);
	ui.PB_oneQuarter->setDown(true);//1/4
	ui.PB_oneEighth->setDown(false);//1/8

	//ui.spinBox_5->setValue(ui.widget->height()/4 * (3248 / ui.spinBox_2->value() / 250));
	//ui.spinBox_6->setValue(ui.widget->width()/4 * (4872 / ui.spinBox->value() / 300));

	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() / 4);
	ui.SpinB_width->setMaximum((maxFrameSize.width() / ui.SpinB_binningHor->value() / 4));
	chagheROI = false;
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value() / 4);
	ui.SpinB_width->setValue((maxFrameSize.width() / ui.SpinB_binningHor->value() / 4));
	chagheROI = true;
	emit sl_buttonChangeSizeClicked(1.0 / 4);
}

void QtGuiSetupSensor::slot_pushOneEighth()
{
	ui.PB_full->setDown(false);
	ui.PB_oneQuarter->setDown(false);//1/4
	ui.PB_oneEighth->setDown(true);//1/8

	/*ui.spinBox_5->setValue(ui.widget->height() / 8 * (3248 / ui.spinBox_2->value() / 250));
	ui.spinBox_6->setValue(ui.widget->width() / 8 * (4872 / ui.spinBox->value() / 300));*/

	ui.SpinB_height->setMaximum(maxFrameSize.height() / ui.SpinB_binningVer->value() / 8);
	ui.SpinB_width->setMaximum(maxFrameSize.width() / ui.SpinB_binningHor->value() / 8);

	chagheROI = false;
	ui.SpinB_ofsetY->setValue(0);
	ui.SpinB_ofsetX->setValue(0);
	ui.SpinB_height->setValue(maxFrameSize.height() / ui.SpinB_binningVer->value() / 8);
	ui.SpinB_width->setValue(maxFrameSize.width() / ui.SpinB_binningHor->value() / 8);
	chagheROI = true;
	emit sl_buttonChangeSizeClicked(1.0 / 8);
}

void QtGuiSetupSensor::slot_pushSetRoi()
{

	LOG.logMessege("Start changing camera settings", _INFO_);
	camera->GetFeatureByName("AcquisitionStop", pFeature);
	pFeature->RunCommand();

	camera->EndCapture();
	camera->FlushQueue();
	camera->RevokeAllFrames();
	/***********************************/
	//binning ���������� � tab2
	camera->GetFeatureByName("BinningHorizontal", pFeature);
	pFeature->SetValue(ui.SpinB_binningHor->value());

	camera->GetFeatureByName("BinningVertical", pFeature);
	pFeature->SetValue(ui.SpinB_binningVer->value());

	camera->GetFeatureByName("Height", pFeature);
	pFeature->SetValue(ui.SpinB_height->value());

	camera->GetFeatureByName("Width", pFeature);
	int tmp = ui.SpinB_width->value();
	while (tmp % 4 != 0)
	{
		tmp++;
	}
	pFeature->SetValue(tmp);

	camera->GetFeatureByName("OffsetX", pFeature);
	pFeature->SetValue(ui.SpinB_ofsetX->value());

	camera->GetFeatureByName("OffsetY", pFeature);
	pFeature->SetValue(ui.SpinB_ofsetY->value());
	/****************************************/


	// Get the image size for the required buffer								�������� ������ ����������� ��� ������ ������������ ������
	// Allocate memory for frame buffer											�������� ������ ��� ������,������� ����� ������� ����
	// Register frame observer/callback for each frame							��������������� ����������� ������ / �������� ����� ��� ������� �����
	// Announce frame to the API												������������ ���� API


	camera->GetFeatureByName("PayloadSize", pFeature);							//�������� ������� �� ����� "������ �������� ��������"(������ ����� ������). ���������� ������� ���������� � pFeature  Feature-��������������, �������
	VmbInt64_t oldNPLS{ nPLS };
	pFeature->GetValue(nPLS);													//������ �������� ������� �������� ��������


	for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)		//FramePtrVector - ������ ���������� �� �����, frames.begin()- ������ ����, frames.end()- ��������� ����. ���� ����������� �� ������� �����
	{
		if (oldNPLS!=nPLS)
			(*iter).reset(new Frame(nPLS));											//����� ���������� ��������. ��������� ����� ������ ��� ,������� ����� ( ������ �� ����� ����� �������� nPLS)
		//obs = 
		(*iter)->RegisterObserver(IFrameObserverPtr(new FrameObserver(camera, videoDisplay,sensorObject)));//���������������� ����������� camera(��� ��������� �� ���� ������,������� �� ��������� �� ID)
		camera->AnnounceFrame(*iter);											//������������� ���� �� camera API
	}
	makePhoto = false;
	// Start the capture engine (API)											������ ��������� ������� ������
	camera->StartCapture();
	for (FramePtrVector::iterator iter = frames.begin(); frames.end() != iter; ++iter)
	{
		// Put frame into the frame queue										��������� ���� � ������� ������
		camera->QueueFrame(*iter);
	}
	// Start the acquisition engine (camera)									��������� �������� ����� ������ (������)
	camera->GetFeatureByName("AcquisitionStart", pFeature);						//AcquisitionStart ������ ��������� �����������
	pFeature->RunCommand();
	LOG.logMessege("Camera settings set", _INFO_);
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

void QtGuiSetupSensor::slot_dataFromWorkWithSensor(ProcessedObj* sensorObj, ProcessedObj* masterObj, CameraPtr& cams, int delay, QtGuiDisplay* videoDisplay_)
{
	QtSetupSimulator::ui.widget_getMasterImg->setActivProcessObj(sensorObj);
	masterObjct = *masterObj;
	sensorObject = sensorObj;
	masterIsActivObject = false;
	camera = cams;
	videoDisplay = videoDisplay_;
	ui.spinB_trigerDelay->setValue(delay);
	//setCameraParamsInGui();
	connect(ui.spinB_trigerDelay, SIGNAL(valueChanged(int)), videoDisplay, SLOT(slot_updateTrigerDelay(int)));
	connect(ui.PB_setRoi, SIGNAL(clicked()), videoDisplay, SLOT(slot_delUpdateImageTime()));
}