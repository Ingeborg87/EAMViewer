#include "dialogscharr.h"
#include "ui_dialogscharr.h"

DialogScharr::DialogScharr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogScharr)
{
    ui->setupUi(this);
    dx = 1;
    dy = 0;
    scale = 1;
    delta = 0;
    borderType = 0;

    connect(ui->sliderDx,SIGNAL(valueChanged(int)),this,SLOT(dxChanged(int)));
    connect(ui->sliderDy,SIGNAL(valueChanged(int)),this,SLOT(dyChanged(int)));
    connect(ui->sliderScale,SIGNAL(sliderMoved(int)),this,SLOT(scaleChanged(int)));
    connect(ui->sliderDelta,SIGNAL(sliderMoved(int)),this,SLOT(deltaChanged(int)));
    connect(ui->cBxBorderType,SIGNAL(currentIndexChanged(int)),this,SLOT(borderTypeChanged(int)));
}

DialogScharr::~DialogScharr()
{
    delete ui;
}

void DialogScharr::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogScharr::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogScharr::dxChanged(int i)
{
    dx = i;
    if (i==0)
    {
        dy = 1;
        ui->sliderDy->setValue(1);
    }
    else
    {
        dy = 0;
        ui->sliderDy->setValue(0);
    }
    emit signalDxChanged();
}

void DialogScharr::dyChanged(int i)
{
    dy = i;
    if (i==0)
    {
        dx = 1;
        ui->sliderDx->setValue(1);
    }
    else
    {
        dx = 0;
        ui->sliderDx->setValue(0);
    }
    emit signalDyChanged();
}

void DialogScharr::scaleChanged(int i)
{
    scale = double(i)/100;
    emit signalScaleChanged();
}

void DialogScharr::deltaChanged(int i)
{
    delta = double(i);
    emit signalDeltaChanged();
}

void DialogScharr::borderTypeChanged(int i)
{
    borderType = i;
    if(i == 3)
        borderType = 4;
    emit signalBorderTypeChanged();
}
