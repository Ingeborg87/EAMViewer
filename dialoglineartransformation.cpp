#include "dialoglineartransformation.h"
#include "ui_dialoglineartransformation.h"

DialogLinearTransformation::DialogLinearTransformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLinearTransformation)
{
    ui->setupUi(this);
    sliderValueLinTrans = 0;
    connect(ui->sliderValue,SIGNAL(sliderMoved(int)),this,SLOT(valueLinTransChanged(int)));
}

DialogLinearTransformation::~DialogLinearTransformation()
{
    delete ui;
}

void DialogLinearTransformation::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogLinearTransformation::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogLinearTransformation::valueLinTransChanged(int i)
{
    sliderValueLinTrans = i;
    emit signalValueLinTransChanged();
}
