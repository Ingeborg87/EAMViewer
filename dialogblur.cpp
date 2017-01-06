#include "dialogblur.h"
#include "ui_dialogblur.h"
#define test std::cout << "test" << std :: endl;

DialogBlur::DialogBlur(QWidget *parent):QDialog(parent),ui(new Ui::DialogBlur)
{
    ui->setupUi(this);
    sliderValueSizeX = 3;
    sliderValueSizeY = 3;
    sliderValueAnchorX = 0;
    sliderValueAnchorY = 0;
    X = 0;
    Y = 0;
    cbxIndex = 0;
    connect(ui->sliderSizeX,SIGNAL(sliderMoved(int)),this,SLOT(sizeXChanged(int)));
    connect(ui->sliderSizeY,SIGNAL(sliderMoved(int)),this,SLOT(sizeYChanged(int)));
    connect(ui->sliderAnchorX,SIGNAL(sliderMoved(int)),this,SLOT(anchorXChanged(int)));
    connect(ui->sliderAnchorY,SIGNAL(sliderMoved(int)),this,SLOT(anchorYChanged(int)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(cbxIndexChanged(int)));
}

DialogBlur::~DialogBlur()
{
    delete ui;
}

void DialogBlur::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogBlur::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogBlur::sizeXChanged(int i)
{
    sliderValueSizeX = i;
    if(sliderValueSizeX < sliderValueAnchorX)
    {
        sliderValueAnchorX = sliderValueSizeX - 1;
        ui->sliderAnchorX->setValue(sliderValueAnchorX);
    }
    emit signalSizeXChanged();
}

void DialogBlur::sizeYChanged(int i)
{
    sliderValueSizeY = i;
    if(sliderValueSizeY <= sliderValueAnchorY)
    {
        sliderValueAnchorY = sliderValueSizeY - 1;
        ui->sliderAnchorY->setValue(sliderValueAnchorY);
    }
    signalSizeYChanged();
}

void DialogBlur::cbxIndexChanged(int i)
{
    cbxIndex = i;
    if(i==3)
        cbxIndex = 4;
    emit signalCbxIndexChanged();

}

void DialogBlur::showSlot()
{
    ui->sliderSizeX->setMaximum(X/4);
    ui->sliderSizeY->setMaximum(Y/4);
    ui->sliderAnchorX->setMaximum(X/4 - 1);
    ui->sliderAnchorY->setMaximum(Y/4 - 1);
}

void DialogBlur::anchorXChanged(int i)
{
    sliderValueAnchorX = i;
    if(sliderValueSizeX < sliderValueAnchorX)
    {
        sliderValueAnchorX = sliderValueSizeX - 1;
        ui->sliderAnchorX->setValue(sliderValueAnchorX);
    }
    emit signalAnchorXChanged();
}

void DialogBlur::anchorYChanged(int i)
{
    sliderValueAnchorY = i;
    if(sliderValueSizeY <= sliderValueAnchorY)
    {
        sliderValueAnchorY = sliderValueSizeY - 1;
        ui->sliderAnchorY->setValue(sliderValueAnchorY);
    }
    emit signalAnchorYChanged();
}

/*
void DialogBlur::sizeYChanged(QString qstr)
{
    if(!checkString(qstr,ui->lineEditSizeY->cursorPosition()))
    {
        if(qstr.length() == 0)
        {
            return;
        }
        else
        {
            ui->lineEditSizeY->clear();
            ui->lineEditSizeY->setText(qstr);
            return;
        }
    }
    sizeY = qstr.toInt();
    if(sizeY < 3)
        sizeY = 3;
}

bool DialogBlur::checkString(QString &qstr, int pos)
{
    int n = qstr.length();
    if(n != 0)
    {
        string str = qstr.toStdString().substr(pos-1);

        if(!str.compare("0")){}
        else if(!str.compare("1")){}
        else if(!str.compare("2")){}
        else if(!str.compare("3")){}
        else if(!str.compare("4")){}
        else if(!str.compare("5")){}
        else if(!str.compare("6")){}
        else if(!str.compare("7")){}
        else if(!str.compare("8")){}
        else if(!str.compare("9")){}
        else
        {
            qstr.remove(pos-1,1);
            return false;
        }
        return true;
    }
    else
        return false;
}
*/
