#include "dialogevalmser.h"
#include "ui_dialogevalmser.h"

DialogEvalMSER::DialogEvalMSER(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEvalMSER)
{
    ui->setupUi(this);
    connect(ui->cBSortBySize, SIGNAL(clicked(bool)), this, SLOT(sortBySizeChanged(bool)));
    connect(ui->cBSortByHull, SIGNAL(clicked(bool)), this, SLOT(sortByHullChanged(bool)));
    connect(ui->sliderMin, SIGNAL(valueChanged(int)), this, SLOT(minSizeChanged(int)));
    connect(ui->sliderMax, SIGNAL(valueChanged(int)), this, SLOT(maxSizeChanged(int)));
    connect(ui->sliderMinRatio, SIGNAL(valueChanged(int)), this, SLOT(minRatioChanged(int)));
    connect(ui->sliderMaxRatio, SIGNAL(valueChanged(int)), this, SLOT(maxRatioChanged(int)));
    connect(ui->sliderThickness, SIGNAL(valueChanged(int)), this, SLOT(thicknessChanged(int)));
    connect(ui->cBDrawKeyPoints, SIGNAL(clicked(bool)), this, SLOT(drawKeyPointsFlagChanged(bool)));
    connect(ui->cBDrawHulls, SIGNAL(clicked(bool)), this, SLOT(drawHullsFlagChanged(bool)));
    connect(ui->cBDrawEllipses, SIGNAL(clicked(bool)), this, SLOT(drawEllipsesFlagChanged(bool)));
    connect(ui->pBSaveData, SIGNAL(clicked()), this, SLOT(pBSaveDataPushed()));
}


void DialogEvalMSER::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogEvalMSER::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogEvalMSER::sortBySizeChanged(bool b)
{
    sortBySize = b;
    emit signalSortBySizeChanged();
}

void DialogEvalMSER::sortByHullChanged(bool b)
{
    sortByHull = b;
    emit signalSortByHullChanged();
}

void DialogEvalMSER::minSizeChanged(int i)
{
    if(i >= ui->sliderMax->value())
        ui->sliderMin->setSliderPosition(ui->sliderMax->value() -1);
    minSize = float(ui->sliderMin->value())/1000;
    emit signalMinSizeChanged();
}

void DialogEvalMSER::maxSizeChanged(int i)
{
    if(i-1 <= ui->sliderMin->value())
        ui->sliderMax->setSliderPosition(ui->sliderMin->value());
    maxSize = float(ui->sliderMax->value()-1)/1000;
    emit signalMaxSizeChanged();
}

void DialogEvalMSER::minRatioChanged(int i)
{
    if(i >= ui->sliderMaxRatio->value())
        ui->sliderMinRatio->setSliderPosition(ui->sliderMaxRatio->value() -1);
    minRatio = float(ui->sliderMinRatio->value())/1000;
    emit signalMinRatioChanged();
}

void DialogEvalMSER::maxRatioChanged(int i)
{
    if(i-1 <= ui->sliderMinRatio->value())
        ui->sliderMaxRatio->setSliderPosition(ui->sliderMinRatio->value());
    maxRatio = float(ui->sliderMaxRatio->value()-1)/1000;
    emit signalMaxRatioChanged();
}

void DialogEvalMSER::thicknessChanged(int i)
{
    thickness = i;
}

DialogEvalMSER::~DialogEvalMSER()
{
    delete ui;
}

void DialogEvalMSER::addModel(QStandardItemModel *mdl)
{
    ui->tableView->setModel(mdl);
}

void DialogEvalMSER::drawKeyPointsFlagChanged(bool b)
{
    drawFlagKeyPoints = b;
    emit signalDrawKeyPointsFlagChanged();
}

void DialogEvalMSER::drawHullsFlagChanged(bool b)
{
    drawFlagHulls = b;
    emit signalDrawFlagHullsChanged();
}

void DialogEvalMSER::drawEllipsesFlagChanged(bool b)
{
    drawFlagEllipses = b;
    emit signalDrawFlagEllipsesChanged();
}

void DialogEvalMSER::pBSaveDataPushed()
{
    emit signalPBSaveDataPushed();
}
