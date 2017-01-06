#ifndef DIALOGEVALMSER_H
#define DIALOGEVALMSER_H

#include <QDialog>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <opencv2/core/core.hpp>

using namespace cv;
namespace Ui {
class DialogEvalMSER;
}

class DialogEvalMSER : public QDialog
{
    Q_OBJECT

public:
    bool sortBySize = false;
    bool sortByHull = false;
    float maxSize = 1;
    float minSize = 0;
    float minRatio = 0;
    float maxRatio = 1;
    int thickness = 1;
    bool drawFlagKeyPoints = false;
    bool drawFlagHulls = false;
    bool drawFlagEllipses = false;
    void addModel( QStandardItemModel* mdl);
    explicit DialogEvalMSER(QWidget *parent = 0);
    ~DialogEvalMSER();

private:
    QStandardItemModel* stItModel;
    Ui::DialogEvalMSER *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *prEvent);
    void calculateHulls();
    vector<vector<Point>> points;
    vector<vector<Point>> hulls;

private slots:
    void sortBySizeChanged(bool b);
    void sortByHullChanged(bool b);
    void minSizeChanged(int i);
    void minRatioChanged(int i);
    void maxRatioChanged(int i);
    void maxSizeChanged(int i);
    void pBSaveDataPushed();
    void thicknessChanged(int i);
    void drawKeyPointsFlagChanged(bool b);
    void drawHullsFlagChanged(bool b);
    void drawEllipsesFlagChanged(bool b);

signals:
    void signalXDialog();
    void signalPressReturn();
    void signalSortBySizeChanged();
    void signalSortByHullChanged();
    void signalMinRatioChanged();
    void signalMaxRatioChanged();
    void signalMinSizeChanged();
    void signalMaxSizeChanged();
    void signalDrawKeyPointsFlagChanged();
    void signalDrawFlagHullsChanged();
    void signalDrawFlagEllipsesChanged();
    void signalPBSaveDataPushed();

};

#endif // DIALOGEVALMSER_H
