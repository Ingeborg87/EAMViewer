#include "cvvideowidget.h"
#include "ui_cvvideowidget.h"

CVVideoWidget::CVVideoWidget(int dev,float fps, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CVVideoWidget)
{
    ui->setupUi(this);
    camDev.open(dev);
    timer =  new QTimer(this);
    if(camDev.isOpened() == false)
    {
        warning = tr("No device found!");
        emit warningError();
    }
    recordFlag = 0;
    connect(timer,SIGNAL(timeout()),this,SLOT(grabAndProcessFrame()));
    connect(ui->pbPlay,SIGNAL(clicked()),this,SLOT(startStopGrabbingAndShowing()));
    connect(ui->pbRecord,SIGNAL(clicked()),this,SLOT(startStopRecordingMovie()));
    connect(ui->pbChooseFrame,SIGNAL(clicked()),this,SLOT(chooseCurrentFrame()));
    connect(ui->sliderFPS,SIGNAL(sliderMoved(int)),this,SLOT(FPSChanged(int)));
    connect(ui->cbxShowingFrames,SIGNAL(currentIndexChanged(int)),this,SLOT(IndexCbxShowingFramesChanged(int)));
    grabAndProcessFrame();
    framesPS = fps;
    timer->start(int(1000/fps));
    ui->lblFPS->setText(tr("fps: ") + QString::number(fps) + tr("/s"));
    ui->sliderFPS->setValue(int(fps));
    ui->pbPlay->setText(tr("II"));
    startStopGrabbingAndShowing();
}

CVVideoWidget::~CVVideoWidget()
{
    delete ui;
    timer->stop();
    delete timer;
}

//////////////////////////////////////////////////////////////////////////

void CVVideoWidget::grabAndProcessFrame()
{
    camDev.read(vidImg);
    if(vidImg.empty() == true)
    {
        warning = tr("No data from device");
        timer->stop();
        ui->pbPlay->setText(tr(">"));
        return;
    }

    vidProc = vidImg.clone();
    Mat showMat = vidImg.clone();
    if(showMat.channels() > 1)
    {
        cvtColor(showMat,showMat,CV_BGR2RGB);
        qImg = QImage((uchar*)showMat.data,showMat.cols,showMat.rows,showMat.step,QImage::Format_RGB888);
    }
    else if(showMat.channels() == 1)
        qImg = QImage((uchar*)showMat.data,showMat.cols,showMat.rows,showMat.step,QImage::Format_Indexed8);
    ui->lblOrig->setPixmap(QPixmap::fromImage(qImg));

    showMat = vidProc.clone();
    if(showMat.channels() > 1)
    {
        cvtColor(showMat,showMat,CV_BGR2RGB);
        qProc = QImage((uchar*)showMat.data,showMat.cols,showMat.rows,showMat.step,QImage::Format_RGB888);
    }
    else if(showMat.channels() == 1)
        qProc = QImage((uchar*)showMat.data,showMat.cols,showMat.rows,showMat.step,QImage::Format_Indexed8);
    ui->lblProc->setPixmap(QPixmap::fromImage(qProc));

}

void CVVideoWidget::startStopGrabbingAndShowing()
{
    if(timer->isActive() == true)
    {
        timer->stop();
        ui->pbPlay->setText(tr(">"));

    }
    else if(timer->isActive() == false)
    {
        timer->start(int(1000/framesPS));
        ui->pbPlay->setText(tr("II"));
    }
}

void CVVideoWidget::startStopRecordingMovie()
{
    if(timer->isActive() == true)
    {
        recordFlag = !recordFlag;
        if(recordFlag == true)
        {
            ui->pbRecord->setText(tr("stop record"));
        }
        if(recordFlag == false)
        {
            ui->pbRecord->setText(tr("record"));
        }
    }
}

void CVVideoWidget::chooseCurrentFrame()
{
    emit loadCurrentVideoFrame();
}

void CVVideoWidget::IndexCbxShowingFramesChanged(int i)
{
    if(i == 0)
    {
           ui->lblOrig->setVisible(true);
           ui->lblProc->setVisible(true);
    }
    else if(i == 1)
    {

        ui->lblOrig->setVisible(true);
        ui->lblProc->setVisible(false);
    }
    else if(i == 2)
    {
        ui->lblOrig->setVisible(false);
        ui->lblProc->setVisible(true);
    }
}

void CVVideoWidget::FPSChanged(int i)
{
    framesPS = float(i);
    timer->stop();
    timer->start(int(1000/framesPS));
    ui->lblFPS->setText(tr("fps: ") + QString::number(framesPS) + tr(" 1/s"));
}

QString CVVideoWidget::returnWarning()
{
    return warning;
}

Mat CVVideoWidget::returnCurrentVideoFrame()
{
    return vidProc;
}
