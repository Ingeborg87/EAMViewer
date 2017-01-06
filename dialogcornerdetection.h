#ifndef DIALOGCORNERDETECTION_H
#define DIALOGCORNERDETECTION_H

#include <QDialog>
#include <QStandardItemModel>
#include <QKeyEvent>
namespace Ui {
class DialogCornerDetection;
}

class DialogCornerDetection : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogCornerDetection(QWidget *parent = 0);
    ~DialogCornerDetection();
    bool    harris;
    bool    shiTomasi;
    int     sobelSize;
    int     blockSize;
    int     borderType;
    int     color;
    int     lineThickness;
    int     quality;
    bool    drawFlag;
    void addModel(QStandardItemModel* mdl);
private:
    Ui::DialogCornerDetection *ui;
    void keyPressEvent(QKeyEvent *);
    void closeEvent(QCloseEvent *);
private slots:
    void harrisChanged(bool b);
    void shiTomasiChanged(bool b);
    void sobelSizeChanged(int i);
    void blockSizeChanged(int i);
    void borderTypeChanged(int i);
    void lineThicknessChanged(int i);
    void colorChanged(int i);
    void setDrawCirclesSignal(bool b);
    void qualityChanged(int i);
signals:
    void signalChangeDrawFlag(bool b);
    void signalDrawCircles();
    void signalCornerFlagChanged();
    void signalSobelSizeChanged();
    void signalBlockSizeChanged();
    void signalBorderTypeChanged();
    void signalQualityChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGCORNERDETECTION_H
