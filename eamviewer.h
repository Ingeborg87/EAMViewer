#ifndef EAMVIEWER_H
#define EAMVIEWER_H

// TM = template matching //
#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/video/background_segm.hpp>
#include <boost/dynamic_bitset.hpp>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <QResizeEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QGroupBox>
#include <QVBoxLayout>
#include <iostream>
#include <fstream>
#include <QSignalMapper>
#include <eventsqgraphicsview.h>
#include <dialoglineartransformation.h>
#include <dialoggammatransformation.h>
#include <dialogthresholding.h>
#include <dialogadaptivethreshold.h>
#include <dialogblur.h>
#include <dialogmedianblur.h>
#include <dialoggaussian.h>
#include <dialogsobel.h>
#include <dialogdilation.h>
#include <dialogerode.h>
#include <dialogmorphologyex.h>
#include <dialogcustomfilter.h>
#include <dialoglaplacian.h>
#include <dialogscharr.h>
#include <dialogcanny.h>
#include <dialoghoughlines.h>
#include <dialogmser.h>
#include <dialogfast.h>
#include <dialogorb.h>
#include <dialogbrisk.h>
#include <dialogfreak.h>
#include <dialogevalmser.h>
#include <deque>
#include <formroidatabase.h>
#include <QStandardItemModel>
#include <QStandardItem>
#include <dialoghoughcircles.h>
#include <dialogcornerdetection.h>
#include <QLabel>
#include <QListWidget>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <time.h>
#include <thread>
#include <QDateTime>
#include <NaturalMergeSorter.h>

#define test  cout << "test" << endl;
#define test1 cout << "test1" << endl;
#define test2 cout << "test2" << endl;
#define test3 cout << "test3" << endl;
#define test4 cout << "test4" << endl;
#define test5 cout << "test5" << endl;
#define test6 cout << "test6" << endl;
#define test7 cout << "test7" << endl;
#define test8 cout << "test8" << endl;
#define test9 cout << "test9" << endl;

#define lines cout << endl;
#define HARRIS 0
#define SHITOMASI 1
#define ROIIMG 9
#define ROIHIST 10


using namespace std;
using namespace cv;


struct RoiEventStruct
{
    Mat img;
    Mat imgDraw;
    Mat roi;
    Rect rec;
    Mat bgModel,fgModel;
    bool draw;
    bool drawnFlag;
    bool foreGroundFlag;
    bool backGroundFlag;
    bool initGCwithRect;
    Mat gCMask;
};

namespace Ui
{
    class EAMViewer;
}

class EAMViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit EAMViewer(QWidget *parent = 0);
    ~EAMViewer();
    /// *** methods and template methods for the GUI working and QT4 - OpenCV interaction for single image processing *** ///
    Mat calculatehistogram(Mat in);
    void calculateEllipses(vector<vector<Point> > &BlobPoints, vector<vector<Point> > &HullPoints, vector<RotatedRect> &BlobEllipses);
    void calculateHulls(vector<vector<Point> > &BlobPoints, vector<vector<Point> > &BlobHulls);
    void clearROI();
    void clearScenes();
    void clearTMData();
    void closeAllDialogs();
    void deleteScenes();
    void disableTabChanging(int i);
    void drawBlobEllipses(vector<RotatedRect> &BlobEllipses, int thickness);
    void drawBlobHulls(vector<vector<Point> > &blobs, int thickness);
    void drawBlobPoints(vector<vector<Point> > &blobs, int thickness);
    void drawKeyPoints(vector<KeyPoint> &keyPoints);
    void drawLines(vector<Vec2f> &Lines);
    void drawLines(vector<Vec4i> &Lines);
    void enableTabChanging();
    void evaluateMSERData();
    void fillDataInModel(QStandardItemModel* mdl, unsigned int maxLength = 0);
    void loadImages(int n);
    void loadPixmaps();    
    void loadVideoInBuffer();
    bool loadVideoSize();
    void loadVideoUntilFramePos();
    QImage matToQImage(Mat &mat);
    void newLineInText(QString text);
    void nextPic();
    void previousPic();
    void refreshCornersTbldata(vector<Vec2i> &corn);
    void refreshHoughCirclesTbldata(vector<Vec3f> &cHough);
    void refreshHoughLinesTbldata(vector<Vec2f> &lHough);
    void refreshHoughLinesPTbldata(vector<Vec4i> &lHoughP);
    void refreshTblFASTKeyPoints(vector<KeyPoint> &keyPoints);
    void refreshTblFREAKKeyPoints(vector<KeyPoint> &keyPoints);
    void refreshTblMSERPoints(vector<vector<Point> > &blobs);
    void refreshTblMSEREvalPoints(vector<vector<Point> > &blobs);
    void refreshTblORBKeyPoints(vector<KeyPoint> &keyPoints);
    void refreshTblBRISKKeyPoints(vector<KeyPoint> &keyPoints);
    void releaseVideo();
    void removeMSERDataOutOfIntervall();
    void removeMSERDataOutOfRatioIntervall();
    void removeEdgePoints(vector<Point> &Points);
    void removeEdgePoints(vector<vector<Point> > &blobs);
    void resetSinglePic(Mat img, int i);
    void resizeEvent(QResizeEvent *);
    void sortEvalMSERDataByHulls();
    void sortEvalMSERDataBySize();
    void showTMData(Mat &result, int i);
    static void mouseEvent(int event, int x, int y, int flag, void* param)
    {
        RoiEventStruct* RES = static_cast<RoiEventStruct*>(param);
        if(RES->drawnFlag == false)
        {
            if(event == CV_EVENT_MOUSEMOVE)
                if( RES->draw  == true)
                {
                    RES->rec.width = x-RES->rec.x;
                    RES->rec.height = y-RES->rec.y;
                }

            if(event == CV_EVENT_LBUTTONDOWN)
            {
                RES->draw = true;
                RES->rec = Rect( x, y, 0, 0 );
            }
            if(event == CV_EVENT_LBUTTONUP)
            {
                RES->draw = false;
                if( RES->rec.width < 0 )
                {
                    RES->rec.x += RES->rec.width;
                    RES->rec.width *= -1;
                }
                if( RES->rec.height < 0 )
                {
                    RES->rec.y += RES->rec.height;
                    RES->rec.height *= -1;
                }
            }
            if(RES->draw == true)
            {
                Mat img = RES->img.clone();
                rectangle(img,RES->rec,Scalar(0,0,255),3);
                imshow("select ROI",img);
            }
        }
        if(RES->drawnFlag == true)
        {
            if(event == CV_EVENT_MOUSEMOVE)
            {
                if(RES->foreGroundFlag == true)
                {
                    circle( RES->imgDraw, Point(x,y), 3, Scalar(255,255,255), -1);
                    circle( RES->gCMask, Point( RES->rec.x + x, RES->rec.y + y), 3, GC_FGD, -1);
                    imshow("get the foreground in ROI" ,RES->imgDraw);
                }
                if((RES->backGroundFlag == true) & (flag == 9))
                {
                    circle( RES->imgDraw, Point(x,y), 3, Scalar(0,0,0), -1);
                    circle( RES->gCMask, Point( RES->rec.x + x, RES->rec.y + y), 3, GC_BGD, -1);
                    imshow("get the foreground in ROI",RES->imgDraw);
                }
            }

            if(event == CV_EVENT_LBUTTONDOWN)
            {
                RES->foreGroundFlag = true;
                circle( RES->imgDraw, Point(x,y), 3, Scalar(255,255,255), -1);
                circle( RES->gCMask, Point( RES->rec.x + x, RES->rec.y + y), 3, GC_FGD, -1);
                imshow("get the foreground in ROI",RES->imgDraw);
            }

            if(event == CV_EVENT_LBUTTONUP)
                RES->foreGroundFlag = false;

            if(flag == EVENT_FLAG_SHIFTKEY + CV_EVENT_LBUTTONDOWN)
            {
                RES->backGroundFlag = true;
                circle( RES->imgDraw, Point(x,y), 3, Scalar(0, 0, 0), -1);
                circle( RES->gCMask, Point( RES->rec.x + x, RES->rec.y + y), 3, GC_BGD, -1);
                imshow("get the foreground in ROI",RES->imgDraw);
            }

            if(flag == EVENT_FLAG_SHIFTKEY + CV_EVENT_LBUTTONUP)
                RES->backGroundFlag = false;

            if(flag == EVENT_FLAG_CTRLKEY + CV_EVENT_LBUTTONDOWN)
            {
                if(RES->initGCwithRect == false)
                    grabCut( RES->img, RES->gCMask, RES->rec, RES->bgModel, RES->fgModel, 1, GC_INIT_WITH_RECT);
                if(RES->initGCwithRect == true)
                    grabCut( RES->img, RES->gCMask, RES->rec, RES->bgModel, RES->fgModel, 1, GC_INIT_WITH_MASK);

                Mat matPFg(RES->gCMask.size(),CV_8UC1,Scalar(0));
                Mat matFg(RES->gCMask.size(),CV_8UC1,Scalar(0));
                compare( RES->gCMask, GC_FGD, matFg, CMP_EQ);
                compare( RES->gCMask, GC_PR_FGD, matPFg, CMP_EQ);
                Mat mat = matPFg + matFg;
                Mat img(RES->img.size(),CV_8UC3,cv::Scalar(0,0,0));
                RES->img.copyTo(img, mat);

                RES->initGCwithRect = true;

                RES->imgDraw = img(RES->rec).clone();
                RES->roi = img(RES->rec).clone();
                imshow("get the foreground in ROI",RES->imgDraw);
            }
        }
    }

    /// *** methods for imageprocessing *** ///
    void adaptivethreshold(Mat &img,int maxVal, int method,int threshType,int blockSize,double offset);
    void canny(Mat &img, int threshold1, int threshold2,int sobelSize, bool L2);
    void calcHoughCircles(Mat &img, vector<Vec3f> &cHough, int method, double invRatio, double minDist, double cannyThreshold, double threshold, int minRadius, int maxRadius);
    void calcHoughLines(Mat &img, vector<Vec2f> &lHough ,double rho, double rhoDiv, int threshold, double theta, double thetaDiv );
    void calcHoughLinesP(Mat &img,vector<Vec4i> &lHoughP, double rho, double theta, int threshold, double minLength, double maxGap);
    void cornerdetect(Mat &img, vector<Vec2i> &corn, int blockSize, int sobelSize, int cornerFlag, int border, int quality, InputArray mask);
    void dilate(Mat &img,int shape, int sizeX, int sizeY,int anchorX, int anchorY, int iterations,int border);
    void erode(Mat &img,int shape, int sizeX, int sizeY,int anchorX, int anchorY, int iterations,int border);
    void gammatransformation(Mat &img, int i);
    void gaussianblur( Mat &img, int sizeX, int sizeY, float sigmaX, float sigmaY, int border);
    void histogramequalization( Mat &img);
    void inversion( Mat &img);
    void laplacian(Mat &img,int size, double scale, double delta, int border);
    void lineartransformation(Mat &img, int i);
    Mat  templatematching(Mat &img, Mat &roi, int mode);
    void meanblur(Mat &img,int sizeX, int sizeY, int anchorX, int anchorY, int border);
    void medianblur(Mat &img, int size);
    void morphologyfilter(Mat &img, int opMethod, int shape, int sizeX, int sizeY,int anchorX, int anchorY, int iterations,int border);
    void scharr(Mat &img, int dx, int dy, double scale, double delta, int border);
    void simpleFilter(Mat &img,int X, int Y, int anchorX, int anchorY, double delta, double* data, int border);
    void sobel(Mat &img,int dx, int dy, int size, double scale, double delta, int border);
    void threshold(Mat &img, double thres, double maxVal, int mode);
    void simpleBackgroundSubstraction(Mat &img, Mat &imgBG);

    /// *** methods and attributes for videoprocessing *** ///

    vector<int> processingToolchainIndex;
    vector<int> processingVideoToolchainIndex;
    bool checkIfCurrentFcnIsAlreadyInToolchain( int i);
    bool checkIfCurrentFcnIsAlreadyInVideoToolchain( int i);
    void validateCurrentFcn( int i, QString hstr);
    // adaptive threshold values
    int adaptThreshMaxValValue;
    int adaptThreshMethodValue;
    int adaptThreshTypeValue;
    int adaptThreshBlockSizeValue;
    int adaptThreshOffsetValue;

    // calchoughlines/P funtions values
    bool calcHoughLinesPropValue;

    vector<Vec2f> calcLinesHoughCam, calcLinesHoughVideo, calcLinesHoughROI;
    vector<Vec4i> calcLinesHoughPCam, calcLinesHoughPVideo, calcLinesHoughPROI;
    double calcHoughLinesRhoValue;
    double calcHoughLinesRhoDivValue;
    int calcHoughLinesThresholdValue;
    double calcHoughLinesThetaValue;
    double calcHoughLinesThetaDivValue;
    double calcHoughLinesPRhoValue;
    double calcHoughLinesPThetaValue;
    int calcHoughLinesPThresholdValue;
    double calcHoughLinesPMinLengthValue;
    double calcHoughLinesPMaxGapValue;

    // calcHoughCircles functions values
    vector<Vec3f> calcCirclesHoughCam, calcCirclesHoughVideo, calcCirclesHoughROI;
    int calcHoughCirclesMethodValue;
    double calcHoughCirclesInvRatioValue;
    double calcHoughCirclesMinDistValue;
    double calcHoughCirclesCannyThresholdValue;
    double calcHoughCirclesThresholdValue;
    int calcHoughCirclesMinRadiusValue;
    int calcHoughCirclesMaxRadiusValue;
    // canny function values
    int cannyThreshold1Values;
    int cannyThreshold2Values;
    int cannySobelSize;
    bool cannyL2Value;
    // cornerDetect funtion values
    vector<Vec2i> cornersCam, cornersVideo, cornersROI;
    int cornerDetectBlockSizeValue;
    int cornerDetectSobelSizeValue;
    int cornerDetectCornerFlagValue;
    int cornerDetectBorderValue;
    int cornerDetectQualityValue;
    // dilate function values
    int dilateShape;
    int dilateSizeX;
    int dilateSizeY;
    int dilateAnchorX;
    int dilateAnchorY;
    int dilateIterationsValue;
    int dilateBorder;

    // erode function values
    int erodeShape;
    int erodeSizeX;
    int erodeSizeY;
    int erodeAnchorX;
    int erodeAnchorY;
    int erodeIterationsValue;
    int erodeBorder;
    // gamma transformation values
    int gammaTransformationValue;
    // gaussian blur
    int gaussianSizeX;
    int gaussianSizeY;
    float gaussianSigmaX;
    float gaussianSigmaY;
    int gaussianBorder;

    // laplace function values
    int laplaceSize;
    double laplaceScaleValue;
    double laplaceDeltaValue;
    int laplaceBorderValue;
    // linear transformation values
    int linearTransformationValue;
    // mean blur values
    int meanBlurSizeX;
    int meanBlurSizeY;
    int meanBlurAnchorX;
    int meanBlurAnchorY;
    int meanBlurBorder;
    // median blur
    int medianBlurSizeValue;
    // morphologyfilter function values
    int morphologyFilterOpMethodValue;
    int morphologyFilterShapeValue;
    int morphologyFilterSizeXValue;
    int morphologyFilterSizeYValue;
    int morphologyFilterAnchorXValue;
    int morphologyFilterAnchorYValue;
    int morphologyFilterIterationsValue;
    int morphologyFilterBorderValue;
    // scharr function values
    int scharrDx;
    int scharrDy;
    double scharrScaleValue;
    double scharrDeltaValue;
    int scharrBorderValue;
    // simplefilter funtion values
    int simpleFilterXValue;
    int simpleFilterYValue;
    int simpleFilterAnchorXValue;
    int simpleFilterAnchorYValue;
    double simpleFilterDeltaValue;
    double* simpleFilterDataValues;
    int simpleFilterBorderValue;
    // sobel function values
    int sobelDx;
    int sobelDy;
    int sobelSize;
    double sobelDeltaValue;
    double sobelScaleValue;
    int sobelBorder;

    // templatematching function values
    vector<int>chosenDbIndexVideo;
    int templateMatchingModeValue;
    // threshold funtion values
    int threshValue;
    int threshMaxValValue;
    int threshModeValue;
    bool threshOtsuValue;

    // tm video
    int chosenRoi;
    int currentTMMode;    
    
    // MSER function values
    MSER FtMSER, FtMSERVid, FtMSERCam;
    int MSERDelta;
    int MSERMinArea;
    int MSERMaxArea;
    double MSERMaxVariation;
    double MSERMinDiversity;
    vector< vector< Point> > MSERPoints, MSERPointsCam, MSERPointsVid, MSERPointsROI,
                             MSERHulls , MSERHullsCam , MSERHullsVid, MSERHullsROI;
    vector<RotatedRect>      MSEREllipses,    MSEREllipsesCam, MSEREllipsesVid, MSEREllipsesROI;

    // FAST Values
    vector<KeyPoint> FASTKeyPoints, FASTKeyPointsROI, FASTKeyPointsCam, FASTKeyPointsVid;
    int FASTThreshold;
    bool FASTNMS;
    int FASTType;

    // ORB values and data
    bool ORBKPFlag = false;
    bool ORBKPFlagVid = false;
    bool ORBKPFlagCam = false;
    ORB FtORB, FtORBCam, FtORBVid;
    Mat ORBDescriptors, ORBDescriptorsVid, ORBDescriptorsCam, ORBDescriptorsROI;
    vector<KeyPoint>  ORBKeyPoints, ORBKeyPointsCam, ORBKeyPointsVid, ORBKeyPointsROI;
    int ORBNFeatures;
    int ORBPatchSize;
    int ORBNLevels;
    int ORBFirstLevel;
    int ORBEdgethreshold;
    float ORBScaleFactor;

    // BRISK values and data
    bool BRISKKPFlag = false;
    bool BRISKKPFlagVid = false;
    bool BRISKKPFlagCam = false;
    BRISK FtBRISK, FtBRISKCam, FtBRISKVid;
    Mat BRISKDescriptors, BRISKDescriptorsVid, BRISKDescriptorsCam, BRISKDescriptorsROI;
    vector<KeyPoint>  BRISKKeyPoints, BRISKKeyPointsCam, BRISKKeyPointsVid, BRISKKeyPointsROI;
    int BRISKThresh;
    int BRISKOctaves;
    float BRISKPatternScale;

    // FREAK values and data
    FREAK FtFREAK, FtFREAKCam, FtFREAKVid;
    Mat FREAKDescriptors, FREAKDescriptorsVid, FREAKDescriptorsCam, FREAKDescriptorsROI;
    vector<KeyPoint>  FREAKKeyPoints, FREAKKeyPointsCam, FREAKKeyPointsVid, FREAKKeyPointsROI;
    bool FREAKOrientationNormalization;
    bool FREAKScaleNormalized;
    float FREAKPatternScale;
    int FREAKNOctaves;

    // MSEREval values and data
    bool MSEREvalSortBySize = false;
    bool MSEREvalSortByHull = false;
    float MSEREvalMinRatio;
    float MSEREvalMaxRatio;
    float MSEREvalMinSize;
    float MSEREvalMaxSize;
    vector<vector <Point> > MSEREvalPoints, MSEREvalHulls;
    vector<RotatedRect> MSEREvalEllipses;


    const double pi = 3.14159265358979323846;
    void chooseFcnForVidProcessing(int i);
    Ptr<FilterEngine> DilateFE;
    void initDilate(Mat &img, int shape, int sizeX, int sizeY,int anchorX, int anchorY, int border);
    Ptr<FilterEngine> ErodeFE;
    void initErode(Mat &img, int shape, int sizeX, int sizeY, int anchorX,int anchorY, int border);
    Ptr<FilterEngine> gaussianFE;
    void initGaussian(Mat &img,int sizeX, int sizeY, int sigmaX, int sigmaY, int border);
    Ptr<FilterEngine> laplaceFE;
    void initLaplacian(Mat &img,int size,int border);
    Ptr<FilterEngine> meanBlurFE;
    void initMeanBlur(Mat &img,int sizeX, int sizeY, int anchorX, int anchorY, int border);
    Ptr<FilterEngine> sobelFE;
    void initSobel(Mat &img,int dx, int dy, int size, int border);
    Ptr<FilterEngine>  scharrFE;
    void initScharr(Mat &img, int dx, int dy, int border);

    void addLineToVideoTextEdit(QString qstr);
    void changeLineOfVideoTextEdit(QString qstr);
    void removeLastLineFromVideoTextEdit();

    // functiondialogs
    DialogLinearTransformation* diallintrans;
    DialogGammaTransformation* dialgammatrans;
    DialogThresholding* dialthresh;
    DialogAdaptiveThreshold* dialadaptthresh;
    DialogBlur* dialblur;
    DialogMedianBlur* dialmedblur;
    DialogGaussian* dialgauss;
    DialogSobel* dialsobel;
    DialogDilation* dialdilate;
    DialogErode* dialerode;
    DialogMorphologyEx* dialmorph;
    DialogCustomFilter* dialcustfilt;
    DialogLaplacian* diallaplace;
    DialogScharr* dialscharr;
    DialogCanny* dialcanny;
    DialogHoughLines* dialhoughlines;
    DialogHoughCircles* dialhoughcircles;
    DialogCornerDetection* dialcornerdetect;
    DialogMSER* dialmser;
    DialogFAST* dialfast;
    DialogORB* dialorb;
    DialogBRISK* dialbrisk;
    DialogFREAK* dialfreak;
    DialogEvalMSER* dialmsereval;
    
private:
    Ui::EAMViewer *ui;
    QGraphicsScene *scene0, *scene1, *scene2, *scene3, *scene4, *scene5, *scene6, *scene7;
    QGraphicsScene *sceneColorImage, *sceneGrayImage, *sceneProcessedGrayImage, *sceneGrayHistogram, *sceneProcessedColorImage, *sceneColorHistogram;
    QGraphicsScene *sceneROI,*sceneROIHist;
    QFileInfoList List, ListVideos;
    int PicNum, VidNum, nline, h, h0, w0, index, functionFlag = 0, ROItoDBFlag[6], numVid, numCam;
    unsigned int currentVideoFrame;
    QDesktopWidget* desktop;
    QString str;
    QSignalMapper* QSMDialogVarSignals;
    QSignalMapper* QSMShowTabs;
    QSignalMapper* QSMKeyPressEvent;
    QSignalMapper* QSMROIEvent;
    QSignalMapper* QSMROIDBEvent;
    QSignalMapper* QSMTMKeyPressEvent;
    QPixmap pm[8], pmROI[2];
    vector<Vec2f> linesHough;
    vector<Vec2i> corners;
    vector<Vec3f> circlesHough;
    vector<Vec4i> linesHoughP;

    //FormROIDataBase currentROIWidget;
    RoiDbStruct dbStructCurrentROI;
    QList<RoiDbStruct> ROIDBItems;
    QList<FormROIDataBase*> ROIDBWidgetItems;

    // GraphicViews for TM
    QList<EventsQGraphicsView*> TMViews;
    QList<QPixmap>pmTM;

    QStandardItemModel* stItMHoughLines;
    QStandardItemModel* stItMHoughCircles;
    QStandardItemModel* stItMCorners;
    QStandardItemModel* stItMSER;
    QStandardItemModel* stItFAST;
    QStandardItemModel* stItORB;
    QStandardItemModel* stItBRISK;
    QStandardItemModel* stItFREAK;
    QStandardItemModel* stItMSEREval;
    bool ROIFlag, HEFlag, closeflag;

    // variables for Imageprocessing
    Mat img0, img1, img2, img3, img4, img5, img6, img7, matbuffc, matbuffg, mask, mattempc, mattempg, ROI,ROIHist, ROIBuff, matdrawn, ROIdrawn;

    // data for camera & videos
    VideoWriter VW;

    QString  videoSaveName;
    Mat vidImg, vidImgProc, camImg, camImgProc, showMat, showMatVideo;
    deque <Mat> VideoBuffer;
    clock_t startTime, endTime;
    unsigned int vidProcTimeDuration, vidIndex, writingVidSize, vidSize, sliderVidFlag;
    QImage qImg, qImgVid;
    VideoCapture camDev, vidDev;
    QTimer  *timer,*timerVideo,              
            *timerRefreshHoughLinesTbl, *timerRefreshHoughLinesTblVideo, 
            *timerRefreshHoughCirclesTbl, *timerRefreshHoughCirclesTblVideo, 
            *timerRefreshCornersTbl, *timerRefreshCornersTblVideo,
            *timerRefreshMSERTbl, *timerRefreshMSERTblVideo, 
            *timerRefreshFASTTbl, *timerRefreshFASTTblVideo,
            *timerRefreshORBTbl, *timerRefreshORBTblVideo, 
            *timerRefreshBRISKTbl, *timerRefreshBRISKTblVideo, 
            *timerRefreshFREAKTbl, *timerRefreshFREAKTblVideo,
            *timerRefreshMSEREvalTbl, *timerRefreshMSEREvalTblVideo;
    bool recordFlagCam, recordFlagVid, camFlag, vidFlag;
    float framesPS, framesPSVid;

    vector<bool> imgVipProcFlags;

    float zf[8]; // zoomfactor

private slots:
    void calcVidProcessingTime();
    void changeTab(int i);
    void confirmProcessedData();
    void closeHoughDialogs();
    void closeTab(int ID);
    void deleteSingleElementsInDB();
    void paramsChanged();
    void drawCornerCircles();
    void drawBRISKFeatures();
    void drawFASTFeatures();
    void drawFREAKFeatures();
    void drawingStructuresCircles(bool b);
    void drawingStructuresCorners(bool b);
    void drawingStructuresLines(bool b);
    void drawHoughLines();
    void drawHoughCircles();
    void drawMSERFeatures();
    void drawMSEREvalFeatures();
    void drawORBFeatures();
    void FPSChanged(int i);
    void FPSChangedVid(int i);
    void grabAndProcessFrame();
    void grabAndProcessFrameVideo();
    void histogramEqual();
    void invertTrans();
    void lastSettings();
    void loadCurrentVideoFrame();
    void loadingDatapath();
    void loadingDatapathVideos();
    void mappingSlotGVMouseEvent(int i);
    void mappingSlotGVKeyPressEvent(int i);
    void mappingSlotTMGVKeyPressEvent(int i);
    void nextVideo();
    void openCamTab();
    void openDatabase();
    void openDialAdaptiveThreshold();
    void openDialBrisk();
    void openDialCanny();
    void openDialCustFilt();
    void openDialCornerDetect();
    void openDialDilate();
    void openDialErode();
    void openDialFast();
    void openDialFreak();
    void openDialGammaTrans();
    void openDialGaussian();
    void openDialHoughCircles();
    void openDialHoughLines();
    void openDialLaplacian();
    void openDialLinearTrans();
    void openDialMeanBlur();
    void openDialMedianBlur();
    void openDialMorph();
    void openDialMSER();
    void openDialMSEREval();
    void openDialOrb();
    void openDialScharr();
    void openDialSobel();
    void openDialThreshold();
    void openTMTab();
    void openVideoTab();
    void prevVideo();
    void refreshTblCornersSlot();
    void refreshTblBRISKKeyPointsSlot();
    void refreshTblFASTKeyPointsSlot();
    void refreshTblFREAKKeyPointsSlot();
    void refreshTblHoughCirclesSlot();
    void refreshTblHoughLinesSlot();
    void refreshTblMSERPointsSlot();
    void refreshTblMSEREvalPointsSlot();
    void refreshTblORBSlot();
    void removeLastFunctionOfVideoToolchain();
    void resetData();
    void resetImgProcViewAfterCornerFlagChanging();
    void resetImgProcViewAfterProbChanging();
    void save();
    void saveEvaluatedMSERData();
    void saveDBToFile();
    void saveROItoDb();
    void selectROI();
    void selectROIFromDB(int i);
    void sliderCurrentFramePosChanged(bool changingFlag = true);
    void sliderPressedStart();
    void sliderPressedStop();
    void startStopGrabbingAndShowingCamera();
    void startStopGrabbingAndShowingVideo();
    void startStopRecordingMovieVideo();
    void startStopRecordingMovieCamera();
    void TMROI();
signals:
    void showDialog();
};

#endif // EAMVIEWER_H
