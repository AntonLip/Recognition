#pragma once

#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "ui_QtWorkGui.h"
#include "QtGuiSimulator.h"
#include "QtConnect.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "QtSimCamera.h"
#include "simplLoger.h"

class QtWorkGui : public QMainWindow
{
    Q_OBJECT

public:
    QtWorkGui(QWidget *parent = Q_NULLPTR);
    ~QtWorkGui();
private:
    QtGuiSimulator* simulatorMenu;
    QtConnect* connectMenu;
    QtSimCamera* qwer;
    Ui::QtWorkGuiClass ui;
    simplLoger LOG;
private slots:
    void conect_slot();
    void openSimulator_slot();
    void slot_dataFromCameraConect();
signals:
    void getDataToSimulator(cv::Mat InputImg, QString filename);
};
