#ifndef DIALOGGAMMATRANSFORMATION_H
#define DIALOGGAMMATRANSFORMATION_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogGammaTransformation;
}

class DialogGammaTransformation : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogGammaTransformation(QWidget *parent = 0);
    ~DialogGammaTransformation();
    int valueGammaTrans;
private:
    Ui::DialogGammaTransformation *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void valueGammaTransChanged(int i);
signals:
    void signalGammaTransChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGGAMMATRANSFORMATION_H
