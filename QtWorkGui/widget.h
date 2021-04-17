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

public slots:
    void st_CoordItemChange(QPointF& itemCoord);
    void st_ItemFromWidgetSizeChange(QPointF& itemSize);

    void st_buttonChangeSizeClicked(double changeKoefficient);
    
   /* void st_ItemHeightChange(int height, int m_kH);
    void st_ItemWidthChange(int width, int m_kW);
    void st_SpinBoxChangeOff_Y(int offsetY, int m_kH);
    void st_SpinBoxChangeOff_X(int offsetX, int m_kW);*/


signals:
    void CoordItemChange(QPointF& itemCoord);
    void ItemFromWidgetSizeChange(QPointF& itemSize);
    void sl_changeSizeFromButton(QPointF size);
    
   /* void ItemHeightChange(int height,int m_kH);
    void ItemWidthChange(int width, int m_kW);
    void SpinBoxChangeOff_Y(int width, int m_kH);
    void SpinBoxChangeOff_X(int width, int m_kW);*/


};
#endif // WIDGET_H
