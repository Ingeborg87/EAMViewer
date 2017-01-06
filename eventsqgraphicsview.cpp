#include "eventsqgraphicsview.h"

EventsQGraphicsView::EventsQGraphicsView(QWidget *parent):QGraphicsView(parent)
{
    flag = true;
    zoomfactor = 1;
    zoomflag = false;
    ROIFlag = false;
}


void EventsQGraphicsView::mouseDoubleClickEvent(QMouseEvent*)
{
    emit mouseDoubleClicked();
}


void EventsQGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Plus)
    {
        flag = true;
        if(zoomflag < 9)
        {
            zoomflag++;
            if(zoomflag <= 3)
                zoomfactor = float(10 + zoomflag)/10.0;
            else if (zoomflag > 4)
                zoomfactor = float(zoomflag )/3;
            emit keyPressed();
        }
    }
    else if(event->key()==Qt::Key_Minus)
    {
        flag = false;
        if(zoomflag > -9)
        {
            zoomflag--;
            if(zoomflag <= 3)
                zoomfactor = float(10 + zoomflag)/10.0;
            else if (zoomflag > 4)
                zoomfactor = float(zoomflag)/3 ;
            emit keyPressed();
        }
    }
}
