#ifndef DIALOGBLUR_H
#define DIALOGBLUR_H

#include <QDialog>
#include <QKeyEvent>

using namespace std;
namespace Ui {
class DialogBlur;
}

class DialogBlur : public QDialog
{
    Q_OBJECT    
public:
    explicit DialogBlur(QWidget *parent = 0);
    ~DialogBlur();
    int sliderValueSizeX;
    int sliderValueSizeY;
    int cbxIndex;
    int sliderValueAnchorX;
    int sliderValueAnchorY;
    int X,Y;
    void showSlot();
private:
    Ui::DialogBlur *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void sizeXChanged(int i);
    void sizeYChanged(int i);
    void anchorXChanged(int i);
    void anchorYChanged(int i);
    void cbxIndexChanged(int i);
signals:
    void signalSizeXChanged();
    void signalSizeYChanged();
    void signalAnchorXChanged();
    void signalAnchorYChanged();
    void signalCbxIndexChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGBLUR_H
