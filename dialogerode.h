
#ifndef DIALOGERODE_H
#define DIALOGERODE_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogErode;
}

class DialogErode : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogErode(QWidget *parent = 0);
    ~DialogErode();
    int anchorX;
    int anchorY;
    int sizeX;
    int sizeY;
    int iterations;
    int shape;
    int border;
private:
    Ui::DialogErode *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void sizeXChanged(int i);
    void sizeYChanged(int i);
    void anchorXChanged(int i);
    void anchorYChanged(int i);
    void borderChanged(int i);
    void shapeIndexChanged(int i);
    void iterationsChanged(int i);
signals:
    void signalSizeXChanged();
    void signalSizeYChanged();
    void signalAnchorXChanged();
    void signalAnchorYChanged();
    void signalBorderChanged();
    void signalShapeIndexChanged();
    void signalIterationsChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGERODE_H
