#ifndef DIALOGSCHARR_H
#define DIALOGSCHARR_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogScharr;
}

class DialogScharr : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogScharr(QWidget *parent = 0);
    ~DialogScharr();
    int dx;
    int dy;
    double scale;
    double delta;
    int borderType;

private:
    Ui::DialogScharr *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void dxChanged(int i);
    void dyChanged(int i);
    void scaleChanged(int i);
    void deltaChanged(int i);
    void borderTypeChanged(int i);
signals:
    void signalDxChanged();
    void signalDyChanged();
    void signalScaleChanged();
    void signalDeltaChanged();
    void signalBorderTypeChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGSCHARR_H
