#include "dialogfreak.h"
#include "ui_dialogfreak.h"

DialogFREAK::DialogFREAK(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFREAK)
{
    ui->setupUi(this);
    connect(ui->cBOrientationNormalized, SIGNAL(clicked(bool)),this,SLOT(orientationNormalizedChanged(bool)));
    connect(ui->cBScaleNormalized, SIGNAL(clicked(bool)),this, SLOT(scaleNormalizedChanged(bool)));
    connect(ui->sBPatternScale, SIGNAL(valueChanged(double)), this, SLOT(patternScaleChanged(double)));
    connect(ui->sliderNOctaves, SIGNAL(valueChanged(int)), this, SLOT(nOctavesChanged(int)));
    connect(ui->cBDrawKeyPoints, SIGNAL(clicked(bool)), this, SLOT(drawKeyPointsFlagChanged(bool)));
    connect(ui->cBFASTKeyPoints, SIGNAL(clicked(bool)), this, SLOT(FASTKeyPointsChanged(bool)));
    connect(ui->cBORBKeyPoints, SIGNAL(clicked(bool)), this, SLOT(ORBKeyPointsChanged(bool)));
    connect(ui->cBBRISKKeyPoints, SIGNAL(clicked(bool)), this, SLOT(BRISKKeyPointsChanged(bool)));
}

DialogFREAK::~DialogFREAK()
{
    delete ui;
}

void DialogFREAK::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogFREAK::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogFREAK::orientationNormalizedChanged(bool b)
{
    orientationNormalized = b;
    emit signalOrientationNormalizedChanged();
}

void DialogFREAK::scaleNormalizedChanged(bool b)
{
    scaleNormalized = b;
    emit signalScaleNormalizedChanged();
}

void DialogFREAK::patternScaleChanged(double d)
{
    patternScale = float(d);
    emit signalPatternScaleChanged();
}

void DialogFREAK::nOctavesChanged(int i)
{
    nOctaves = i;
    emit signalNOctavesChanged();
}

void DialogFREAK::drawKeyPointsFlagChanged(bool b)
{
    drawKeyPointsFlag = b;
    emit signalDrawKeyPointsFlagChanged();
}

void DialogFREAK::addModel(QStandardItemModel *mdl)
{
    ui->tableView->setModel(mdl);
}

void DialogFREAK::FASTKeyPointsChanged(bool b)
{
    FASTKeyPoints = b;
    if(b == true)
    {
        if(ORBKeyPoints == true)
        {
            ORBKeyPoints = false;
            disconnect(ui->cBORBKeyPoints, SIGNAL(clicked(bool)), this, SLOT(ORBKeyPointsChanged(bool)));
            ui->cBORBKeyPoints->setChecked(false);
            connect(ui->cBORBKeyPoints, SIGNAL(clicked(bool)), this, SLOT(ORBKeyPointsChanged(bool)));
        }
        if(BRISKKeyPoints == true)
        {
            BRISKKeyPoints = false;
            disconnect(ui->cBBRISKKeyPoints, SIGNAL(clicked(bool)), this, SLOT(BRISKKeyPointsChanged(bool)));
            ui->cBBRISKKeyPoints->setChecked(false);
            connect(ui->cBBRISKKeyPoints, SIGNAL(clicked(bool)), this, SLOT(BRISKKeyPointsChanged(bool)));
        }
    }
    emit signalFASTKeyPointsChanged();
}

void DialogFREAK::ORBKeyPointsChanged(bool b)
{
    ORBKeyPoints = b;
    if(b == true)
    {
        if(FASTKeyPoints == true)
        {
            FASTKeyPoints = false;
            disconnect(ui->cBFASTKeyPoints, SIGNAL(clicked(bool)), this, SLOT(FASTKeyPointsChanged(bool)));
            ui->cBFASTKeyPoints->setChecked(false);
            connect(ui->cBFASTKeyPoints, SIGNAL(clicked(bool)), this, SLOT(FASTKeyPointsChanged(bool)));
        }
        if(BRISKKeyPoints == true)
        {
            BRISKKeyPoints = false;
            disconnect(ui->cBBRISKKeyPoints, SIGNAL(clicked(bool)), this, SLOT(BRISKKeyPointsChanged(bool)));
            ui->cBBRISKKeyPoints->setChecked(false);
            connect(ui->cBBRISKKeyPoints, SIGNAL(clicked(bool)), this, SLOT(BRISKKeyPointsChanged(bool)));
        }
    }
    emit signalORBKeyPointsChanged();
}

void DialogFREAK::BRISKKeyPointsChanged(bool b)
{
    BRISKKeyPoints = b;
    if(b == true)
    {
        if(FASTKeyPoints == true)
        {
            FASTKeyPoints = false;
            disconnect(ui->cBFASTKeyPoints, SIGNAL(clicked(bool)), this, SLOT(FASTKeyPointsChanged(bool)));
            ui->cBFASTKeyPoints->setChecked(false);
            connect(ui->cBFASTKeyPoints, SIGNAL(clicked(bool)), this, SLOT(FASTKeyPointsChanged(bool)));
        }
        if(ORBKeyPoints == true)
        {
            ORBKeyPoints = false;
            disconnect(ui->cBORBKeyPoints, SIGNAL(clicked(bool)), this, SLOT(ORBKeyPointsChanged(bool)));
            ui->cBORBKeyPoints->setChecked(false);
            connect(ui->cBORBKeyPoints, SIGNAL(clicked(bool)), this, SLOT(ORBKeyPointsChanged(bool)));
        }
    }
    emit signalBRISKKeyPointsChanged();
}
