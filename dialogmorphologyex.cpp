#include "dialogmorphologyex.h"
#include "ui_dialogmorphologyex.h"

DialogMorphologyEx::DialogMorphologyEx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMorphologyEx)
{
    ui->setupUi(this);
    anchorX = -1;
    anchorY = -1;
    sizeX = 3;
    sizeY = 3;
    border = 0;
    shape = 0;
    iterations = 1;
    opMethod = 2;
    connect(ui->sliderAnchorX,SIGNAL(sliderMoved(int)),this,SLOT(anchorXChanged(int)));
    connect(ui->sliderAnchorY,SIGNAL(sliderMoved(int)),this,SLOT(anchorYChanged(int)));
    connect(ui->sliderSizeX,SIGNAL(sliderMoved(int)),this,SLOT(sizeXChanged(int)));
    connect(ui->sliderSizeY,SIGNAL(sliderMoved(int)),this,SLOT(sizeYChanged(int)));
    connect(ui->cBxBorder,SIGNAL(currentIndexChanged(int)),this,SLOT(borderChanged(int)));
    connect(ui->cBxShape,SIGNAL(currentIndexChanged(int)),this,SLOT(shapeIndexChanged(int)));
    connect(ui->sBxIterations,SIGNAL(valueChanged(int)),SLOT(iterationsChanged(int)));
    connect(ui->cBxOpMethods,SIGNAL(currentIndexChanged(int)),SLOT(opIndexChanged(int)));
}

DialogMorphologyEx::~DialogMorphologyEx()
{
    delete ui;
}

void DialogMorphologyEx::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogMorphologyEx::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogMorphologyEx::sizeXChanged(int i)
{
    sizeX = i;
    ui->sliderAnchorX->setMaximum(i);
    emit signalSizeXChanged();
}

void DialogMorphologyEx::sizeYChanged(int i)
{
    sizeY = i;
    ui->sliderAnchorY->setMaximum(i);
    emit signalSizeYChanged();
}

void DialogMorphologyEx::anchorXChanged(int i)
{
    anchorX = i;
    if(i == 0)
        anchorX = -1;
    emit signalAnchorXChanged();
}

void DialogMorphologyEx::anchorYChanged(int i)
{
    anchorY = i;
    if(i == 0)
        anchorY = -1;
    emit signalAnchorXChanged();
}

void DialogMorphologyEx::borderChanged(int i)
{
    border = i;
    if(i==3)
        border = 4;
    emit signalBorderChanged();
}

void DialogMorphologyEx::shapeIndexChanged(int i)
{
    shape = i;
    emit signalShapeIndexChanged();
}

void DialogMorphologyEx::iterationsChanged(int i)
{
    iterations = i;
    emit signalIterationsChanged();
}

void DialogMorphologyEx::opIndexChanged(int i)
{
    if(i == 0)
        opMethod = 2;
    if(i == 1)
        opMethod = 3;
    if(i == 2)
        opMethod = 4;
    if(i == 3)
        opMethod = 5;
    if(i == 4)
        opMethod = 6;
    emit signalOpIndexChanged();

}
