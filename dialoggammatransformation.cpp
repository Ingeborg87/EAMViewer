#include "dialoggammatransformation.h"
#include "ui_dialoggammatransformation.h"

DialogGammaTransformation::DialogGammaTransformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGammaTransformation)
{
    ui->setupUi(this);
    valueGammaTrans = 0;
    connect(ui->valueGammaTrans,SIGNAL(sliderMoved(int)),this,SLOT(valueGammaTransChanged(int)));
}

DialogGammaTransformation::~DialogGammaTransformation()
{
    delete ui;
}

void DialogGammaTransformation::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogGammaTransformation::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogGammaTransformation::valueGammaTransChanged(int i)
{
    valueGammaTrans = i;
    emit signalGammaTransChanged();
}
