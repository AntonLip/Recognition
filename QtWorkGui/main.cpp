#include "QtWorkGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWorkGui w;
    w.show();
    return a.exec();
}
