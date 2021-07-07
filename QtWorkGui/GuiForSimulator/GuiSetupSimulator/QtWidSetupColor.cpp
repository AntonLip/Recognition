#include "QtWidSetupColor.h"

QtWidSetupColor::QtWidSetupColor(QWidget *parent)
	: QWidget(parent),
	buferColorThreshold_{},
	activColorThreshold_{},
	colorProcessing_{nullptr},
	updateColorProcessing{false}
{
	ui.setupUi(this);
	this->updateGeometry();
	ui.H_lavel->setRenge(0, 255);
	ui.S_lavel->setRenge(0, 255);
	ui.V_lavel->setRenge(0, 255);
	connect(ui.PB_canel, SIGNAL(clicked()), this, SLOT(slot_canel()));
	connect(ui.PB_ok, SIGNAL(clicked()), this, SLOT(slot_OK()));
	connect(ui.H_lavel, SIGNAL(signal_changeSliderPosition(int, int)), this, SLOT(slot_changeThreshold_h(int, int)));
	connect(ui.S_lavel, SIGNAL(signal_changeSliderPosition(int, int)), this, SLOT(slot_changeThreshold_s(int, int)));
	connect(ui.V_lavel, SIGNAL(signal_changeSliderPosition(int, int)), this, SLOT(slot_changeThreshold_v(int, int)));
	setAttribute(Qt::WA_DeleteOnClose, true);
}

QtWidSetupColor::~QtWidSetupColor()
{
}

void QtWidSetupColor::slot_canel()
{
	colorProcessing_->setProcessedThreshold(buferColorThreshold_);
	emit signal_changeThreshold();
	emit signal_endSetup();
}

void QtWidSetupColor::slot_dataFromSetupSimulator(QtProcessedArea* colorProcessing)
{
	colorProcessing_ = colorProcessing;
	colorProcessing_->getProcessedThreshold(buferColorThreshold_);
	activColorThreshold_ = buferColorThreshold_;
	ui.H_lavel->setSliderPosition(activColorThreshold_[0], activColorThreshold_[1]);
	ui.S_lavel->setSliderPosition(activColorThreshold_[2], activColorThreshold_[3]);
	ui.V_lavel->setSliderPosition(activColorThreshold_[4], activColorThreshold_[5]);
	updateColorProcessing = true;
}

void QtWidSetupColor::slot_changeThreshold_h(int min, int max)
{
	activColorThreshold_[0] = min;
	activColorThreshold_[1] = max;
	colorProcessing_->setProcessedThreshold(activColorThreshold_);
	if(updateColorProcessing)
		emit signal_changeThreshold();
}

void QtWidSetupColor::slot_changeThreshold_s(int min, int max)
{
	activColorThreshold_[2] = min;
	activColorThreshold_[3] = max;
	colorProcessing_->setProcessedThreshold(activColorThreshold_);
	if(updateColorProcessing)
		emit signal_changeThreshold();
}

void QtWidSetupColor::slot_changeThreshold_v(int min, int max)
{
	activColorThreshold_[4] = min;
	activColorThreshold_[5] = max;
	colorProcessing_->setProcessedThreshold(activColorThreshold_);
	if(updateColorProcessing)
		emit signal_changeThreshold();
}

void QtWidSetupColor::slot_OK()
{
	emit signal_endSetup();
}
