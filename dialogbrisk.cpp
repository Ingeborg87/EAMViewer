#include "dialogbrisk.h"
#include "ui_dialogbrisk.h"

DialogBRISK::DialogBRISK(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBRISK)
{
    ui->setupUi(this);
    connect(ui->sliderThresh, SIGNAL(valueChanged(int)), this, SLOT(threshChanged(int)));
    connect(ui->sliderOctaves, SIGNAL(valueChanged(int)),this,SLOT(octavesChanged(int)));
    connect(ui->sBPatternScale, SIGNAL(valueChanged(double)),this,SLOT(patternScaleChanged(double)));
    connect(ui->cBDrawKeyPoints,SIGNAL(clicked(bool)),this,SLOT(drawKeyPointsFlagChanged(bool)));
    connect(ui->cBFASTKeyPoints, SIGNAL(clicked(bool)), this, SLOT(FASTKeyPointsChanged(bool)));
    connect(ui->cBORBKeyPoints, SIGNAL(clicked(bool)), this, SLOT(ORBKeyPointsChanged(bool)));
}

DialogBRISK::~DialogBRISK()
{
    delete ui;
}

void DialogBRISK::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogBRISK::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogBRISK::threshChanged(int i)
{
    thresh = i;
    emit signalsThreshChanged();
}

void DialogBRISK::octavesChanged(int i)
{
    octaves = i;
    emit signalsOctavesChanged();
}

void DialogBRISK::patternScaleChanged(double d)
{
    patternScale = float(d);
    emit signalsPatternScaleChanged();
}

void DialogBRISK::drawKeyPointsFlagChanged(bool b)
{
    drawKeyPointsFlag = b;
    emit signalDrawKeyPointsFlagChanged();
}

void DialogBRISK::addModel(QStandardItemModel *mdl)
{
    ui->tableView->setModel(mdl);
}

void DialogBRISK::FASTKeyPointsChanged(bool b)
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
    }
    emit signalFASTKeyPointsChanged();
}

void DialogBRISK::ORBKeyPointsChanged(bool b)
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
    }
    emit signalORBKeyPointsChanged();
}
