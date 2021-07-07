#pragma once

#include <QWidget>
#include "ui_QtWidDoubelSlider.h"

class QtWidDoubelSlider : public QWidget
{
	Q_OBJECT

public:
	QtWidDoubelSlider(QWidget *parent = Q_NULLPTR);
	~QtWidDoubelSlider();
	void setRenge(int min, int max);
	void setSliderPosition(int min, int max);
private:
	Ui::QtWidDoubelSlider ui;

private slots:
	void slot_rightSliderDecrease();
	void slot_rightSliderIncrease();
	void slot_leftSliderDecrease();
	void slot_leftSliderIncrease();
	void slot_chageSliderPosition();
signals:
	void signal_changeSliderPosition(int minValue, int maxValue);
};
