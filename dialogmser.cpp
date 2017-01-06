#include "dialogmser.h"
#include "ui_dialogmser.h"

DialogMSER::DialogMSER(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMSER)
{
    ui->setupUi(this);
    delta = 5;
    minArea = 60;
    maxArea = 144000;
    maxVariation = 0.25;
    minDiversity = 0.2;
    lineThickness = 1;
    drawFlagHulls = false;
    drawFlagKeyPoints = false;
    drawFlagEllipses = false;
    
    connect(ui->spinDelta,SIGNAL(valueChanged(int)),this,SLOT(deltaChanged(int)));
    connect(ui->spinMinArea,SIGNAL(valueChanged(int)),this,SLOT(minAreaChanged(int)));
    connect(ui->spinMaxArea,SIGNAL(valueChanged(int)),this,SLOT(maxAreaChanged(int)));
    connect(ui->spinMaxVariation,SIGNAL(valueChanged(double)),this,SLOT(maxVariationChanged(double)));
    connect(ui->spinMinDiversity,SIGNAL(valueChanged(double)),this,SLOT(minDiversityChanged(double)));

    connect(ui->sliderThickness,SIGNAL(valueChanged(int)),this,SLOT(lineThicknessChanged(int)));
    connect(ui->cBDrawKeyPoints,SIGNAL(clicked(bool)),this,SLOT(drawFlagKeyPointsChanged(bool)));
    connect(ui->cBDrawHulls,SIGNAL(clicked(bool)),this,SLOT(drawFlagHullsChanged(bool)));
    connect(ui->cBDrawEllipses,SIGNAL(clicked(bool)),this,SLOT(drawFlagEllipsesChanged(bool)));
}

DialogMSER::~DialogMSER()
{
    delete ui;
}

void DialogMSER::addModell(QStandardItemModel *mdl)
{
    ui->tableView->setModel(mdl);
}

void DialogMSER::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogMSER::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}
void DialogMSER::deltaChanged(int i)
{
    delta = i;
    emit signalDeltaChanged();
}

void DialogMSER::minAreaChanged(int i)
{
    minArea = i;
    emit signalMinAreaChanged();
}

void DialogMSER::maxAreaChanged(int i)
{
    maxArea = i;
    emit signalMaxAreaChanged();
}

void DialogMSER::maxVariationChanged(double d)
{
    maxVariation = d;
    emit signalMaxVariationChanged();
}


void DialogMSER::minDiversityChanged(double d)
{
    minDiversity = d;
    emit signalMinDiversityChanged();
}

void DialogMSER::lineThicknessChanged(int i)
{
    lineThickness = i;
}

void DialogMSER::drawFlagKeyPointsChanged(bool b)
{
    drawFlagKeyPoints = b;
    emit signalDrawFlagKeyPointsChanged( b);
}

void DialogMSER::drawFlagHullsChanged(bool b)
{
    drawFlagHulls = b;
    emit signalDrawFlagHullsChanged(b);
}

void DialogMSER::drawFlagEllipsesChanged(bool b)
{
    drawFlagEllipses = b;
    emit signalDrawFlagEllipsesChanged(b);
}

