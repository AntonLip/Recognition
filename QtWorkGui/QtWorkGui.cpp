#include "QtWorkGui.h"

QtWorkGui::QtWorkGui(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	QObject::connect(ui.pushButton_conect, SIGNAL(clicked()), this, SLOT(conect_slot()));
	QObject::connect(ui.pushButton_simulator, SIGNAL(clicked()), this, SLOT(openSimulator_slot()));

	simulatorMenu = new QtGuiSimulator();
	connectMenu = new QtConnect();
	QObject::connect(this, SIGNAL(getDataToSimulator(cv::Mat, QString)), simulatorMenu, SLOT(dataFromMainMenu(cv::Mat, QString)));
}

void QtWorkGui::conect_slot()
{
	qwer = new QtSimCamera();
	qwer->show();
	connectMenu->show();
	this->close();
}

void QtWorkGui::openSimulator_slot()
{
	QString qstr_bufer{ QFileDialog::getOpenFileName(this, "Images", "D:/", tr("Images files (*.png *.jpg *.bmp)")) };
	cv::Mat img_bufer;
	img_bufer = cv::imread(qstr_bufer.toStdString());
	if (!img_bufer.empty())// checking that image has loaded 
	{
		simulatorMenu->show();
		emit getDataToSimulator(img_bufer, qstr_bufer);
		this->close();
	}
	else
	{
		QMessageBox::critical(nullptr, QObject::tr("Warning"), QObject::tr("Image not loaded")); //massage about error download
	}
}

