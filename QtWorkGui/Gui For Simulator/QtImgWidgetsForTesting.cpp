#include "QtImgWidgetsForTesting.h"

QtImgWidgetsForTesting::QtImgWidgetsForTesting(QWidget* parent)
	: QtImgWidgets(parent)
{
	ui.setupUi(this);
	//ui.horizontalLayout->addWidget(QtImgWidgets::ui.label_nameImg);
	QtImgWidgets::ui.horizontalLayout->addWidget(ui.label_result);
	QtImgWidgets::ui.horizontalLayout->setStretch(0, 1);
	QtImgWidgets::ui.horizontalLayout->setStretch(1, 1);
}

QtImgWidgetsForTesting::~QtImgWidgetsForTesting()
{
}
