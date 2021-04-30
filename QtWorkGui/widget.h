#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mysquare.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include <iostream>
#include <QDebug>



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setSceneBackground(QPixmap &pixmap);


private:
    Ui::Widget *ui;
    MySquare *myitem;
    QGraphicsScene *scene;


protected:
  bool eventFilter(QObject *, QEvent *event);


private slots:
    void resizeEvent(QResizeEvent *event);
    void slot_setNewOffsetX(int newOffsetX);
    void slot_setNewOffsetY(int newOffsetY);
    void slot_setNewHeigth(int newHeigth);
    void slot_setNewWidth(int newWidth);
public slots:
    void st_CoordItemChange(QRectF& itemCoord);
    void st_ItemFromWidgetSizeChange(QSizeF& itemSize);

    void st_buttonChangeSizeClicked(double changeKoefficient);
    
   /* void st_ItemHeightChange(int height, int m_kH);
    void st_ItemWidthChange(int width, int m_kW);
    void st_SpinBoxChangeOff_Y(int offsetY, int m_kH);
    void st_SpinBoxChangeOff_X(int offsetX, int m_kW);*/


signals:
    void CoordItemChange(QRectF& itemCoord);
    void ItemFromWidgetSizeChange(QSizeF& itemSize);
    void sl_changeSizeFromButton(QSizeF size);
    void signal_new_offsetX(int newOffsetX);
    void signal_new_offsetY(int newOffsetY);
    void signal_new_heigth(int newHeigth);
    void signal_new_width(int newWidth);
   /* void ItemHeightChange(int height,int m_kH);
    void ItemWidthChange(int width, int m_kW);
    void SpinBoxChangeOff_Y(int width, int m_kH);
    void SpinBoxChangeOff_X(int width, int m_kW);*/


};
#endif // WIDGET_H
