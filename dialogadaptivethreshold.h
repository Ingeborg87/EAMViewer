#ifndef DIALOGADAPTIVETHRESHOLD_H
#define DIALOGADAPTIVETHRESHOLD_H

#include <QDialog>
#include <QKeyEvent>
#include <iostream>

namespace Ui {
class DialogAdaptiveThreshold;
}

class DialogAdaptiveThreshold : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAdaptiveThreshold(QWidget *parent = 0);
    ~DialogAdaptiveThreshold();
    int sliderValueMaximum;
    int sliderValueBlocksize;
    int sliderValueC;
    int comboboxIndexMethod;
    int comboboxIndexType;
private:
    Ui::DialogAdaptiveThreshold *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void sliderMaxChanged(int i);
    void sliderBlSizeChanged(int i);
    void sliderCChanged(int i);
    void comboboxIndexMethodChanged(int i);
    void comboboxIndexTypeChanged(int i);
signals:
    void signalMaximumChanged();
    void signalBlSizeChanged();
    void signalCChanged();
    void signalIndexMethodChanged();
    void signalIndexTypeChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGADAPTIVETHRESHOLD_H
