#include "mysquare.h"


void MySquare::changeX(QPointF newPos)
{
    rec.setTopLeft(QPointF(m_shiftMouseCoords.x(), rec.y()));
    m_shiftMouseCoords.setX(newPos.x());
    if (rec.x() < 0)  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
    {
        rec.setTopLeft(QPointF(0, rec.y()));
        m_shiftMouseCoords.setX(0);
    }
    else if (rec.width() <= 0)
    {
        rec.setTopLeft(QPointF(rec.bottomRight().x() - 1, rec.y()));
        m_shiftMouseCoords.setX(rec.x());
    }
}

void MySquare::changeY(QPointF newPos)
{
    rec.setTopLeft(QPointF(rec.x(), m_shiftMouseCoords.y()));
    m_shiftMouseCoords.setY(newPos.y());
    if (rec.y() < 0)  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
    {
        rec.setTopLeft(QPointF(rec.x(), 0));
        m_shiftMouseCoords.setY(0);
    }
    else if (rec.height() <= 0)
    {
        rec.setTopLeft(QPointF(rec.x(), rec.bottomRight().y() - 1));
        m_shiftMouseCoords.setY(rec.y());
    }
}

void MySquare::changeWidth(QPointF newPos)
{
    rec.setWidth(rec.width() + newPos.x() - m_shiftMouseCoords.x());
    m_shiftMouseCoords.setX(newPos.x());
    //ограничивает возможность вытягивания размеров РОИ за границу сцены
    if (rec.x() + rec.width() + 1 > boundingRect().width())  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
    {
        rec.setWidth(boundingRect().width() - rec.x());
        m_shiftMouseCoords.setX(boundingRect().width());
    }
    else if (rec.width() <= 0)
    {
        rec.setWidth(1);
        m_shiftMouseCoords.setX(rec.x());
    }
}

void MySquare::changeHeigth(QPointF newPos)
{
    rec.setHeight(rec.height() + newPos.y() - m_shiftMouseCoords.y());
    m_shiftMouseCoords.setY(newPos.y());
    //ограничивает возможность вытягивания размеров РОИ за границу сцены
    if (rec.y() + rec.height() + 1 > boundingRect().height())  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
    {
        rec.setHeight(boundingRect().height() - rec.y());
        m_shiftMouseCoords.setY(boundingRect().height());
    }
    else if (rec.height() <= 0)
    {
        rec.setHeight(1);
        m_shiftMouseCoords.setY(rec.y());
    }
}

void MySquare::changeOffX(int newX)
{
    QSizeF buferSize{ rec.size() };
    rec.setTopLeft(QPointF(newX, rec.y()));
    rec.setSize(buferSize);
    if (rec.x() < 0)  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
    {
        rec.setTopLeft(QPointF(0, rec.y()));
    }
    else if (rec.width() <= 0)
    {
        rec.setTopLeft(QPointF(rec.bottomRight().x() - 1, rec.y()));
    }
}

void MySquare::changeOffY(int newY)
{
    QSizeF buferSize{ rec.size() };
    rec.setTopLeft(QPointF(rec.x(), newY));
    rec.setSize(buferSize);
    if (rec.y() < 0)  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
    {
        rec.setTopLeft(QPointF(rec.x(), 0));
    }
    else if (rec.height() <= 0)
    {
        rec.setTopLeft(QPointF(rec.x(), rec.bottomRight().y() - 1));
    }
}

void MySquare::changeWidth(int newW)
{
    rec.setWidth(newW);
    //ограничивает возможность вытягивания размеров РОИ за границу сцены
    if (rec.x() + rec.width() + 1 > boundingRect().width())  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
    {
        rec.setWidth(boundingRect().width() - rec.x());
    }
    else if (rec.width() <= 0)
    {
        rec.setWidth(1);
    }
}

void MySquare::changeHeigth(int newH)
{
    rec.setHeight(newH);
    //ограничивает возможность вытягивания размеров РОИ за границу сцены
    if (rec.y() + rec.height() + 1 > boundingRect().height())  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
    {
        rec.setHeight(boundingRect().height() - rec.y());
    }
    else if (rec.height() <= 0)
    {
        rec.setHeight(1);
    }
}

MySquare::MySquare()
{
    rec = boundingRect();
}

void MySquare::changeSizeFromButton(QSizeF size)
{
    prepareGeometryChange();
    rec.setTopLeft(QPointF(0, 0));
    rec.setSize(size);
    //this->setPos(mapToItem(this, 0,0));
    //t_X = 0;
    //t_Y = 0;
    //m_TopLeft = QPointF(t_X, t_Y);
    //b_X = t_X + size.width();
    //b_Y = t_Y + size.height();
    //m_BottomRight = QPointF(b_X, b_Y);
    //rec.setTopLeft(m_TopLeft);
    //rec.setBottomRight(m_BottomRight);
    update();
}

void MySquare::slot_changeOffX(int value)
{
    //this->setX(value);
    /*this->setX(mapToItem(this,QPointF(value, 0)).x());
    if (this->x() + (rec.bottomRight().x()) > scene()->sceneRect().width() + 1)
    {
        this->setX(scene()->sceneRect().width() - (abs(rec.bottomRight().x())));   /// справа
    }*/
    changeOffX(value);
    update();
}

void MySquare::slot_changeOffY(int value)
{
    //this->setY(value);
    /*this->setY(mapToItem(this, QPointF(0, value)).y());
    if (this->y() + (rec.bottomRight().y()) > scene()->sceneRect().height() + 1)
    {
        this->setY(scene()->sceneRect().height() - (abs(rec.bottomRight().y())));   /// снизу
    }*/
    changeOffY(value);
    update();
}

void MySquare::slot_changeHeight(int value)
{
    //prepareGeometryChange();
    ////update(QRectF(x(), y(), value, value));
    //b_Y = t_Y + mapToItem(this, QPointF(0, value)).y();
    //if (b_Y > scene()->sceneRect().height())  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
    //{
    //    b_Y = rec.bottomRight().y();
    //    m_BottomRight = QPointF(b_X, b_Y);
    //}
    //else    //иначе 
    //    m_BottomRight = QPointF(b_X, b_Y);
    //rec.setBottomRight(m_BottomRight);
    //if (this->y() + (rec.topLeft().y()) < 0) 
    //{
    //    this->setY(-rec.topLeft().y());         /// сверху
    //}
    changeHeigth(value);
    update();
}

void MySquare::slot_changeWidth(int value)
{
    //prepareGeometryChange();
    //b_X = t_X + mapToItem(this, QPointF(value, 0)).x();
    //if (b_X > scene()->sceneRect().width() )
    //{
    //    b_X = rec.bottomRight().x() - 1;
    //    m_BottomRight = QPointF(b_X, b_Y);
    //}
    //else    //иначе
    //{
    //    m_BottomRight = QPointF(b_X, b_Y);

    //}
    //rec.setBottomRight(m_BottomRight);
    //if (this->x() + rec.topLeft().x() < 0) 
    //{       
    //    this->setX(-rec.topLeft().x());         /// слева
    //}
    changeWidth(value);
    update();
}

void MySquare::slot_updateSceneSize(QSizeF newSize)
{
    scenaRect.setSize(newSize);
}


QRectF MySquare::boundingRect() const
{
    return scenaRect;
}


void MySquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::gray));
    painter->drawRect(QRectF(rec));
    qreal qw{ this->x() };
    QRectF qwe{ this->boundingRect() };
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF MySquare::getDrawRect()
{
    return rec;
}


void MySquare::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{ 
    //если ПЕРЕТАСКИВАЕМ
    prepareGeometryChange();
    if(this->cursor()==QCursor(Qt::ClosedHandCursor))
    { 
        //изменяем ПОЛОЖЕНИЕ объекта
        //this->setPos((event->pos() - m_shiftMouseCoords));

        QSizeF buferSize{ rec.size() };
        rec.setTopLeft((mapToScene(event->pos()) - m_shiftMouseCoords + rec.topLeft()));
        m_shiftMouseCoords = event->pos();
        rec.setSize(buferSize);

        //ОГРАНИЧЕНИЕ движения
        //1 -толщина линии границы квадрата в пикселях
        if(rec.topLeft().x() < 0)   //left          
        {   
            rec.setX(0);
            m_shiftMouseCoords.setX(rec.width() / 2);
        }
        if(rec.x()+rec.width()+1  > boundingRect().width()) ///rigth
        {
            rec.setX(boundingRect().width() - buferSize.width()-1);
            m_shiftMouseCoords.setX(rec.width() / 2 + rec.x());
        }
        if(rec.topLeft().y() < 0)///top
        {
            rec.setY(0);
            m_shiftMouseCoords.setY(rec.height() / 2);       
        }
        if(rec.y() + rec.height() + 1 > boundingRect().height())//down
        {
            rec.setY(boundingRect().height() - buferSize.height() - 1);
            m_shiftMouseCoords.setY(rec.height() / 2 + rec.y());   
        }
        rec.setSize(buferSize);
        emit CoordinateChange(QRectF(rec));
        update();
    }
    //если ИЗМЕНЯЕМ размер
    else
    {
        /*******     НАЖАТИЕ НА ГРАНИЦЕ    ********************************************************************************************************************************************************************************/
        if(this->cursor()==QCursor(Qt::SizeVerCursor)&&bottom==true) // НИЖНЯЯ граница
        {
            changeHeigth(event->pos());
            emit CoordinateChange(rec);
        }
        else if(this->cursor()==QCursor(Qt::SizeVerCursor)&&top==true) // ВЕРХНЯЯ граница
        {
            changeY(event->pos());
            emit CoordinateChange(rec);
            
        }
        else if(this->cursor()==QCursor(Qt::SizeHorCursor)&&right==true) // ПРАВАЯ граница
        {
            changeWidth(event->pos());
            emit CoordinateChange(rec);
        }
        else if(this->cursor()==QCursor(Qt::SizeHorCursor)&&left==true) // ЛЕВАЯ граница
        {
            changeX(event->pos());
            emit CoordinateChange(rec);
        }
        else if(this->cursor()==QCursor(Qt::SizeFDiagCursor)&&bottom==true&&right==true) // НИЖНИЙ ПРАВЫЙ угол
        {
            changeHeigth(event->pos());
            changeWidth(event->pos());
            emit CoordinateChange(rec);
        }
        else if(this->cursor()==QCursor(Qt::SizeBDiagCursor)&&bottom==true&&left==true) // НИЖНИЙ ЛЕВЫЙ угол
        {
            changeX(event->pos());
            changeHeigth(event->pos());
            emit CoordinateChange(rec);
        }
        else if(this->cursor()==QCursor(Qt::SizeFDiagCursor)&&top==true&&left==true) // ВЕРХНИЙ ЛЕВЫЙ угол
        {
            changeX(event->pos());
            changeY(event->pos());
            emit CoordinateChange(rec);
        }
        else if(this->cursor()==QCursor(Qt::SizeBDiagCursor)&&top==true&&right==true) // ВЕРХНИЙ ПРАВЫЙ угол
        {
            changeY(event->pos());
            changeWidth(event->pos());
            emit CoordinateChange(mapRectToScene(this->boundingRect()));
        }
        /*******     нажатие на границе конец   ********************************************************************************************************************************************************************************/
    }
}


void MySquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "Press";
    m_Pressed=true;
    m_shiftMouseCoords = mapToScene(event->pos());
    //if(rec.contains(event->pos()))
    //    this->setCursor(QCursor(Qt::ClosedHandCursor));

    /*******     НАЖАТИЕ НА ГРАНИЦЕ    ********************************************************************************************************************************************************************************/
    qreal adjust = 5; //отступ от границы
    if(QRectF(rec.x() + adjust, rec.y() + rec.height() - adjust, rec.width() - 2 * adjust, adjust).contains(event->pos()))   //нажатие на нижней границе
    {
        bottom=true;
        //this->setCursor(QCursor(Qt::SizeVerCursor));
        //Y=event->scenePos().y(); //запоминаем в каком мемте находилась мышь когда кликаем(начальное положение) для того, чтобы найти разницу между конечным и начальным положением и на нее увеличить высоту
        //qDebug()<< Y ;
    }
    if(QRectF(rec.x() + adjust, rec.y(), rec.width() - 2 * adjust, adjust).contains(event->pos()))   //нажатие на верхней границе
    {
        top=true;
        //this->setCursor(QCursor(Qt::SizeVerCursor));
        //Y=event->scenePos().y();
    }
    if(QRectF(rec.x() + rec.width() - adjust, rec.y() + adjust, adjust, rec.height() - 2 * adjust).contains(event->pos()))
    {
        right=true;
        //this->setCursor(QCursor(Qt::SizeHorCursor));
        //X=event->scenePos().x();
    }
    if(QRectF(rec.x(), rec.y() + adjust, adjust, rec.height() - 2 * adjust).contains(event->pos()))
    {
        left=true;
        //this->setCursor(QCursor(Qt::SizeHorCursor));
        //X=event->scenePos().x();
    }
    if(QRectF(rec.x() + rec.width() - adjust, rec.y() + rec.height() - adjust, adjust, adjust).contains(event->pos()))
    {
        bottom=true; right=true;
        //this->setCursor(QCursor(Qt::SizeFDiagCursor));
        //X=event->scenePos().x();
        //Y=event->scenePos().y();
    }
    if(QRectF(rec.x(), rec.y() + rec.height() - adjust, adjust, adjust).contains(event->pos()))
    {
        bottom=true; left=true;
        //this->setCursor(QCursor(Qt::SizeBDiagCursor));
        //X=event->scenePos().x();
        //Y=event->scenePos().y();
    }
    if(QRectF(rec.x(), rec.y(), adjust, adjust).contains(event->pos()))
    {
        top=true; left=true;
        //this->setCursor(QCursor(Qt::SizeFDiagCursor));
        //X=event->scenePos().x();
        //Y=event->scenePos().y();
    }
    if(QRectF(rec.x() + rec.width() - adjust, rec.y(), adjust, adjust).contains(event->pos()))
    {
        top=true; right=true;
        //this->setCursor(QCursor(Qt::SizeBDiagCursor));
        //X=event->scenePos().x();
        //Y=event->scenePos().y();
    }
    /*******     нажатие на границе конец   ********************************************************************************************************************************************************************************/

    Q_UNUSED(event);
}


void MySquare::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_Pressed=false;
    this->setCursor(QCursor(Qt::ArrowCursor));

    top=false;
    bottom=false;
    left=false;
    right=false;

    Q_UNUSED(event);
}


