#ifndef MYSCROLLAREA_H
#define MYSCROLLAREA_H

#include <QScrollArea>
#include <QObject>
#include <QWidget>
#include <QCursor>
#include <QMouseEvent>
#include <QScrollBar>
#include <qlabel.h>



class MyScrollArea : public QScrollArea
{
    Q_OBJECT
private:
    int f_X,f_Y,old_deltaX, deltaX,dX=0,old_deltaY, deltaY,dY=0;
public:
    MyScrollArea(QWidget *parent = nullptr) ;


protected:

    //void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

};

#endif // MYSCROLLAREA_H
