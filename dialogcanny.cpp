#include "dialogcanny.h"
#include "ui_dialogcanny.h"

DialogCanny::DialogCanny(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCanny)
{
    ui->setupUi(this);
    threshold1 = 0;
    threshold2 = 0;
    sobelSize = 3;
    L2 = false;

    connect(ui->sliderThreshold1,SIGNAL(sliderMoved(int)),this,SLOT(threshold1Changed(int)));
    connect(ui->sliderThreshold2,SIGNAL(sliderMoved(int)),this,SLOT(threshold2Changed(int)));
    connect(ui->sBSobelSize,SIGNAL(valueChanged(int)),this,SLOT(sobelSizeChanged(int)));
    connect(ui->cBL2,SIGNAL(toggled(bool)),this,SLOT(L2Changed(bool)));
}

DialogCanny::~DialogCanny()
{
    delete ui;
}

void DialogCanny::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogCanny::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogCanny::threshold1Changed(int i)
{
    threshold1 = i;
    emit signalThreshold1Changed();
}

void DialogCanny::threshold2Changed(int i)
{
    threshold2 = i;
    emit signalThreshold1Changed();
}

void DialogCanny::sobelSizeChanged(int i)
{
    sobelSize = i;
    emit signalSobelSizeChanged();
}

void DialogCanny::L2Changed(bool b)
{
    L2 = b;
    emit signalL2Changed();
}
