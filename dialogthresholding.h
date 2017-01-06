#ifndef DIALOGTHRESHOLDING_H
#define DIALOGTHRESHOLDING_H

#include <QDialog>
#include <QKeyEvent>
#include <iostream>

namespace Ui {
class DialogThresholding;
}

class DialogThresholding : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogThresholding(QWidget *parent = 0);
    ~DialogThresholding();
    int sliderValueThreshold;
    int sliderValueMaximum;
    int comboIndex;
    bool chbxState;
private:
    Ui::DialogThresholding *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void sliderThreshChanged();
    void sliderMaxChanged();
    void checkStateChanged(int i);
    void comboIndexChanged(int i);
signals:
    void signalThreshChanged();
    void signalMaxChanged();
    void signalCheckStateChanged();
    void signalComboIndexChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGTHRESHOLDING_H
