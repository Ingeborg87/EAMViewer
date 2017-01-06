#ifndef EVENTSQGRAPHICSVIEW_H
#define EVENTSQGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>

class EventsQGraphicsView:public QGraphicsView
{
    Q_OBJECT
public:
    EventsQGraphicsView(QWidget *parent = 0);
    bool flag;
    bool ROIFlag;
    int zoomflag;
    float zoomfactor;
private:
    void mouseDoubleClickEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent *event);
signals:
    void mouseDoubleClicked();
    void keyPressed();
};
#endif // EventsQGraphicsView_H
