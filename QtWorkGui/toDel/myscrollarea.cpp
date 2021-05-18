#include "myscrollarea.h"
#include <QtDebug>

//void MyScrollArea::wheelEvent(QWheelEvent* event)
//{
//
//    QPoint numPixels = event->pixelDelta();
//    QPoint numDegrees = event->angleDelta() / 8;
//
//
//    if (!numDegrees.isNull())
//    {
//        QPoint numSteps = numDegrees / 15;
//        if (numSteps.y() < 0)
//            scaledImages(0.8);
//        else {
//            scaledImages(1.25);
//        }
//
//    }
//
//    event->accept();
//
//}



MyScrollArea::MyScrollArea(QWidget *parent):QScrollArea(parent)
{

    f_X=0;
    old_deltaX=0;
    f_Y=0;
    old_deltaY=0;
}

void MyScrollArea::mousePressEvent(QMouseEvent *e)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    f_X=e->pos().x();
    f_Y=e->pos().y();
}

void MyScrollArea::mouseMoveEvent(QMouseEvent *e)
{

     deltaX=f_X-e->pos().x();
     deltaY=f_Y-e->pos().y();

     if(deltaX<0||dX>deltaX)
     {
         if(old_deltaX<this->horizontalScrollBar()->minimum())//уперлась ВЛЕВО
             old_deltaX=this->horizontalScrollBar()->minimum();

         else if (old_deltaX>this->horizontalScrollBar()->maximum())//уперлась ВПРАВО
             old_deltaX=this->horizontalScrollBar()->maximum();

         else
         {
             old_deltaX-=this->horizontalScrollBar()->maximum()*0.005;
              this->horizontalScrollBar()->setValue(old_deltaX);
         }
     }
     else
     {
         old_deltaX+=this->horizontalScrollBar()->maximum()* 0.005;
         this->horizontalScrollBar()->setValue(old_deltaX);
     }



     if(deltaY<0||dY>deltaY)
     {
         int x=this->verticalScrollBar()->minimum();
         x=x;

         if(old_deltaY<this->verticalScrollBar()->minimum())//уперлась ВВЕРХ
            old_deltaY=this->verticalScrollBar()->minimum();

         else if (old_deltaY>this->verticalScrollBar()->maximum())//уперлась ВНИЗ
             old_deltaY=this->verticalScrollBar()->maximum();
         else
         {
             old_deltaY-=this->verticalScrollBar()->maximum()* 0.005;
             this->verticalScrollBar()->setValue(old_deltaY);
         }
     }
     else
     {
         old_deltaY+=this->verticalScrollBar()->maximum()* 0.005;
         this->verticalScrollBar()->setValue(old_deltaY);
     }


     dX=deltaX;
     dY=deltaY;

}


void MyScrollArea::mouseReleaseEvent(QMouseEvent *e)
{
     this->setCursor(QCursor(Qt::ArrowCursor));
    deltaX=0;
    deltaY=0;
}


