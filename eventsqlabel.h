#ifndef EVENTSQLABEL_H
#define EVENTSQLABEL_H
#include <QLabel>
#include <QMouseEvent>

class EventsQLabel:public QLabel
{
    Q_OBJECT
public:
    EventsQLabel(QWidget *parent = 0);
private:
    void mouseDoubleClickEvent(QMouseEvent*);
signals:
    void mouseDoubleClicked();
};

#endif // EventsQLabel_H
