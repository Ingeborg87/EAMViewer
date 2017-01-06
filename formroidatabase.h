#ifndef FORMROIDATABASE_H
#define FORMROIDATABASE_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QPixmap>
#include <QGraphicsScene>

using namespace std;
using namespace cv;

namespace Ui {
class FormROIDataBase;
}


struct RoiDbStruct
{
    QString name;
    Mat RoiImg;
    vector<Vec2f> linesHough;
    vector<Vec2i> corners;
    vector<Vec3f> circlesHough;
    vector<Vec4i> linesHoughP;
    vector< vector< Point> > MSERPoints;
    vector<KeyPoint> FASTKeyPoints;
    Mat ORBDescriptors;
    vector<KeyPoint>  ORBKeyPoints;
    Mat BRISKDescriptors;
    vector<KeyPoint>  BRISKKeyPoints;
    Mat FREAKDescriptors;
    vector<KeyPoint>  FREAKKeyPoints;
};

class FormROIDataBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormROIDataBase( QWidget *parent = 0, RoiDbStruct roisStruct = RoiDbStruct());
    ~FormROIDataBase();
    QGraphicsScene* sceneROI;
    QGraphicsScene* sceneROICanny;
    RoiDbStruct dbStruct;
    bool checkedChooseBox;
private:

    QImage matToQImage(Mat &mat);
    Ui::FormROIDataBase *ui;
private slots:
    void checkChooseBox(bool b);
signals:
    void doubleClicked();
};

#endif // FORMROIDATABASE_H
