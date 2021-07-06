#include "QtWidDoubelSlider.h"

QtWidDoubelSlider::QtWidDoubelSlider(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.PB_leftDecrease, SIGNAL(clicked(bool)), this, SLOT(slot_leftSliderDecrease()));
	connect(ui.PB_leftIncrease, SIGNAL(clicked(bool)), this, SLOT(slot_leftSliderIncrease()));
	connect(ui.PB_rightDecrease, SIGNAL(clicked(bool)), this, SLOT(slot_rightSliderDecrease()));
	connect(ui.PB_rightIncrease, SIGNAL(clicked(bool)), this, SLOT(slot_rightSliderIncrease()));
}

QtWidDoubelSlider::~QtWidDoubelSlider()
{
}

void QtWidDoubelSlider::setRenge(int min, int max)
{
	ui.doubelSlider->setRenge(min, max);
}

void QtWidDoubelSlider::slot_rightSliderIncrease()
{
	ui.doubelSlider->getSlider()->setUpperValue(ui.doubelSlider->getSlider()->upperValue() + 1);
}

void QtWidDoubelSlider::slot_leftSliderDecrease()
{
	ui.doubelSlider->getSlider()->setUpperValue(ui.doubelSlider->getSlider()->lowerValue() - 1);
}

void QtWidDoubelSlider::slot_leftSliderIncrease()
{
	ui.doubelSlider->getSlider()->setUpperValue(ui.doubelSlider->getSlider()->lowerValue() + 1);
}

void QtWidDoubelSlider::slot_rightSliderDecrease()
{
	ui.doubelSlider->getSlider()->setUpperValue(ui.doubelSlider->getSlider()->upperValue() - 1);
}
