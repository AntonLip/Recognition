#include "QtMySliderWid.h"

QtMySliderWid::QtMySliderWid(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.horizontalSlider->setTickPosition(QSlider::TicksBelow);
    ui.horizontalSlider->setHandleMovementMode(QxtSpanSlider::NoCrossing);
    connect(ui.horizontalSlider, SIGNAL(spanChanged(int, int)), this, SLOT(slot_changeRange(int, int)));
    connect(ui.horizontalSlider, SIGNAL(moseClicked_()), this, SLOT(slot_clickMouse()));
    mul = (ui.horizontalSlider->size().width() - 10) / 99.0;
    startX1 = ui.label_min->x();
    startX2 = ui.label_max->x();
    oneSlider = false;
}

void QtMySliderWid::setOneSlider(bool isOne)
{
    if (!oneSlider && isOne)
    {
        oneSlider = isOne;
        ui.label_min->hide();
        startX2 = startX2 - 8;
        ui.horizontalSlider->setLowerValue(ui.horizontalSlider->upperValue());
        slot_changeRange(ui.horizontalSlider->lowerValue(), ui.horizontalSlider->upperValue());
    }
    else if (oneSlider && !isOne)
    {
        oneSlider = isOne;
        ui.label_min->show();
        startX2 = startX2 + 8;
        slot_changeRange(ui.horizontalSlider->lowerValue(), ui.horizontalSlider->upperValue());
    }
   // oneSlider = isOne;
}

void QtMySliderWid::setRenge(int min, int max)
{
    mul = (ui.horizontalSlider->size().width() - 10) / static_cast<double>(max-min);
    ui.horizontalSlider->setRange(min, max);
    if (ui.horizontalSlider->lowerValue() < max)
    {
        ui.horizontalSlider->setUpperValue(ui.horizontalSlider->lowerValue());
    }
    else
    {
        ui.horizontalSlider->setUpperValue(max);
        ui.horizontalSlider->setLowerValue(max);
    }
}

QxtSpanSlider* QtMySliderWid::getSlider()
{
    return ui.horizontalSlider;
}

void QtMySliderWid::slot_clickMouse()
{
    emit clicSlider();
}

void QtMySliderWid::slot_changeRange(int min, int max)
{
    if (!oneSlider)
    {
        ui.label_max->setText(QString::number(max));
        ui.label_max->setGeometry(startX2 + floor(mul * max), ui.label_max->y(), ui.label_max->size().width(), ui.label_max->size().height());
        ui.label_min->setText(QString::number(min));
        ui.label_min->setGeometry(startX1 + floor(mul * min), ui.label_max->y(), ui.label_max->size().width(), ui.label_max->size().height());
    }
    else
    {
        ui.horizontalSlider->setLowerValue(max-1);
        ui.label_max->setText(QString::number(max));
        ui.label_max->setGeometry(startX2 + floor(mul * max), ui.label_max->y(), ui.label_max->size().width(), ui.label_max->size().height());
    }
    emit changeRange();
}