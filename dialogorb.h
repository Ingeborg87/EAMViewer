#ifndef DIALOGORB_H
#define DIALOGORB_H

#include <QDialog>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QStandardItemModel>

namespace Ui {
class DialogORB;
}

class DialogORB : public QDialog
{
    Q_OBJECT

public:
    explicit DialogORB(QWidget *parent = 0);
    ~DialogORB();
    int nFeatures = 500;
    int patchSize = 31;
    int nLevels = 8;
    int firstLevel;
    int edgeThreshold = 31;
    float scaleFactor = 1.2f;
    bool drawKeyPointsFlag = false;
    bool FASTKeyPoints = false;
    bool BRISKKeyPoints = false;
    void addModel( QStandardItemModel* mdl);

private:
    Ui::DialogORB *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *prEvent);
private slots:
    void FASTKeyPointsChanged(bool b);
    void BRISKKeyPointsChanged(bool b);
    void nFeaturesChanged(int i);
    void scaleFactorChanged(double d);
    void nLevelsChanged(int i);
    void edgeThresholdChanged(int i);
    void firstLevelChanged(int i);
    void patchSizeChanged(int i);
    void drawKeyPointsFlagChanged(bool b);

signals:
    void signalXDialog();
    void signalPressReturn();
    void signalNFeaturesChanged();
    void signalScaleFactorChanged();
    void signalNLevelsChanged();
    void signalEdgeThresholdChanged();
    void signalFirstLevelChanged();
    void signalPatchSizeChanged();
    void signalDrawKeyPointsFlagChanged();
    void signalFASTKeyPointsChanged();
    void signalBRISKKeyPointsChanged();
};

#endif // DIALOGORB_H
