#pragma once

#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "ui_QtWorkGui.h"
#include "QtGuiSimulator.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

class QtWorkGui : public QMainWindow
{
    Q_OBJECT

public:
    QtWorkGui(QWidget *parent = Q_NULLPTR);

private:
    QtGuiSimulator* simulatorMenu;
    Ui::QtWorkGuiClass ui;
private slots:
    void conect_slot();
    void openSimulator_slot();
signals:
    void getDataToSimulator(cv::Mat InputImg, QString filename);
};
