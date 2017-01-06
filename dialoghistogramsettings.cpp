#include "dialoghistogramsettings.h"
#include "ui_dialoghistogramsettings.h"

DialogHistogramSettings::DialogHistogramSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHistogramSettings)
{
    widgetindex = 0;
    ui->setupUi(this);
    connect(ui->checkBoxHistoEq,SIGNAL(clicked(bool)),this,SLOT(slotHistogramEqualization(bool)));
    connect(ui->checkBoxInv,SIGNAL(clicked(bool)),this,SLOT(slotInversion(bool)));
    connect(ui->horizontalSliderGammaTrans,SIGNAL(sliderReleased()),this,SLOT(slotGammaTransformation()));
    connect(ui->horizontalSliderLinTrans,SIGNAL(sliderReleased()),this,SLOT(slotLinearTransformation()));
}

DialogHistogramSettings::~DialogHistogramSettings()
{
    delete ui;
}

void DialogHistogramSettings::slotGammaTransformation()
{
    widgetindex = 1;
    sliderValueGamma = ui->horizontalSliderGammaTrans->value();
    emit signalGammaTransformation();
}

void DialogHistogramSettings::slotHistogramEqualization(bool b)
{
    widgetindex = 2;
    emit signalHistogramEqualization(b);
}

void DialogHistogramSettings::slotInversion(bool b)
{
    widgetindex = 3;
    emit signalInversion(b);
}

void DialogHistogramSettings::slotLinearTransformation()
{
    widgetindex = 4;
    sliderValueLinear = ui->horizontalSliderLinTrans->value();
    emit signalLinearTransformation();
}

void DialogHistogramSettings::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogHistogramSettings::keyPressEvent(QKeyEvent* prEvent)
{
    if( prEvent->key() == Qt::Key_Return)
    {
        if(widgetindex == 2)
            if(!ui->checkBoxHistoEq->isChecked())
                return;
        else if(widgetindex == 3)
            if(!ui->checkBoxInv->isChecked())
                return;
        ui->horizontalSliderGammaTrans->setValue(0);
        ui->checkBoxHistoEq->setChecked(false);
        ui->checkBoxInv->setChecked(false);
        ui->horizontalSliderLinTrans->setValue(0);
        emit signalPressReturn();
    }
}
