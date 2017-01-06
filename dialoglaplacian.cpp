#include "dialoglaplacian.h"
#include "ui_dialoglaplacian.h"

DialogLaplacian::DialogLaplacian(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLaplacian)
{
    ui->setupUi(this);
    size = 3;
    scale = 1;
    delta = 0;
    border = 0;

    connect(ui->sliderSize,SIGNAL(sliderMoved(int)),this,SLOT(sizeChanged(int)));
    connect(ui->sliderScale,SIGNAL(sliderMoved(int)),this,SLOT(scaleChanged(int)));
    connect(ui->sliderDelta,SIGNAL(sliderMoved(int)),this,SLOT(deltaChanged(int)));
    connect(ui->cBxBorder,SIGNAL(currentIndexChanged(int)),this,SLOT(borderChanged(int)));
}

DialogLaplacian::~DialogLaplacian()
{    
    delete ui;
}

void DialogLaplacian::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogLaplacian::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogLaplacian::sizeChanged(int i)
{
    if(i%2 == 0)
    {
        i--;
        ui->sliderSize->setValue(i);
    }
    size = i;
    emit signalSizeChanged();
}

void DialogLaplacian::scaleChanged(int i)
{
    scale = double(i)/100;
    emit signalScaleChanged();
}

void DialogLaplacian::deltaChanged(int i)
{
    delta = double(i)/100;
    emit signalDeltaChanged();
}

void DialogLaplacian::borderChanged(int i)
{
    border = i;
    if(i == 3)
        border = 4;
    emit signalBorderChanged();
}
