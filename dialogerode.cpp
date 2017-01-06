#include "dialogerode.h"
#include "ui_dialogerode.h"

DialogErode::DialogErode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogErode)
{
    ui->setupUi(this);
    anchorX = -1;
    anchorY = -1;
    sizeX = 3;
    sizeY = 3;
    border = 0;
    shape = 0;
    iterations = 1;
    connect(ui->sliderAnchorX,SIGNAL(sliderMoved(int)),this,SLOT(anchorXChanged(int)));
    connect(ui->sliderAnchorY,SIGNAL(sliderMoved(int)),this,SLOT(anchorYChanged(int)));
    connect(ui->sliderSizeX,SIGNAL(sliderMoved(int)),this,SLOT(sizeXChanged(int)));
    connect(ui->sliderSizeY,SIGNAL(sliderMoved(int)),this,SLOT(sizeYChanged(int)));
    connect(ui->cBxBorder,SIGNAL(currentIndexChanged(int)),this,SLOT(borderChanged(int)));
    connect(ui->cBxShape,SIGNAL(currentIndexChanged(int)),this,SLOT(shapeIndexChanged(int)));
    connect(ui->sBxDilateIterations,SIGNAL(valueChanged(int)),SLOT(iterationsChanged(int)));

}

DialogErode::~DialogErode()
{
    delete ui;
}

void DialogErode::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogErode::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogErode::sizeXChanged(int i)
{
    sizeX = i;
    ui->sliderAnchorX->setMaximum(i);
    emit signalSizeXChanged();
}

void DialogErode::sizeYChanged(int i)
{
    sizeY = i;
    ui->sliderAnchorY->setMaximum(i);
    emit signalSizeXChanged();
}

void DialogErode::anchorXChanged(int i)
{
   anchorX = i;
    if(i == 0)
        anchorX = -1;
    emit signalAnchorXChanged();
}

void DialogErode::anchorYChanged(int i)
{
    anchorY = i;
    if(i == 0)
        anchorY = -1;
    emit signalAnchorYChanged();
}

void DialogErode::borderChanged(int i)
{
    border = i;
    if(i==3)
        border = 4;
    emit signalBorderChanged();
}

void DialogErode::shapeIndexChanged(int i)
{
    shape = i;
    emit signalShapeIndexChanged();
}

void DialogErode::iterationsChanged(int i)
{
    iterations = i;
    emit signalIterationsChanged();
}
