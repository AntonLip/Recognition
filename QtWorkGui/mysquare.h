#ifndef MYSQUARE_H
#define MYSQUARE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <cmath>
#include "ui_widget.h"

class MySquare : public QObject, public QGraphicsItem
{
  Q_OBJECT
private:

    int b_X = 64, b_Y = 64, t_X = 0, t_Y = 0;
        //X,Y;
    bool top=false, bottom=false, left=false, right=false;
    QPointF m_shiftMouseCoords;                 //Координаты сдвига позиции курсора относительно координаты (0, 0) в координатной системе MoveItem.

    QRectF rec;                                 //фигура прямоугольник
    QPointF m_TopLeft=QPointF(t_X,t_Y);         //к-ты верхнего левого угла
    QPointF m_BottomRight=QPointF(b_X,b_Y);     //к-ты нижнего правого угла


public:

    Ui::Widget *ui;
    MySquare();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    bool m_Pressed=false;

public slots:
    void changeSizeFromButton(QPointF size);
    /*void st_SpinBoxChangeOffX(int value,int m_kW);
    void st_SpinBoxChangeOffY(int value,int m_kH);
    void st_ItemHeightChangeee(int value, int m_kH);
    void st_ItemWidthChangeee(int value, int m_kW);*/

signals:
    void CoordinateChange(QPointF &point); 
    void sizeChange(QPointF& itemSize);


protected:

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // MYSQUARE_H
