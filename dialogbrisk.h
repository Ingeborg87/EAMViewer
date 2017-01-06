#ifndef DIALOGBRISK_H
#define DIALOGBRISK_H

#include <QDialog>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QStandardItemModel>

namespace Ui {
class DialogBRISK;
}

class DialogBRISK : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBRISK(QWidget *parent = 0);
    ~DialogBRISK();
    int thresh = 30;
    int octaves = 3;
    float patternScale = 1.0f;
    bool drawKeyPointsFlag = false;
    bool FASTKeyPoints = false;
    bool ORBKeyPoints = false;
    void addModel( QStandardItemModel* mdl);

private:
    Ui::DialogBRISK *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *prEvent);

private slots:
    void threshChanged(int i);
    void octavesChanged(int i);
    void patternScaleChanged(double d);
    void drawKeyPointsFlagChanged(bool b);
    void FASTKeyPointsChanged(bool b);
    void ORBKeyPointsChanged(bool b);
signals:
    void signalXDialog();
    void signalPressReturn();
    void signalFASTKeyPointsChanged();
    void signalORBKeyPointsChanged();
    void signalsThreshChanged();
    void signalsOctavesChanged();
    void signalsPatternScaleChanged();
    void signalDrawKeyPointsFlagChanged();
};

#endif // DIALOGBRISK_H
