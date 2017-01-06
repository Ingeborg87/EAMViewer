#include "dialogbgsubstraction.h"
#include "ui_dialogbgsubstraction.h"

DialogBGSubstraction::DialogBGSubstraction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBGSubstraction)
{
    ui->setupUi(this);
}

DialogBGSubstraction::~DialogBGSubstraction()
{
    delete ui;
}
