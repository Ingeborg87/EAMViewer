#ifndef DIALOGMORPHOLOGYEX_H
#define DIALOGMORPHOLOGYEX_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogMorphologyEx;
}

class DialogMorphologyEx : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMorphologyEx(QWidget *parent = 0);
    ~DialogMorphologyEx();
    int anchorX;
    int anchorY;
    int sizeX;
    int sizeY;
    int iterations;
    int shape;
    int opMethod;
    int border;
    
private:
    Ui::DialogMorphologyEx *ui;
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
    void opIndexChanged(int i);
signals:
    void signalSizeXChanged();
    void signalSizeYChanged();
    void signalAnchorXChanged();
    void signalAnchorYChanged();
    void signalBorderChanged();
    void signalShapeIndexChanged();
    void signalIterationsChanged();
    void signalOpIndexChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGMORPHOLOGYEX_H
