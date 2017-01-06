#ifndef DIALOGFREAK_H
#define DIALOGFREAK_H

#include <QDialog>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QStandardItemModel>

namespace Ui {
class DialogFREAK;
}

class DialogFREAK : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFREAK(QWidget *parent = 0);
    ~DialogFREAK();
    bool orientationNormalized = true;
    bool scaleNormalized = true;
    float patternScale = 22.0f;
    int nOctaves = 4;
    bool drawKeyPointsFlag = false;
    void addModel( QStandardItemModel* mdl);
    bool FASTKeyPoints = true;
    bool ORBKeyPoints = false;
    bool BRISKKeyPoints = false;
private:
    Ui::DialogFREAK *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *prEvent);

private slots:
    void FASTKeyPointsChanged(bool b);
    void ORBKeyPointsChanged(bool b);
    void BRISKKeyPointsChanged(bool b);
    void orientationNormalizedChanged(bool b);
    void scaleNormalizedChanged(bool b);
    void patternScaleChanged(double d);
    void nOctavesChanged(int i);
    void drawKeyPointsFlagChanged(bool b);

signals:
    void signalXDialog();
    void signalPressReturn();
    void signalOrientationNormalizedChanged();
    void signalScaleNormalizedChanged();
    void signalPatternScaleChanged();
    void signalNOctavesChanged();
    void signalDrawKeyPointsFlagChanged();
    void signalFASTKeyPointsChanged();
    void signalORBKeyPointsChanged();
    void signalBRISKKeyPointsChanged();
};

#endif // DIALOGFREAK_H
