#include "dialogsobel.h"
#include "ui_dialogsobel.h"

DialogSobel::DialogSobel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSobel)
{
    ui->setupUi(this);
    spinValueDx = 1;
    spinValueDy = 1;
    spinValueSize = 3;
    spinValueScale = 1;
    spinValueDelta = 0;
    cbxIndex = 0;

    connect(ui->spinBoxDx,SIGNAL(valueChanged(int)),this,SLOT(dxChanged(int)));
    connect(ui->spinBoxDy,SIGNAL(valueChanged(int)),this,SLOT(dyChanged(int)));
    connect(ui->spinBoxSize,SIGNAL(valueChanged(int)),this,SLOT(sizeChanged(int)));
    connect(ui->dSpinboxScale,SIGNAL(valueChanged(double)),this,SLOT(scaleChanged(double)));
    connect(ui->dSpinBoxDelta,SIGNAL(valueChanged(double)),this,SLOT(deltaChanged(double)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(cbxIndexChanged(int)));
}

DialogSobel::~DialogSobel()
{
    delete ui;
}

void DialogSobel::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogSobel::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogSobel::dxChanged(int i)
{
    spinValueDx = i;
    if((i == 0) & (spinValueDy == 0))
    {
            spinValueDy = 1;
            ui->spinBoxDy->setValue(1);
    }
    if(spinValueDx == spinValueSize)
    {
        spinValueDx = spinValueDx - 1;
        ui->spinBoxDx->setValue(spinValueDx);
    }
    emit signalDxChanged();
}

void DialogSobel::dyChanged(int i)
{
    spinValueDy = i;
    if((i == 0) & (spinValueDx == 0))
    {
        spinValueDx = 1;
        ui->spinBoxDx->setValue(1);
    }    
    if(spinValueDy == spinValueSize)
    {
        spinValueDy = spinValueDy - 1;
        ui->spinBoxDy->setValue(spinValueDy);
    }
    emit signalDyChanged();
}

void DialogSobel::sizeChanged(int i)
{
    spinValueSize = i;
    emit signalSizeChanged();
}

void DialogSobel::scaleChanged(double d)
{
    spinValueScale = d;
    emit signalScaleChanged();
}

void DialogSobel::deltaChanged(double d)
{
    spinValueDelta = d;
    emit signalDeltaChanged();
}

void DialogSobel::cbxIndexChanged(int i)
{
    cbxIndex = i;
    if(i==3)
        cbxIndex = 4;
    emit signalCbxIndexChanged();
}
