#ifndef DIALOGCANNY_H
#define DIALOGCANNY_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogCanny;
}

class DialogCanny : public QDialog
{
    Q_OBJECT
public:
    explicit DialogCanny(QWidget *parent = 0);
    ~DialogCanny();
    int threshold1;
    int threshold2;
    int sobelSize;
    bool L2;
    
private:
    Ui::DialogCanny *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void threshold1Changed(int i);
    void threshold2Changed(int i);
    void sobelSizeChanged(int i);
    void L2Changed(bool b);
signals:
    void signalThreshold1Changed();
    void signalThreshold2Changed();
    void signalSobelSizeChanged();
    void signalL2Changed();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGCANNY_H
