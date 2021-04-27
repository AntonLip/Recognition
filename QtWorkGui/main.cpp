#include "QtWorkGui.h"
#include <QtWidgets/QApplication>
#include "simplLoger.h"

int main(int argc, char *argv[])
{
    LOG.logInit(argv[1]);
    LOG.logMessege("Program start", _INFO_);
    QApplication a(argc, argv);
    QtWorkGui* mainForm;
    try
    {
        mainForm = new QtWorkGui();
    }
    catch(...)
    {
        LOG.logMessege("mainForm create error",_ERROR_);
    }
    mainForm->show();
    return a.exec();
    /*try
    {
        delete mainForm;
    }
    catch (...)
    {
        LOG.logMessege("mainForm delete error", _ERROR_);
    }
    LOG.logMessege("Program end", _INFO_);*/
}
