#ifndef DIALOGCUSTOMFILTER_H
#define DIALOGCUSTOMFILTER_H

#include <QDialog>
#include <QKeyEvent>
#include <iostream>
#include <QSignalMapper>
#include <QLineEdit>
#include <cmath>

using namespace std;
namespace Ui {
class DialogCustomFilter;
}

class DialogCustomFilter : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogCustomFilter(QWidget *parent = 0);
    ~DialogCustomFilter();
    int x, y;
    int anchorX;
    int anchorY;
    double delta;
    int border;
    QSignalMapper* QSM;
    double* returnDataPointer();
private:
    Ui::DialogCustomFilter *ui;

    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
    bool checkString(QString &qstr, int pos);

private slots:
    void textChangingSlot(int w);
    void xIndexChanged(int i);
    void yIndexChanged(int i);
    void anchorXChanged(int i);
    void anchorYChanged(int i);
    void deltaChanged(int i);
    void borderChanged(int i);
signals:
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGCUSTOMFILTER_H
