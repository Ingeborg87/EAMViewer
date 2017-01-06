#include "dialoggaussian.h"
#include "ui_dialoggaussian.h"


DialogGaussian::DialogGaussian(QWidget *parent):QDialog(parent),
    ui(new Ui::DialogGaussian)
{
    ui->setupUi(this);
    sliderValueSizeX = 3;
    sliderValueSizeY = 3;
    sliderValueSigmaX = 1/500;
    sliderValueSigmaY = 1/500;
    X = 0;
    Y = 0;
    cbxIndex = 0;
    connect(ui->sliderSizeX,SIGNAL(sliderMoved(int)),this,SLOT(sizeXChanged(int)));
    connect(ui->sliderSizeY,SIGNAL(sliderMoved(int)),this,SLOT(sizeYChanged(int)));
    connect(ui->sliderSigmaX,SIGNAL(sliderMoved(int)),this,SLOT(sigmaXChanged(int)));
    connect(ui->sliderSigmaY,SIGNAL(sliderMoved(int)),this,SLOT(sigmaYChanged(int)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(cbxIndexChanged(int)));
}

DialogGaussian::~DialogGaussian()
{
    delete ui;
}

void DialogGaussian::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogGaussian::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogGaussian::sizeXChanged(int i)
{  
    if(i%2 == 0)
    {
        i--;
        ui->sliderSizeX->setValue(i);
    }
    sliderValueSizeX = i;
    emit signalSizeXChanged();
}

void DialogGaussian::sizeYChanged(int i)
{    
    if(i%2 == 0)
    {
        i--;
        ui->sliderSizeY->setValue(i);
    }
    sliderValueSizeY = i;
    emit signalSizeYChanged();
}

void DialogGaussian::sigmaXChanged(int i)
{
    sliderValueSigmaX = float(i)/500;
    emit signalSigmaXChanged();
}

void DialogGaussian::sigmaYChanged(int i)
{
    sliderValueSigmaY = float(i)/500;
    emit signalSigmaYChanged();
}

void DialogGaussian::cbxIndexChanged(int i)
{
    cbxIndex = i;
    if(i==3)
        cbxIndex = 4;
    emit signalCbxIndexChanged();
}

void DialogGaussian::showSlot()
{
    if( X >= Y)
    {
        ui->sliderSizeX->setMaximum(Y/16);
        if(ui->sliderSizeX->maximum()%2 == 0)
            ui->sliderSizeX->setMaximum(ui->sliderSizeX->maximum()-1);
        ui->sliderSizeY->setMaximum(Y/16);
        if(ui->sliderSizeY->maximum()%2 == 0)
            ui->sliderSizeY->setMaximum(ui->sliderSizeY->maximum()-1);
    }
    if( X < Y)
    {
        ui->sliderSizeX->setMaximum(X/16);
        if(ui->sliderSizeX->maximum()%2 == 0)
            ui->sliderSizeX->setMaximum(ui->sliderSizeX->maximum()-1);
        ui->sliderSizeY->setMaximum(X/16);
        if(ui->sliderSizeY->maximum()%2 == 0)
            ui->sliderSizeY->setMaximum(ui->sliderSizeY->maximum()-1);
    }
}
