#pragma once

#include <QWidget>
#include "ui_QtWidSetupColor.h"
#include "ProcessingObject/QtProcessedArea.h"

class QtWidSetupColor : public QWidget
{
	Q_OBJECT
	std::vector<int> buferColorThreshold_;
	std::vector<int> activColorThreshold_;
	QtProcessedArea* colorProcessing_;
	bool updateColorProcessing;
public:
	QtWidSetupColor(QWidget *parent = Q_NULLPTR);
	~QtWidSetupColor();

private:
	Ui::QtWidSetupColor ui;
private slots:
	void slot_OK();
	void slot_canel();
	void slot_dataFromSetupSimulator(QtProcessedArea* colorProcessing);
	void slot_changeThreshold_h(int min, int max);
	void slot_changeThreshold_s(int min, int max);
	void slot_changeThreshold_v(int min, int max);
signals:
	void signal_changeThreshold();
	void signal_endSetup();
};
