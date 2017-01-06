#include "dialoghoughcircles.h"
#include "ui_dialoghoughcircles.h"

DialogHoughCircles::DialogHoughCircles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHoughCircles)
{
    ui->setupUi(this);
    method = 3;
    invRatio = 1;
    minDist = 1;
    cannyThreshold = 100;
    threshold = 100;
    minRadius = 40;
    maxRadius = 100;
    lineThickness = 1;
    drawFlag = false;
    color = 0;

    connect(ui->cBxMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(methodChanged(int)));
    connect(ui->dblSBInvRat,SIGNAL(valueChanged(double)),this,SLOT(invRatioChanged(double)));
    connect(ui->dblSBMinDist,SIGNAL(valueChanged(double)),this,SLOT(minDistChanged(double)));
    connect(ui->dblDBCannyThreshold,SIGNAL(valueChanged(double)),this,SLOT(cannyThresholdChanged(double)));
    connect(ui->dblSBThreshold,SIGNAL(valueChanged(double)),this,SLOT(thresholdChanged(double)));
    connect(ui->sBMinRadius,SIGNAL(valueChanged(int)),this,SLOT(minRadiusChanged(int)));
    connect(ui->sBMaxRadius,SIGNAL(valueChanged(int)),this,SLOT(maxRadiusChanged(int)));

    connect(ui->sliderColor,SIGNAL(valueChanged(int)),this,SLOT(colorChanged(int)));
    connect(ui->sliderLineThickness,SIGNAL(valueChanged(int)),this,SLOT(lineThicknessChanged(int)));
    connect(ui->cBDrawCircles,SIGNAL(clicked(bool)),this,SLOT(setDrawCirclesSignal(bool)));
}

DialogHoughCircles::~DialogHoughCircles()
{
    delete ui;
}

void DialogHoughCircles::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogHoughCircles::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogHoughCircles::methodChanged(int i)
{
    if(i == 0)
        method = 3;
    emit signalMethodChanged();
}

void DialogHoughCircles::minDistChanged(double d)
{
    minDist = d;
    emit signalMinDistChanged();
}

void DialogHoughCircles::invRatioChanged(double d)
{
    invRatio = d;
    emit signalInvRatioChanged();
}

void DialogHoughCircles::cannyThresholdChanged(double d)
{
    cannyThreshold = d;
    emit signalCannyThresholdChanged();
}

void DialogHoughCircles::thresholdChanged(double d)
{
    threshold = d;
    emit signalThresholdChanged();
}

void DialogHoughCircles::minRadiusChanged(int i)
{
    minRadius = i;
    emit signalMinRadiusChanged();
}

void DialogHoughCircles::maxRadiusChanged(int i)
{
    maxRadius = i;
    emit signalMaxRadiusChanged();
}

void DialogHoughCircles::setDrawCirclesSignal(bool b)
{
    drawFlag = b;
    emit signalChangeDrawFlag(b);
}

void DialogHoughCircles::addModel(QStandardItemModel *mdl)
{
    ui->tableView->setModel(mdl);
}

void DialogHoughCircles::lineThicknessChanged(int i)
{
    lineThickness = i;
    if(drawFlag == true)
        emit signalDrawCircles();
}

void DialogHoughCircles::colorChanged(int i)
{
    color = i;
    if(drawFlag == true)
        emit signalDrawCircles();
}
