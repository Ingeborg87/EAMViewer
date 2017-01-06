#ifndef DIALOGFAST_H
#define DIALOGFAST_H

#include <QDialog>
#include <QKeyEvent>
#include <QStandardItemModel>

namespace Ui {
class DialogFAST;
}

class DialogFAST : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogFAST(QWidget *parent = 0);
    ~DialogFAST();
    int threshold;
    bool NMS;
    int type;
    bool drawKeyPointsFlag;
    void addModel( QStandardItemModel* mdl);
private:
    Ui::DialogFAST *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);

private slots:
    void thresholdChanged(int i);
    void NMSChanged(bool b);
    void typeChanged(int i);
    void drawKeyPointsFlagChanged(bool b);
signals:
    void signalPressReturn();
    void signalXDialog();
    void signalThresholdChanged();
    void signalNMSChanged();
    void signalTypeChanged();
    void signalDrawKeyPointsFlagChanged();
};

#endif // DIALOGFAST_H
