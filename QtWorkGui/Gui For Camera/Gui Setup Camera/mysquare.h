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

    bool top=false, bottom=false, left=false, right=false;
    QPointF m_shiftMouseCoords;                 //Координаты сдвига позиции курсора относительно координаты (0, 0) в координатной системе MoveItem.

    QRectF rec;                                 //фигура прямоугольник
    QRectF scenaRect;
    void changeX(QPointF newPos);
    void changeY(QPointF newPos);
    void changeWidth(QPointF newPos);
    void changeHeigth(QPointF newPos);
    void changeOffX(int newX);
    void changeOffY(int newY);
    void changeWidth(int newW);
    void changeHeigth(int newH);
public:

    Ui::Widget *ui;
    MySquare();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    bool m_Pressed=false;
    QRectF getDrawRect();
public slots:
    void changeSizeFromButton(QSizeF size);
    void slot_changeOffX(int value);
    void slot_changeOffY(int value);
    void slot_changeHeight(int value);
    void slot_changeWidth(int value);
    void slot_updateSceneSize(QSizeF newSize);
signals:
    void CoordinateChange(QRectF &rect); 
    void sizeChange(QSizeF& itemSize);


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // MYSQUARE_H
