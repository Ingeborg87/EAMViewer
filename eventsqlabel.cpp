#include "eventsqlabel.h"

EventsQLabel::EventsQLabel(QWidget *parent):QLabel(parent )
{    
}

void EventsQLabel::mouseDoubleClickEvent(QMouseEvent*)
{
    emit mouseDoubleClicked();
}
