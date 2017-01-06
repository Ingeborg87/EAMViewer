#include "dialogorb.h"
#include "ui_dialogorb.h"

DialogORB::DialogORB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogORB)
{
    ui->setupUi(this);    

    connect(ui->sliderNFeatures,SIGNAL(valueChanged(int)),SLOT(nFeaturesChanged(int)));
    connect(ui->sBScaleFactor,SIGNAL(valueChanged(double)),this,SLOT(scaleFactorChanged(double)));
    connect(ui->sliderNLevels,SIGNAL(valueChanged(int)),this,SLOT(nLevelsChanged(int)));
    connect(ui->sliderEdgeThreshold,SIGNAL(valueChanged(int)),this,SLOT(edgeThresholdChanged(int)));
    connect(ui->sliderFirstLevel,SIGNAL(valueChanged(int)), this, SLOT(firstLevelChanged(int)));
    connect(ui->sliderPatchSize,SIGNAL(valueChanged(int)),this,SLOT(patchSizeChanged(int)));
    connect(ui->cBDrawKeypoints,SIGNAL(clicked(bool)),this,SLOT(drawKeyPointsFlagChanged(bool)));
    connect(ui->cBFASTKeyPoints, SIGNAL(clicked(bool)), this, SLOT(FASTKeyPointsChanged(bool)));
    connect(ui->cBBRISKKeyPoints, SIGNAL(clicked(bool)), this, SLOT(BRISKKeyPointsChanged(bool)));
}

DialogORB::~DialogORB()
{
    delete ui;
}

void DialogORB::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogORB::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogORB::nFeaturesChanged(int i)
{
    nFeatures = i;
    emit signalNFeaturesChanged();
}

void DialogORB::scaleFactorChanged(double d)
{
    scaleFactor = float(d);
    emit signalScaleFactorChanged();
}

void DialogORB::nLevelsChanged(int i)
{
    nLevels = i;
    emit signalNLevelsChanged();
}

void DialogORB::edgeThresholdChanged(int i)
{
    edgeThreshold = i;
    emit signalEdgeThresholdChanged();
}

void DialogORB::firstLevelChanged(int i)
{
    firstLevel = i;
    emit signalFirstLevelChanged();
}

void DialogORB::patchSizeChanged(int i)
{
    patchSize = i;
    emit signalPatchSizeChanged();
}

void DialogORB::drawKeyPointsFlagChanged(bool b)
{
    drawKeyPointsFlag = b;
    emit signalDrawKeyPointsFlagChanged();
}

void DialogORB::addModel(QStandardItemModel *mdl)
{
    ui->tableView->setModel(mdl);
}

void DialogORB::FASTKeyPointsChanged(bool b)
{
    FASTKeyPoints = b;
    if(b == true)
    {
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

void DialogORB::BRISKKeyPointsChanged(bool b)
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
    }
    emit signalBRISKKeyPointsChanged();
}
