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

signals:
    void CoordItemChange(QRectF& itemCoord);
    void ItemFromWidgetSizeChange(QSizeF& itemSize);
    void sl_changeSizeFromButton(QSizeF size);
    void signal_new_offsetX(int newOffsetX);
    void signal_new_offsetY(int newOffsetY);
    void signal_new_heigth(int newHeigth);
    void signal_new_width(int newWidth);
    void signal_newSizeScene(QSizeF newSize);
};
#endif // WIDGET_H
