#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtMySliderWid.h"
#include <cmath>
class QtMySliderWid : public QWidget
{
    Q_OBJECT
    double mul;
    int startX1, startX2;
    bool oneSlider;
public:
    QtMySliderWid(QWidget *parent = Q_NULLPTR);
    void setOneSlider(bool isOne);
    void setRenge(int min, int max);
    QxtSpanSlider* getSlider();
protected:
    Ui::QtMySliderWidClass ui;
protected slots:
    void slot_changeRange(int min, int max);
    void slot_clickMouse();
signals:
    void changeRange();
    void clicSlider();
};
