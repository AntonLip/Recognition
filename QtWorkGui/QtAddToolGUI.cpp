#include "QtAddToolGUI.h"

QtAddToolGUI::QtAddToolGUI(QWidget *parent)
	: QWidget(parent),
	dialog(nullptr),
	checkedButton(0),
	isClose(false)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	PButtonList.push_back(ui.PButtn_outline);
	PButtonList.push_back(ui.PButtn_color);
	PButtonList.push_back(ui.PButton_edgePix);
	PButtonList.push_back(ui.PButton_positAdjust);
	PButtonList.push_back(ui.PButton_width);
	PButtonList.push_back(ui.PButton_diametr);
	PButtonList.push_back(ui.PButton_edge);
	PButtonList.push_back(ui.PButton_pitch);
	PButtonList.push_back(ui.PButton_highSpeedPosit);
	PButtonList.push_back(ui.PButton_OCR);
	for (int i{ 0 }; i < PButtonList.size(); ++i)
	{
		PButtonList[i]->setCheckable(true);
		connect(PButtonList[i], SIGNAL(clicked()), this, SLOT(slot_pushButtonClic()));
		if (i == 0)
		{
			PButtonList[i]->setChecked(true);
			checkedButton = 0;
		}
	}
	connect(ui.tabWidget_Tools, SIGNAL(currentChanged(int)), this, SLOT(slot_chanchTab(int)));
	connect(ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(slot_clicOK()));
	connect(ui.pushButton_Canel, SIGNAL(clicked()), this, SLOT(slot_clicCanel()));
}

QtAddToolGUI::~QtAddToolGUI()
{
	delete dialog;
	dialog = nullptr;
}

void QtAddToolGUI::closeEvent(QCloseEvent* event)
{
	if (!isClose)
	{
		event->ignore();
		isClose = true;
		dialog = new QtMyDialog("Are you sure you want to close setup simulator window?", this);
		dialog->show();
		connect(dialog, SIGNAL(answer(bool)), this, SLOT(slot_dataFromDialog(bool)));
	}
	else
	{
		this->close();
	}
}

void QtAddToolGUI::slot_chanchTab(int activTab)
{
	QString desiredButtn{ "OCR" };
	if (activTab == 0)
	{
		desiredButtn = "Outline";
	}
	else if (activTab == 1)
	{
		desiredButtn = "Width";
	}
	PButtonList[checkedButton]->setChecked(false);
	for (int i{ 0 }; i < PButtonList.size(); ++i)
	{
		if (PButtonList[i]->text() == desiredButtn)
		{
			PButtonList[i]->setChecked(true);
			checkedButton = i;
			ui.stackedWidget->setCurrentIndex(i);
		}
	}
}

void QtAddToolGUI::slot_clicOK()
{
	isClose = true;
	emit dataToSetup(checkedButton + 1, 0);
	//this->close();
}

void QtAddToolGUI::slot_clicCanel()
{
	this->close();
}

void QtAddToolGUI::slot_dataFromDialog(bool answer)
{
	if (answer)
	{
		isClose = true;
		this->close();
	}
	else
	{
		delete dialog;
		dialog = nullptr;
		isClose = false;
	}
}

void QtAddToolGUI::slot_pushButtonClic()
{
	PButtonList[checkedButton]->setChecked(false);
	for (int i{ 0 }; i < PButtonList.size(); ++i)
	{
		if (PButtonList[i]->isChecked())
		{
			checkedButton = i;
			ui.stackedWidget->setCurrentIndex(i);
		}
	}
}
