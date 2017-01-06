#ifndef DIALOGMEDIANBLUR_H
#define DIALOGMEDIANBLUR_H

#include <QDialog>
#include <QKeyEvent>
#include <iostream>

namespace Ui {
class DialogMedianBlur;
}

class DialogMedianBlur : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMedianBlur(QWidget *parent = 0);
    ~DialogMedianBlur();
    int sliderValueMedianSize;
    int K;
    void showSlot();
private:
    Ui::DialogMedianBlur *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void medianSizeChanged(int i);
signals:
    void signalMedianSizeChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGMEDIANBLUR_H
