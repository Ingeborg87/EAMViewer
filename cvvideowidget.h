#ifndef CVVIDEOWIDGET_H
#define CVVIDEOWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtCore>
#include <QTimer>
#include <QImage>
#include <eamviewer.h>




class EAMViewer;
using namespace cv;
namespace Ui {
class CVVideoWidget;
}

class CVVideoWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CVVideoWidget(int dev = 0, float fps = 33,QWidget *parent = 0);
    ~CVVideoWidget();
    Mat vidImg;
    Mat vidProc;
    QImage qImg;
    QImage qProc;
    VideoCapture camDev;
    QTimer* timer;
    QString warning;
    QString returnWarning();
    Mat returnCurrentVideoFrame();

    
private:
    bool recordFlag;
    float framesPS;
    Ui::CVVideoWidget *ui;



private slots:
    void chooseCurrentFrame();
    void FPSChanged(int i);
    void grabAndProcessFrame();
    void IndexCbxShowingFramesChanged(int i);
    void startStopGrabbingAndShowing();
    void startStopRecordingMovie();
signals:
    void warningError();
    void loadCurrentVideoFrame();
};

#endif // CVVIDEOWIDGET_H
