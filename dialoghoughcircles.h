#ifndef DIALOGHOUGHCIRCLES_H
#define DIALOGHOUGHCIRCLES_H

#include <QDialog>
#include <QKeyEvent>
#include <QStandardItemModel>

namespace Ui {
class DialogHoughCircles;
}

class DialogHoughCircles : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHoughCircles(QWidget *parent = 0);
    ~DialogHoughCircles();
    int method;
    double invRatio;
    double minDist;
    double cannyThreshold;
    double threshold;
    int minRadius;
    int maxRadius;
    int lineThickness;
    int color;
    bool drawFlag;
    void addModel(QStandardItemModel* mdl);
private:
    Ui::DialogHoughCircles *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void methodChanged(int i);
    void minDistChanged(double d);
    void invRatioChanged(double d);
    void cannyThresholdChanged(double d);
    void thresholdChanged(double d);
    void minRadiusChanged(int i);
    void maxRadiusChanged(int i);
    void setDrawCirclesSignal(bool b);
    void lineThicknessChanged(int i);
    void colorChanged(int i);
signals:
    void signalDrawCircles();
    void signalChangeDrawFlag(bool b);
    void signalMethodChanged();
    void signalMinDistChanged();
    void signalInvRatioChanged();
    void signalCannyThresholdChanged();
    void signalThresholdChanged();
    void signalMinRadiusChanged();
    void signalMaxRadiusChanged();
    void signalXDialog();
    void signalPressReturn();

};

#endif // DIALOGHOUGHCIRCLES_H
