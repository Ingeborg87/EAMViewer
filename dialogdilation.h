#ifndef DIALOGDILATION_H
#define DIALOGDILATION_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogDilation;
}

class DialogDilation : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDilation(QWidget *parent = 0);
    ~DialogDilation();
    int anchorX;
    int anchorY;
    int sizeX;
    int sizeY;
    int iterations;
    int shape;
    int border;
private:
    Ui::DialogDilation *ui;
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

#endif // DIALOGDILATION_H
