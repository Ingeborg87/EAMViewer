#ifndef DIALOGMSER_H
#define DIALOGMSER_H

#include <QDialog>
#include <QStandardItemModel>
#include <QKeyEvent>

namespace Ui {
class DialogMSER;
}

class DialogMSER : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMSER(QWidget *parent = 0);
    ~DialogMSER();
    int delta;
    int minArea;
    int maxArea;
    double maxVariation;
    double minDiversity;
    int lineThickness;
    bool drawFlagKeyPoints;
    bool drawFlagHulls;
    bool drawFlagEllipses;
    void addModell(QStandardItemModel* mdl);
    
private:
    Ui::DialogMSER *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void deltaChanged(int i);
    void minAreaChanged(int i);
    void maxAreaChanged(int i);
    void minDiversityChanged(double d);
    void maxVariationChanged(double d);
    
    void lineThicknessChanged(int i);
    void drawFlagKeyPointsChanged(bool b);
    void drawFlagHullsChanged(bool b);
    void drawFlagEllipsesChanged(bool b);
signals:
    void signalDeltaChanged();
    void signalMinAreaChanged();
    void signalMaxAreaChanged();
    void signalMinDiversityChanged();
    void signalMaxVariationChanged();
    void signalPressReturn();
    void signalXDialog();
    
    void signalDrawFlagKeyPointsChanged(bool b);
    void signalDrawFlagHullsChanged(bool b);
    void signalDrawFlagEllipsesChanged(bool b);
};

#endif // DIALOGMSER_H
