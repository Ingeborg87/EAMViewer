#include "formroidatabase.h"
#include "ui_formroidatabase.h"

FormROIDataBase::FormROIDataBase(QWidget *parent, RoiDbStruct roiStruct) :
    QWidget(parent),
    ui(new Ui::FormROIDataBase)
{
    ui->setupUi(this);
    dbStruct = roiStruct;
    checkedChooseBox = false;
    sceneROI = new QGraphicsScene;
    sceneROICanny = new QGraphicsScene;

    if(dbStruct.linesHough.size() > 0)
        ui->cBLines->setChecked(true);
    if(dbStruct.linesHoughP.size() > 0)
        ui->cBLinesP->setChecked(true);
    if(dbStruct.circlesHough.size() > 0)
        ui->cBCircles->setChecked(true);
    if(dbStruct.corners.size() > 0)
        ui->cBCorners->setChecked(true);
    if(dbStruct.FASTKeyPoints.size() > 0)
        ui->cBFAST->setChecked(true);
    if(dbStruct.BRISKKeyPoints.size() > 0)
        ui->cBBRISK->setChecked(true);
    if(dbStruct.ORBKeyPoints.size() > 0)
        ui->cBORB->setChecked(true);
    if(dbStruct.FREAKKeyPoints.size() > 0)
        ui->cBFREAK->setChecked(true);
    if(dbStruct.MSERPoints.size() > 0)
        ui->cBMSER->setChecked(true);

    ui->label->setText(dbStruct.name);

    ui->gVROI->setScene(sceneROI);
    sceneROI->addPixmap(QPixmap::fromImage(matToQImage(dbStruct.RoiImg)));
    connect(ui->gVROI,SIGNAL(mouseDoubleClicked()),this,SIGNAL(doubleClicked()));
    connect(ui->cBChoose, SIGNAL(clicked(bool)), this, SLOT(checkChooseBox(bool)));
}

FormROIDataBase::~FormROIDataBase()
{
    delete ui;
    delete sceneROI;
    delete sceneROICanny;
}

QImage FormROIDataBase::matToQImage(Mat &mat )
{
    if(mat.channels() == 1)
    {
        const uchar *qImageBuffer = (const uchar*)mat.data;
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        return img;
    }
    if(mat.channels() == 3)
    {
        const uchar *qImageBuffer = (const uchar*)mat.data;
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    return QImage();
}

void FormROIDataBase::checkChooseBox(bool b)
{
    checkedChooseBox = b;
}
