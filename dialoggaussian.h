#ifndef DIALOGGAUSSIAN_H
#define DIALOGGAUSSIAN_H

#include <QDialog>
#include <QKeyEvent>
#include <iostream>

using namespace std;

namespace Ui {
class DialogGaussian;
}

class DialogGaussian : public QDialog
{
    Q_OBJECT
public:
    explicit DialogGaussian(QWidget *parent = 0);
    ~DialogGaussian();
    float sliderValueSigmaX;
    float sliderValueSigmaY;
    int sliderValueSizeX;
    int sliderValueSizeY;
    int cbxIndex;
    int X,Y;
    void showSlot();
private:
    Ui::DialogGaussian *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void sizeXChanged(int i);
    void sizeYChanged(int i);
    void sigmaXChanged(int i);
    void sigmaYChanged(int i);
    void cbxIndexChanged(int i);
signals:
    void signalSizeXChanged();
    void signalSizeYChanged();
    void signalSigmaXChanged();
    void signalSigmaYChanged();
    void signalCbxIndexChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGGAUSSIAN_H
