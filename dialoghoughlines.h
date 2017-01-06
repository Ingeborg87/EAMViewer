#ifndef DIALOGHOUGHLINES_H
#define DIALOGHOUGHLINES_H

#include <QDialog>
#include <QKeyEvent>
#include <QStandardItemModel>

namespace Ui {
class DialogHoughLines;
}

class DialogHoughLines : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogHoughLines(QWidget *parent = 0);
    ~DialogHoughLines();
    bool prob;
    double rho;
    double rhoDiv;
    double theta;
    double thetaDiv;
    int threshold;
    double minLength;
    double maxGap;
    int lineThickness;
    int color;
    bool drawFlag;
    void addModel(QStandardItemModel* mdl);
    
private:
    Ui::DialogHoughLines *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
    double pi;
private slots:
    void probChanged(bool b);
    void rhoChanged(double d);
    void rhoDivChanged(double d);
    void thetaChanged(double d);
    void thetaDivChanged(double d);
    void thresholdChanged(int i);
    void minLengthChanged(double d);
    void maxGapChanged(double d);
    void setDrawLinesSignal(bool b);
    void lineThicknessChanged(int i);
    void colorChanged(int i);
signals:
    void signalChangeDrawFlag(bool b);
    void signalDrawLines(bool b);
    void signalProbChanged();
    void signalRhoChanged();
    void signalRhoDivChanged();
    void signalThetaChanged();
    void signalThetaDivChanged();
    void signalThresholdChanged();
    void signalMinLengthChanged();
    void signalMaxGapChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGHOUGHLINES_H
