#ifndef DIALOGBGSUBSTRACTION_H
#define DIALOGBGSUBSTRACTION_H

#include <QDialog>

namespace Ui {
class DialogBGSubstraction;
}

class DialogBGSubstraction : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogBGSubstraction(QWidget *parent = 0);
    ~DialogBGSubstraction();
    
private:
    Ui::DialogBGSubstraction *ui;
};

#endif // DIALOGBGSUBSTRACTION_H
