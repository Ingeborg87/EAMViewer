#include "dialoghoughlines.h"
#include "ui_dialoghoughlines.h"

DialogHoughLines::DialogHoughLines(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHoughLines)
{
    pi = 3.14159265359;
    ui->setupUi(this);

    prob = false;
    rho = 1;
    rhoDiv = 0;
    theta = pi/180;
    thetaDiv = 0;
    threshold = 150;
    minLength = 10;
    maxGap = 10;
    lineThickness = 1;
    drawFlag = false;
    ui->dblSBRho->setValue(1);
    ui->dblSBTheta->setValue(pi/180);

    connect(ui->rBProb,SIGNAL(toggled(bool)),this,SLOT(probChanged(bool)));
    connect(ui->dblSBRho,SIGNAL(valueChanged(double)),this,SLOT(rhoChanged(double)));
    connect(ui->dblSBDivRho,SIGNAL(valueChanged(double)),this,SLOT(rhoDivChanged(double)));
    connect(ui->dblSBTheta,SIGNAL(valueChanged(double)),this,SLOT(thetaChanged(double)));
    connect(ui->dblSBDivTheta,SIGNAL(valueChanged(double)),this,SLOT(thetaDivChanged(double)));
    connect(ui->sBThreshold,SIGNAL(valueChanged(int)),this,SLOT(thresholdChanged(int)));
    connect(ui->dblSBMinLength,SIGNAL(valueChanged(double)),this,SLOT(minLengthChanged(double)));
    connect(ui->dblSBMaxGap,SIGNAL(valueChanged(double)),this,SLOT(maxGapChanged(double)));

    connect(ui->sliderColor,SIGNAL(valueChanged(int)),this,SLOT(colorChanged(int)));
    connect(ui->sliderLineThickness,SIGNAL(valueChanged(int)),this,SLOT(lineThicknessChanged(int)));

    connect(ui->cBDrawLines,SIGNAL(clicked(bool)),this,SLOT(setDrawLinesSignal(bool)));

    ui->dblSBRho->setMinimum(0.000001);
    ui->dblSBTheta->setMinimum(0.000001);

    ui->dblSBRho->setSingleStep(0.25);
    ui->dblSBTheta->setSingleStep(0.1);
    ui->dblSBDivRho->setSingleStep(0.1);
    ui->dblSBDivTheta->setSingleStep(0.1);
    ui->dblSBMinLength->setSingleStep(0.25);
    ui->dblSBMaxGap->setSingleStep(0.25);

    probChanged(false);
}

DialogHoughLines::~DialogHoughLines()
{
    delete ui;
}

void DialogHoughLines::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogHoughLines::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogHoughLines::probChanged(bool b)
{
    ui->lblDivRho->setVisible(!b);
    ui->lblDivTheta->setVisible(!b);
    ui->lblMinLength->setVisible(b);
    ui->lblMaxGap->setVisible(b);

    ui->dblSBDivRho->setVisible(!b);
    ui->dblSBDivTheta->setVisible(!b);
    ui->dblSBMinLength->setVisible(b);
    ui->dblSBMaxGap->setVisible(b);

    prob = b;
    emit signalProbChanged();
}

void DialogHoughLines::rhoChanged(double d)
{
    rho = d;
    emit signalRhoChanged();
}

void DialogHoughLines::rhoDivChanged(double d)
{
    rhoDiv = d;
    emit signalRhoDivChanged();
}

void DialogHoughLines::thetaChanged(double d)
{
    theta = d;
    emit signalThetaChanged();
}

void DialogHoughLines::thetaDivChanged(double d)
{
    thetaDiv = d;
    emit signalThetaDivChanged();
}

void DialogHoughLines::thresholdChanged(int i)
{
    threshold = i;
    emit signalThresholdChanged();
}

void DialogHoughLines::minLengthChanged(double d)
{
    minLength = d;
    emit signalMinLengthChanged();
}

void DialogHoughLines::maxGapChanged(double d)
{
    maxGap = d;
    emit signalMaxGapChanged();
}

void DialogHoughLines::setDrawLinesSignal(bool b)
{
    drawFlag = b;
    emit signalChangeDrawFlag(b);
}

void DialogHoughLines::addModel(QStandardItemModel *mdl)
{
    ui->tableView->setModel(mdl);
}

void DialogHoughLines::lineThicknessChanged(int i)
{
    lineThickness = i;
    if(drawFlag == true)
        emit signalDrawLines(prob);
}

void DialogHoughLines::colorChanged(int i)
{
    color = i;
    if(drawFlag == true)
        emit signalDrawLines(prob);
}
