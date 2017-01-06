#ifndef DIALOGSOBEL_H
#define DIALOGSOBEL_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogSobel;
}

class DialogSobel : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogSobel(QWidget *parent = 0);
    ~DialogSobel();
    int spinValueDx;
    int spinValueDy;
    int spinValueSize;
    double spinValueScale;
    double spinValueDelta;
    int cbxIndex;
private:
    Ui::DialogSobel *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void dxChanged(int i);
    void dyChanged(int i);
    void sizeChanged(int i);
    void scaleChanged(double d);
    void deltaChanged(double d);
    void cbxIndexChanged(int i);
signals:
    void signalDxChanged();
    void signalDyChanged();
    void signalSizeChanged();
    void signalScaleChanged();
    void signalDeltaChanged();
    void signalCbxIndexChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGSOBEL_H
