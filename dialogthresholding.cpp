#include "dialogthresholding.h"
#include "ui_dialogthresholding.h"

DialogThresholding::DialogThresholding(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogThresholding)
{
    ui->setupUi(this);
    comboIndex = 0;
    sliderValueThreshold = 128;
    sliderValueMaximum = 255;
    connect(ui->horizontalSliderThreshold,SIGNAL(sliderMoved(int)),this,SLOT(sliderThreshChanged()));
    connect(ui->horizontalSliderMaximum,SIGNAL(sliderMoved(int)),this,SLOT(sliderMaxChanged()));
    connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(checkStateChanged(int)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(comboIndexChanged(int)));
}

DialogThresholding::~DialogThresholding()
{
    delete ui;
}

void DialogThresholding::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogThresholding::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogThresholding::sliderThreshChanged()
{
    sliderValueThreshold = ui->horizontalSliderThreshold->value();
    sliderValueMaximum   = ui->horizontalSliderMaximum->value();
    if(sliderValueThreshold > sliderValueMaximum)
        ui->horizontalSliderMaximum->setValue(sliderValueThreshold);
    emit signalThreshChanged();
}

void DialogThresholding::sliderMaxChanged()
{
    sliderValueThreshold = ui->horizontalSliderThreshold->value();
    sliderValueMaximum   = ui->horizontalSliderMaximum->value();
    if(sliderValueMaximum < sliderValueThreshold)
        ui->horizontalSliderThreshold->setValue(sliderValueMaximum);
    emit signalMaxChanged();
}

void DialogThresholding::checkStateChanged(int i)
{
    chbxState = i;
    emit signalCheckStateChanged();
}

void DialogThresholding::comboIndexChanged(int i)
{
    comboIndex = i;
    emit signalComboIndexChanged();
}
