#include "mysquare.h"


MySquare::MySquare()
{
    rec = boundingRect();
}

void MySquare::changeSizeFromButton(QPointF size)
{
    prepareGeometryChange();
    this->setPos(0,0);
    b_X = t_X + size.x();
    b_Y = t_Y + size.y();
    m_BottomRight = QPointF(b_X, b_Y);
    rec.setBottomRight(m_BottomRight);
    update();
}
//{

//void MySquare::st_ItemHeightChangeee(int height, int m_kH)
//{
//    //setFlag(ItemIsMovable, false);
//    prepareGeometryChange();
//    b_Y = t_Y + height/ m_kH;
//    m_BottomRight = QPointF(b_X, b_Y);
//    rec.setBottomRight(m_BottomRight);
//    update();
//}
//
//void MySquare::st_ItemWidthChangeee(int width, int m_kW)
//{
//    //setFlag(ItemIsMovable, false);
//    prepareGeometryChange();
//    b_X = t_X + width/ m_kW;
//    m_BottomRight = QPointF(b_X, b_Y);
//    rec.setBottomRight(m_BottomRight);
//    update();
//}
//
//void MySquare::st_SpinBoxChangeOffY(int value,int m_kH)
//{
//    if (this->cursor() != QCursor(Qt::ClosedHandCursor))
//        this->setY(value* m_kH);
//}
//
//
//void MySquare::st_SpinBoxChangeOffX(int value,int m_kW)
//{
//    if(this->cursor()!= QCursor(Qt::ClosedHandCursor))
//        this->setX(value* m_kW);
//}




QRectF MySquare::boundingRect() const
{
    return QRectF(m_TopLeft,m_BottomRight);
}


void MySquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::gray));
    painter->drawRect(rec);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}


void MySquare::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    
    
    //если ПЕРЕТАСКИВАЕМ
    if(this->cursor()==QCursor(Qt::ClosedHandCursor))
    {
        
        //изменяем ПОЛОЖЕНИЕ объекта
        this->setPos(mapToScene(event->pos() - m_shiftMouseCoords));

        //ОГРАНИЧЕНИЕ движения
        if(this->x()+rec.topLeft().x() < 0){       //1 -толщина линии границы квадрата в пикселях
            this->setX(-rec.topLeft().x());         /// слева
        }
        if(this->x() +(rec.bottomRight().x())  > scene()->sceneRect().width()){
            this->setX(scene()->sceneRect().width() - (abs(rec.bottomRight().x())));   /// справа
        }
        if(this->y()+(rec.topLeft().y()) < 0){
            this->setY(-rec.topLeft().y());         /// сверху
        }
        if(this->y() + (rec.bottomRight().y())  > scene()->sceneRect().height()){
            this->setY(scene()->sceneRect().height() - (abs(rec.bottomRight().y())) );   /// снизу
        }
        QPointF coordinate = QPointF(mapToScene(m_TopLeft));
        emit CoordinateChange(coordinate);

    }
    //если ИЗМЕНЯЕМ размер
    else
    {
        /*******     НАЖАТИЕ НА ГРАНИЦЕ    ********************************************************************************************************************************************************************************/
        if(this->cursor()==QCursor(Qt::SizeVerCursor)&&bottom==true) // НИЖНЯЯ граница
        {

            b_Y = event->pos().y();                //к-ты курсора в системе объекта,получается что к-ты равны нижней границе

            //ограничивает возможность вытягивания размеров РОИ за границу сцены
            if (mapToScene(m_BottomRight).y() > scene()->sceneRect().height())  //если к-та нижней границы выходит за пределы сцены, то не изменяем ее к-ту, т.е она остается на границе
            {
                b_Y = rec.bottomRight().y();
            }
            else    //иначе 
                m_BottomRight = QPointF(b_X, b_Y);      //присваиваем нижнму левому углу вычисленные к-ты

            prepareGeometryChange();             //подготовка к изменению размеров
            rec.setBottomRight(m_BottomRight);   //устанавливаем для фигуры новые к-ты нижнего правого угла


        }
        else if(this->cursor()==QCursor(Qt::SizeVerCursor)&&top==true) // ВЕРХНЯЯ граница
        {

           //setFlag(ItemIsMovable,false);

            if (mapToScene( event->pos()).y() < 0)
                event->setPos(QPointF(1, event->pos().y()));
            else
                t_Y = event->pos().y();


            if (mapToScene(m_TopLeft).y() < 0 )
            {
                t_Y = event->pos().y();
                m_TopLeft = QPointF(t_X, t_Y);

            }
            else    //иначе
            {
                 m_TopLeft=QPointF(t_X,t_Y);

            }

            prepareGeometryChange();
            rec.setTopLeft(m_TopLeft);

            QPointF coordinate = QPointF(mapToScene(m_TopLeft));
            emit CoordinateChange(coordinate);

        }
        else if(this->cursor()==QCursor(Qt::SizeHorCursor)&&right==true) // ПРАВАЯ граница
        {

            //setFlag(ItemIsMovable,false);

            if (event->pos().x() > scene()->sceneRect().width() - 1)
                event->setPos(QPointF(scene()->sceneRect().width() - 1,event->pos().y()));
            else
                b_X=event->pos().x();

            if (mapToScene(m_BottomRight).x() >scene()->sceneRect().width()-1)
            {
                b_X=rec.bottomRight().x()-1;
                m_BottomRight = QPointF(b_X, b_Y);
            }
            else    //иначе
            {
                 m_BottomRight=QPointF(b_X,b_Y);

            }
            prepareGeometryChange();
            rec.setBottomRight(m_BottomRight);

        }
        else if(this->cursor()==QCursor(Qt::SizeHorCursor)&&left==true) // ЛЕВАЯ граница
        {

           //setFlag(ItemIsMovable,false);
            t_X=event->pos().x();
            if (mapToScene(m_TopLeft).x() <= 0)
            {
                t_X=rec.topLeft().x();
            }
            else    //иначе
            {
                 m_TopLeft=QPointF(t_X,t_Y);

            }

            prepareGeometryChange();
            rec.setTopLeft(m_TopLeft);

            QPointF coordinate = QPointF(mapToScene(m_TopLeft));
            emit CoordinateChange(coordinate);

        }
        else if(this->cursor()==QCursor(Qt::SizeFDiagCursor)&&bottom==true&&right==true) // НИЖНИЙ ПРАВЫЙ угол
        {

            //setFlag(ItemIsMovable,false);
            b_X=event->pos().x();
            b_Y=event->pos().y();
            if (mapToScene(m_BottomRight).x() >=scene()->sceneRect().width()||mapToScene(m_BottomRight).y() >=scene()->sceneRect().height())
            {
                b_X=rec.bottomRight().x();
                b_Y=rec.bottomRight().y();
            }
            else    //иначе
            {
                 m_BottomRight=QPointF(b_X,b_Y);

            }

            prepareGeometryChange();
            rec.setBottomRight(m_BottomRight);

        }
        else if(this->cursor()==QCursor(Qt::SizeBDiagCursor)&&bottom==true&&left==true) // НИЖНИЙ ЛЕВЫЙ угол
        {

           // setFlag(ItemIsMovable,false);
            t_X=event->pos().x();
            b_Y=event->pos().y();
            if (mapToScene(m_TopLeft).x() <=0||mapToScene(m_BottomRight).y() >=scene()->sceneRect().height())
            {
                t_X=rec.topLeft().x();
                b_Y=rec.bottomRight().y();
            }
            else    //иначе
            {
                m_TopLeft=QPointF(t_X,t_Y);
                m_BottomRight=QPointF(b_X,b_Y);

            }

            prepareGeometryChange();
            rec.setBottomRight(m_BottomRight);
            rec.setTopLeft(m_TopLeft);

        }
        else if(this->cursor()==QCursor(Qt::SizeFDiagCursor)&&top==true&&left==true) // ВЕРХНИЙ ЛЕВЫЙ угол
        {

            //setFlag(ItemIsMovable,false);
            t_X=event->pos().x();
            t_Y=event->pos().y();
            if (mapToScene(m_TopLeft).x() <=0||mapToScene(m_TopLeft).y() <=0)
            {
                t_X=rec.topLeft().x();
                t_Y=rec.topLeft().y();
            }
            else    //иначе
            {
                m_TopLeft=QPointF(t_X,t_Y);

            }

            prepareGeometryChange();
            rec.setTopLeft(m_TopLeft);

        }
        else if(this->cursor()==QCursor(Qt::SizeBDiagCursor)&&top==true&&right==true) // ВЕРХНИЙ ПРАВЫЙ угол
        {

            //setFlag(ItemIsMovable,false);
            t_Y=event->pos().y();
            b_X=event->pos().x();
            if (mapToScene(m_BottomRight).x() >=scene()->sceneRect().width()||mapToScene(m_TopLeft).y() <=0)
            {
                t_Y=rec.topLeft().y();
                b_X=rec.bottomRight().x();
            }
            else    //иначе
            {
                m_TopLeft=QPointF(t_X,t_Y);
                m_BottomRight=QPointF(b_X,b_Y);

            }

            prepareGeometryChange();
            rec.setBottomRight(m_BottomRight);
            rec.setTopLeft(m_TopLeft);

        }
        /*******     нажатие на границе конец   ********************************************************************************************************************************************************************************/
        emit sizeChange(QPointF(m_BottomRight.x()-m_TopLeft.x(), m_BottomRight.y() - m_TopLeft.y()));
        
    }
    
}


void MySquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Press";
    m_Pressed=true;
    m_shiftMouseCoords = mapToScene(event->pos())-this->pos();

    this->setCursor(QCursor(Qt::ClosedHandCursor));

    /*******     НАЖАТИЕ НА ГРАНИЦЕ    ********************************************************************************************************************************************************************************/
    qreal adjust = 8; //отступ от границы
    if((event->pos().x() > boundingRect().left()  + adjust)&&(event->pos().x() < boundingRect().right() - adjust) &&(event->pos().y() < boundingRect().bottom()+ adjust) &&(event->pos().y() > boundingRect().bottom()- adjust))   //нажатие на нижней границе
    {
        bottom=true;
        this->setCursor(QCursor(Qt::SizeVerCursor));
        //Y=event->scenePos().y(); //запоминаем в каком мемте находилась мышь когда кликаем(начальное положение) для того, чтобы найти разницу между конечным и начальным положением и на нее увеличить высоту
        //qDebug()<< Y ;
    }
    if((event->pos().x() > boundingRect().left()  + adjust)&&(event->pos().x() < boundingRect().right() - adjust) &&(event->pos().y() < boundingRect().top()+ adjust) &&(event->pos().y() > boundingRect().top()- adjust))   //нажатие на верхней границе
    {
        top=true;
        this->setCursor(QCursor(Qt::SizeVerCursor));
        //Y=event->scenePos().y();
    }
    if((event->pos().x() > boundingRect().right() - adjust) && (event->pos().x() < boundingRect().right() + adjust) && (event->pos().y() < boundingRect().bottom() - adjust) && (event->pos().y() > boundingRect().top() + adjust))
    {
        right=true;
        this->setCursor(QCursor(Qt::SizeHorCursor));
        //X=event->scenePos().x();
    }
    if((event->pos().x() > boundingRect().left() - adjust) && (event->pos().x() < boundingRect().left() + adjust) && (event->pos().y() < boundingRect().bottom() - adjust) && (event->pos().y() > boundingRect().top() + adjust))
    {
        left=true;
        this->setCursor(QCursor(Qt::SizeHorCursor));
        //X=event->scenePos().x();
    }
    if((event->pos().x() > boundingRect().right() - adjust) && (event->pos().x() < boundingRect().right() + adjust) && (event->pos().y() < boundingRect().bottom() + adjust) && (event->pos().y() > boundingRect().bottom() - adjust))
    {
        bottom=true; right=true;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
        //X=event->scenePos().x();
        //Y=event->scenePos().y();
    }
    if((event->pos().x() > boundingRect().left() - adjust) && (event->pos().x() < boundingRect().left() + adjust) && (event->pos().y() < boundingRect().bottom() + adjust) && (event->pos().y() > boundingRect().bottom() - adjust))
    {
        bottom=true; left=true;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
        //X=event->scenePos().x();
        //Y=event->scenePos().y();
    }
    if((event->pos().x() > boundingRect().left() - adjust) && (event->pos().x() < boundingRect().left() + adjust) && (event->pos().y() > boundingRect().top() - adjust) && (event->pos().y() < boundingRect().top() + adjust))
    {
        top=true; left=true;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
        //X=event->scenePos().x();
        //Y=event->scenePos().y();
    }
    if((event->pos().x() < boundingRect().right() + adjust) && (event->pos().x() > boundingRect().right() - adjust) && (event->pos().y() < boundingRect().top() + adjust) && (event->pos().y() > boundingRect().top() - adjust))
    {
        top=true; right=true;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
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


