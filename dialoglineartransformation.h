#ifndef DIALOGLINEARTRANSFORMATION_H
#define DIALOGLINEARTRANSFORMATION_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DialogLinearTransformation;
}

class DialogLinearTransformation : public QDialog
{
    Q_OBJECT

    
public:
    explicit DialogLinearTransformation(QWidget *parent = 0);
    ~DialogLinearTransformation();
    int sliderValueLinTrans;
private:
    Ui::DialogLinearTransformation *ui;
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* prEvent);
private slots:
    void valueLinTransChanged(int i);
signals:
    void signalValueLinTransChanged();
    void signalXDialog();
    void signalPressReturn();
};

#endif // DIALOGLINEARTRANSFORMATION_H
