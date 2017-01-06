#include "dialogcustomfilter.h"
#include "ui_dialogcustomfilter.h"

DialogCustomFilter::DialogCustomFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCustomFilter)
{
    ui->setupUi(this);
    x = 3;
    y = 3;
    anchorX = 0;
    anchorY = 0;
    delta = 0;
    border = 0;

    connect(ui->sBxX,SIGNAL(valueChanged(int)),SLOT(xIndexChanged(int)));
    connect(ui->sBxY,SIGNAL(valueChanged(int)),SLOT(yIndexChanged(int)));
    connect(ui->sliderAnchorX,SIGNAL(valueChanged(int)),this,SLOT(anchorXChanged(int)));
    connect(ui->sliderAnchorY,SIGNAL(valueChanged(int)),this,SLOT(anchorYChanged(int)));
    connect(ui->sliderDelta,SIGNAL(valueChanged(int)),this,SLOT(deltaChanged(int)));
    connect(ui->cBxBorder,SIGNAL(currentIndexChanged(int)),this,SLOT(borderChanged(int)));

    ui->lE3->setVisible(false);
    ui->lE4->setVisible(false);
    ui->lE5->setVisible(false);
    ui->lE6->setVisible(false);
    ui->lE10->setVisible(false);
    ui->lE11->setVisible(false);
    ui->lE12->setVisible(false);
    ui->lE13->setVisible(false);
    ui->lE17->setVisible(false);
    ui->lE18->setVisible(false);
    ui->lE19->setVisible(false);
    ui->lE20->setVisible(false);
    ui->lE21->setVisible(false);
    ui->lE22->setVisible(false);
    ui->lE23->setVisible(false);
    ui->lE24->setVisible(false);
    ui->lE25->setVisible(false);
    ui->lE26->setVisible(false);
    ui->lE27->setVisible(false);
    ui->lE28->setVisible(false);
    ui->lE29->setVisible(false);
    ui->lE30->setVisible(false);
    ui->lE31->setVisible(false);
    ui->lE32->setVisible(false);
    ui->lE33->setVisible(false);
    ui->lE34->setVisible(false);
    ui->lE35->setVisible(false);
    ui->lE36->setVisible(false);
    ui->lE37->setVisible(false);
    ui->lE38->setVisible(false);
    ui->lE39->setVisible(false);
    ui->lE40->setVisible(false);
    ui->lE41->setVisible(false);
    ui->lE42->setVisible(false);
    ui->lE43->setVisible(false);
    ui->lE44->setVisible(false);
    ui->lE45->setVisible(false);
    ui->lE46->setVisible(false);
    ui->lE47->setVisible(false);
    ui->lE48->setVisible(false);

    QSM = new QSignalMapper(this);
    QSM->setMapping(ui->lE0,0);
    QSM->setMapping(ui->lE1,1);
    QSM->setMapping(ui->lE2,2);
    QSM->setMapping(ui->lE3,3);
    QSM->setMapping(ui->lE4,4);
    QSM->setMapping(ui->lE5,5);
    QSM->setMapping(ui->lE6,6);
    QSM->setMapping(ui->lE7,7);
    QSM->setMapping(ui->lE8,8);
    QSM->setMapping(ui->lE9,9);
    QSM->setMapping(ui->lE10,10);
    QSM->setMapping(ui->lE11,11);
    QSM->setMapping(ui->lE12,12);
    QSM->setMapping(ui->lE13,13);
    QSM->setMapping(ui->lE14,14);
    QSM->setMapping(ui->lE15,15);
    QSM->setMapping(ui->lE16,16);
    QSM->setMapping(ui->lE17,17);
    QSM->setMapping(ui->lE18,18);
    QSM->setMapping(ui->lE19,19);
    QSM->setMapping(ui->lE20,20);
    QSM->setMapping(ui->lE21,21);
    QSM->setMapping(ui->lE22,22);
    QSM->setMapping(ui->lE23,23);
    QSM->setMapping(ui->lE24,24);
    QSM->setMapping(ui->lE25,25);
    QSM->setMapping(ui->lE26,26);
    QSM->setMapping(ui->lE27,27);
    QSM->setMapping(ui->lE28,28);
    QSM->setMapping(ui->lE29,29);
    QSM->setMapping(ui->lE30,30);
    QSM->setMapping(ui->lE31,31);
    QSM->setMapping(ui->lE32,32);
    QSM->setMapping(ui->lE33,33);
    QSM->setMapping(ui->lE34,34);
    QSM->setMapping(ui->lE35,35);
    QSM->setMapping(ui->lE36,36);
    QSM->setMapping(ui->lE37,37);
    QSM->setMapping(ui->lE38,38);
    QSM->setMapping(ui->lE39,39);
    QSM->setMapping(ui->lE40,40);
    QSM->setMapping(ui->lE41,41);
    QSM->setMapping(ui->lE42,42);
    QSM->setMapping(ui->lE43,43);
    QSM->setMapping(ui->lE44,44);
    QSM->setMapping(ui->lE45,45);
    QSM->setMapping(ui->lE46,46);
    QSM->setMapping(ui->lE47,47);
    QSM->setMapping(ui->lE48,48);

    connect(ui->lE0,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE1,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE2,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE3,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE4,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE5,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE6,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE7,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE8,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE9,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE10,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE11,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE12,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE13,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE14,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE15,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE16,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE17,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE18,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE19,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE20,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE21,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE22,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE23,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE24,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE25,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE26,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE27,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE28,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE29,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE30,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE31,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE32,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE33,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE34,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE35,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE36,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE37,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE38,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE39,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE40,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE41,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE42,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE43,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE44,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE45,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE46,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE47,SIGNAL(textEdited(QString)),QSM,SLOT(map()));
    connect(ui->lE48,SIGNAL(textEdited(QString)),QSM,SLOT(map()));

    connect(QSM,SIGNAL(mapped(int)),this,SLOT(textChangingSlot(int)));
}

DialogCustomFilter::~DialogCustomFilter()
{
    delete ui;
}

void DialogCustomFilter::closeEvent(QCloseEvent *)
{
    emit signalXDialog();
}

void DialogCustomFilter::keyPressEvent(QKeyEvent *prEvent)
{
    if(prEvent->key() == Qt::Key_Return)
        emit signalPressReturn();
}

bool DialogCustomFilter::checkString(QString &qstr, int pos)
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
        else if(!str.compare("-") && (n == 1) ){}
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

void DialogCustomFilter::textChangingSlot( int i)
{
    QLineEdit* LE = qobject_cast<QLineEdit*>(QSM->mapping(i));
    QString hstr = LE->text();

    if(!checkString(hstr,LE->cursorPosition()))
    {
        if(hstr.length() == 0)
        {
            return;
        }
        else
        {
            LE->clear();
            LE->setText(hstr);
            return;
        }
    }
}

void DialogCustomFilter::xIndexChanged(int i)
{
    QLineEdit* LE;
    x = i;
    if(i == 3)
    {
        for(int l = 0; l < y; l++)
            for(int h = i + 7*l; h < 7 + 7*l; h++)
            {
                LE = qobject_cast<QLineEdit*>(QSM->mapping(h));
                LE->setVisible(false);
                LE->setText(tr("0"));
            }
    }

    if(i == 5)
    {
        for(int l = 0; l < y; l++)
            for(int h = 7*l; h < 5 + 7*l; h++)
            {
                LE = qobject_cast<QLineEdit*>(QSM->mapping(h));
                LE->setVisible(true);
            }
        for(int l = 0; l < y; l++)
            for(int h = 5 + 7*l; h < 7 + 7*l; h++)
            {
                LE = qobject_cast<QLineEdit*>(QSM->mapping(h));
                LE->setVisible(false);
                LE->setText(tr("0"));
            }
    }

    if(i == 7)
        for(int l = 0; l < y; l++)
            for(int h = 0 + 7*l; h < 7 + 7*l; h++)
            {
                LE = qobject_cast<QLineEdit*>(QSM->mapping(h));
                LE->setVisible(true);
            }

    ui->sliderAnchorX->setMaximum(i-1);
    if(anchorX > i-1)
        ui->sliderAnchorX->setValue(i-1);
}

void DialogCustomFilter::yIndexChanged(int i)
{
    QLineEdit* LE;
    y = i;
    if(i == 3)
    {
        for(int l = 0; l < 4; l++)
            for(int h = 21 + 7*l; h < 28 - (7 - x) + 7*l; h++)
            {
                LE = qobject_cast<QLineEdit*>(QSM->mapping(h));
                LE->setVisible(false);
                LE->setText(tr("0"));
            }
    }

    if(i == 5)
    {
        for(int l = 0; l < 2; l++)
            for(int h = 21 + 7*l; h < 28 - (7 - x) + 7*l; h++)
            {
                LE = qobject_cast<QLineEdit*>(QSM->mapping(h));
                LE->setVisible(true);
            }
        for( int l = 0; l < 2; l++)
            for( int h = 35 + 7*l; h < 42 - (7 - x) + 7*l; h++)
            {
                LE = qobject_cast<QLineEdit*>(QSM->mapping(h));
                LE->setVisible(false);
                LE->setText(tr("0"));
            }
    }
    if(i == 7)
        for( int l = 0; l < 4; l++)
            for( int h = 21 + 7*l; h < 28 - (7 - x) + 7*l; h++)
            {
                LE = qobject_cast<QLineEdit*>(QSM->mapping(h));
                LE->setVisible(true);
            }

    ui->sliderAnchorY->setMaximum(i-1);
    if(anchorY > i-1)
        ui->sliderAnchorY->setValue(i-1);
}

void DialogCustomFilter::anchorXChanged(int i)
{
    anchorX = i;
}

void DialogCustomFilter::anchorYChanged(int i)
{
    anchorY = i;
}

void DialogCustomFilter::deltaChanged(int i)
{
    delta = float(i)/100;
}

void DialogCustomFilter::borderChanged(int i)
{
    border = i;
    if(i == 3)
        border = 4;
}

double* DialogCustomFilter::returnDataPointer()
{
    double* data = new double[y*x];
    QLineEdit* LE;
    for(int l = 0; l < y; l++ )
        for(int h = 0; h < x; h++ )
        {
            LE = qobject_cast<QLineEdit*>(QSM->mapping(h + 7*l));
            data[h + 3*l] = LE->text().toDouble();
        }
    double sum = 0;

    if(ui->cBoxNormalize->isChecked())
    {
        for(int h = 0; h < y*x; h++)
            sum = sum +  sqrt(data[h]*data[h]);
        if(sum != 0)
            for(int h = 0; h < y*x; h++)
                data[h] = data[h]/sum;
    }
    return data;
}
