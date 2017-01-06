#include "dialogmedianblur.h"
#include "ui_dialogmedianblur.h"
#define test std::cout << "test" << std :: endl;

DialogMedianBlur::DialogMedianBlur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMedianBlur)
{
    sliderValueMedianSize = 1;
    ui->setupUi(this);
    K = 0;
    connect(ui->sliderMedianSize,SIGNAL(sliderMoved(int)),this,SLOT(medianSizeChanged(int)));
}

DialogMedianBlur::~DialogMedianBlur()
{
    delete ui;
}

void DialogMedianBlur::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogMedianBlur::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

void DialogMedianBlur::medianSizeChanged(int i)
{
    sliderValueMedianSize = i;
    if(i%2 == 0)
    {
        i--;
        ui->sliderMedianSize->setValue(i);
    }
    emit signalMedianSizeChanged();
}

void DialogMedianBlur::showSlot()
{
    ui->sliderMedianSize->setMaximum(K/10);
}
