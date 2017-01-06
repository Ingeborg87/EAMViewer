#ifndef DIALOGLAPLACIAN_H
#define DIALOGLAPLACIAN_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogLaplacian;
}

class DialogLaplacian : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogLaplacian(QWidget *parent = 0);
    ~DialogLaplacian();
    int size;
    double scale;
    double delta;
    int border;
    
private:
    Ui::DialogLaplacian *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void sizeChanged(int i);
    void scaleChanged(int i);
    void deltaChanged(int i);
    void borderChanged(int i);
signals:
    void signalSizeChanged();
    void signalScaleChanged();
    void signalDeltaChanged();
    void signalBorderChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGLAPLACIAN_H
