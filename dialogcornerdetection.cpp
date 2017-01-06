#include "dialogcornerdetection.h"
#include "ui_dialogcornerdetection.h"

DialogCornerDetection::DialogCornerDetection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCornerDetection)
{
    ui->setupUi(this);
    harris = true;
    shiTomasi = false;
    sobelSize = 3;
    blockSize = 3;
    lineThickness = 1;
    color = 0;
    quality = 50;
    borderType = 0;
    drawFlag = false;

    connect(ui->rBHarris,SIGNAL(clicked(bool)),this,SLOT(harrisChanged(bool)));
    connect(ui->rBShiTomasi,SIGNAL(clicked(bool)),this,SLOT(shiTomasiChanged(bool)));
    connect(ui->sBSobelSize,SIGNAL(valueChanged(int)),this,SLOT(sobelSizeChanged(int)));
    connect(ui->sBBlockSize,SIGNAL(valueChanged(int)),this,SLOT(blockSizeChanged(int)));
    connect(ui->cBxBorderType,SIGNAL(currentIndexChanged(int)),this,SLOT(borderTypeChanged(int)));
    connect(ui->sliderColor,SIGNAL(valueChanged(int)),this,SLOT(colorChanged(int)));
    connect(ui->sliderQuality,SIGNAL(valueChanged(int)),this,SLOT(qualityChanged(int)));
    connect(ui->cBDrawCorners,SIGNAL(clicked(bool)),this,SLOT(setDrawCirclesSignal(bool)));
    connect(ui->sliderLineThickness, SIGNAL(sliderMoved(int)),SLOT(lineThicknessChanged(int)));
}

DialogCornerDetection::~DialogCornerDetection()
{
    delete ui;
}

void DialogCornerDetection::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogCornerDetection::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogCornerDetection::harrisChanged(bool b)
{
    harris = b;
    ui->rBShiTomasi->setChecked(!b);
    shiTomasi = !b;
    emit signalCornerFlagChanged();
}

void DialogCornerDetection::shiTomasiChanged(bool b)
{
    shiTomasi = b;
    ui->rBHarris->setChecked(!b);
    harris = !b;
    emit signalCornerFlagChanged();
}

void DialogCornerDetection::sobelSizeChanged(int i)
{
    sobelSize = i;
    emit signalSobelSizeChanged();
}

void DialogCornerDetection::blockSizeChanged(int i)
{
    blockSize = i;
    emit signalBlockSizeChanged();
}

void DialogCornerDetection::borderTypeChanged(int i)
{
    borderType = i;
    if(i == 3)
        borderType = 4;
    emit signalBorderTypeChanged();
}

void DialogCornerDetection::addModel(QStandardItemModel *mdl)
{
    ui->tableView->setModel(mdl);
}

void DialogCornerDetection::lineThicknessChanged(int i)
{
    lineThickness = i;
    if(drawFlag == true)
        emit signalDrawCircles();
}

void DialogCornerDetection::colorChanged(int i)
{
    color = i;
    if(drawFlag == true)
        emit signalDrawCircles();
}

void DialogCornerDetection::setDrawCirclesSignal(bool b)
{
    drawFlag = b;
    emit signalChangeDrawFlag(b);
}

void DialogCornerDetection::qualityChanged(int i)
{
    quality = i;
    emit signalQualityChanged();
}
