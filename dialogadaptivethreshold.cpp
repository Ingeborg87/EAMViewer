#include "dialogadaptivethreshold.h"
#include "ui_dialogadaptivethreshold.h"

DialogAdaptiveThreshold::DialogAdaptiveThreshold(QWidget *parent):QDialog(parent),ui(new Ui::DialogAdaptiveThreshold)
{
    ui->setupUi(this);
    sliderValueMaximum = ui->sliderMaximum->value();
    sliderValueBlocksize = ui->sliderBlocksize->value();
    sliderValueC = ui->sliderC->value();
    comboboxIndexMethod = 0;
    comboboxIndexType = 0;

    connect(ui->sliderC,SIGNAL(sliderMoved(int)),this,SLOT(sliderCChanged(int)));
    connect(ui->sliderBlocksize,SIGNAL(sliderMoved(int)),this,SLOT(sliderBlSizeChanged(int)));
    connect(ui->sliderMaximum,SIGNAL(sliderMoved(int)),this,SLOT(sliderMaxChanged(int)));
    connect(ui->comboBoxMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(comboboxIndexMethodChanged(int)));
    connect(ui->comboBoxType,SIGNAL(currentIndexChanged(int)),this,SLOT(comboboxIndexTypeChanged(int)));
}

DialogAdaptiveThreshold::~DialogAdaptiveThreshold()
{
    delete ui;
}

void DialogAdaptiveThreshold::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogAdaptiveThreshold::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogAdaptiveThreshold::sliderMaxChanged(int i)
{
    sliderValueMaximum = i;
    emit signalMaximumChanged();
}

void DialogAdaptiveThreshold::sliderBlSizeChanged(int i)
{
    if( i%2 == 0)
    {
        sliderValueBlocksize = i - 1;
        ui->sliderBlocksize->setValue(sliderValueBlocksize);
    }
    else
        sliderValueBlocksize = i;

    emit signalBlSizeChanged();
}

void DialogAdaptiveThreshold::sliderCChanged(int i)
{
    sliderValueC = i;
    emit signalCChanged();
}

void DialogAdaptiveThreshold::comboboxIndexMethodChanged(int i)
{
    comboboxIndexMethod = i;
    emit signalIndexMethodChanged();
}

void DialogAdaptiveThreshold::comboboxIndexTypeChanged(int i)
{
    comboboxIndexType = i;
    emit signalIndexTypeChanged();
}
