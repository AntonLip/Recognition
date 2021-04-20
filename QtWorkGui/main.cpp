#include "QtWorkGui.h"
#include <QtWidgets/QApplication>
#include "simplLoger.h"
int main(int argc, char *argv[])
{
    simplLoger LOG;
    LOG.logInit(argv[1]);
    LOG.logMessege("Program start", _INFO_);
    QApplication a(argc, argv);
    QtWorkGui w;
    w.show();
    return a.exec();
    LOG.logMessege("Program end", _INFO_);
}
