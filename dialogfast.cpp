#include "dialogfast.h"
#include "ui_dialogfast.h"

DialogFAST::DialogFAST(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFAST)
{
    ui->setupUi(this);
    threshold = 5;
    NMS = false;
    type = 2;
    drawKeyPointsFlag = false;

    connect(ui->sliderThreshold, SIGNAL(sliderMoved(int)),this, SLOT(thresholdChanged(int)));
    connect(ui->cBNMS, SIGNAL(clicked(bool)),this, SLOT(NMSChanged(bool)));
    connect(ui->cBxType,SIGNAL(currentIndexChanged(int)),this,SLOT(typeChanged(int)));
    connect(ui->cBDrawKeyPoints,SIGNAL(clicked(bool)),this,SLOT(drawKeyPointsFlagChanged(bool)));
}

DialogFAST::~DialogFAST()
{
    delete ui;
}

void DialogFAST::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogFAST::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogFAST::drawKeyPointsFlagChanged(bool b)
{
    drawKeyPointsFlag = b;
    emit signalDrawKeyPointsFlagChanged();
}

void DialogFAST::thresholdChanged(int i)
{
    threshold = i;
    emit signalThresholdChanged();
}

void DialogFAST::NMSChanged(bool b)
{
    NMS = b;
    emit signalNMSChanged();
}

void DialogFAST::typeChanged(int i)
{
    type = i;
    if(i == 0)
        type = 2;
    if(i == 2)
        type = 0;
    emit signalTypeChanged();
}

void DialogFAST::addModel(QStandardItemModel *mdl)
{
    ui->tableView->setModel(mdl);
}
