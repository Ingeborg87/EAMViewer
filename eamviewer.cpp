#include "eamviewer.h"
#include "ui_eamviewer.h"

EAMViewer::EAMViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EAMViewer)
{
    ui->setupUi(this);
    ///*** prepare flags, indizes and index arrays, standarditemmodels ***///
    nline = 0;
    PicNum = 0; // number of current image in List
    VidNum = 0; // number of current video in ListVideos
    numVid = 0;
    numCam = 0;
    sliderVidFlag = 0;
    for( h = 0; h < 6; h++)
        ROItoDBFlag[h] = 0;

    HEFlag = false;
    index = 8;
    stItMHoughLines     = new QStandardItemModel;
    stItMHoughCircles   = new QStandardItemModel;
    stItMCorners        = new QStandardItemModel;
    stItMSER            = new QStandardItemModel;
    stItFAST            = new QStandardItemModel;
    stItORB             = new QStandardItemModel;
    stItBRISK           = new QStandardItemModel;
    stItFREAK           = new QStandardItemModel;
    stItMSEREval        = new QStandardItemModel;

    closeflag = false;
    //------------------------------------------------//

    ///*** prepare dialogs an cvwidgets ***///

    dialgammatrans      = new DialogGammaTransformation;
    diallintrans        = new DialogLinearTransformation;
    dialthresh          = new DialogThresholding;
    dialadaptthresh     = new DialogAdaptiveThreshold;
    dialblur            = new DialogBlur;
    dialmedblur         = new DialogMedianBlur;
    dialgauss           = new DialogGaussian;
    dialsobel           = new DialogSobel;
    dialdilate          = new DialogDilation;
    dialerode           = new DialogErode;
    dialmorph           = new DialogMorphologyEx;
    dialcustfilt        = new DialogCustomFilter;
    diallaplace         = new DialogLaplacian;
    dialscharr          = new DialogScharr;
    dialcanny           = new DialogCanny;
    dialhoughlines      = new DialogHoughLines;
    dialhoughcircles    = new DialogHoughCircles;
    dialcornerdetect    = new DialogCornerDetection;
    dialmser            = new DialogMSER;
    dialfast            = new DialogFAST;
    dialorb             = new DialogORB;
    dialbrisk           = new DialogBRISK;
    dialfreak           = new DialogFREAK;
    dialmsereval        = new DialogEvalMSER;
    //------------------------------------//

    ///*** prepare graphicviews ***///
    scene0 = new QGraphicsScene;
    scene1 = new QGraphicsScene;
    scene2 = new QGraphicsScene;
    scene3 = new QGraphicsScene;
    scene4 = new QGraphicsScene;
    scene5 = new QGraphicsScene;
    scene6 = new QGraphicsScene;
    scene7 = new QGraphicsScene;

    sceneColorImage = new QGraphicsScene;
    sceneGrayImage = new QGraphicsScene;
    sceneProcessedGrayImage = new QGraphicsScene;
    sceneGrayHistogram = new QGraphicsScene;
    sceneColorHistogram = new QGraphicsScene;
    sceneProcessedColorImage = new QGraphicsScene;

    sceneROI = new QGraphicsScene;
    sceneROIHist = new QGraphicsScene;

    ui->gV_0->setScene(scene0);
    ui->gV_1->setScene(scene1);
    ui->gV_2->setScene(scene2);
    ui->gV_3->setScene(scene3);
    ui->gV_4->setScene(scene4);
    ui->gV_5->setScene(scene5);
    ui->gV_6->setScene(scene6);
    ui->gV_7->setScene(scene7);

    ui->gVColorImg->setScene(sceneColorImage);
    ui->gVGrayImg->setScene(sceneGrayImage);
    ui->gVProcGrayImg->setScene(sceneProcessedGrayImage);
    ui->gVGrayHist->setScene(sceneGrayHistogram);
    ui->gVProcColorImg->setScene(sceneProcessedColorImage);
    ui->gVColorHist->setScene(sceneColorHistogram);

    ui->gVROI->setScene(sceneROI);
    ui->gVROIHist->setScene(sceneROIHist);

    //------------------------------------//

    ///*** prepare flags, indizes and index arrays ***///
    for(h = 0; h < 11; h++ )
        ui->tabWidget->removeTab(0);

    ui->tabWidget->setTabsClosable(true);

    //------------------------------------//

    ///*** load image data ***///
    fstream file;
    char* c = new char[100];
    file.open("loading_directory.txt",ios_base::in);

    if(!file.is_open())
    {
        file.close();
        QString str = QFileDialog::getExistingDirectory(this, tr("open imagedirectory"),"/home/peter/DA/pics/", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
        QDir dir(str);
        List = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,QDir::Name);
        file.open("loading_directory.txt",ios_base::trunc |ios_base::out);
        file.close();
    }
    else if(file.is_open())
    {
        file.getline(c,100);
        file.close();
        QDir dir(tr(c));
        List = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,QDir::Name);
    }

    for( h = (List.size()-1); h >= 0; h--)
    {
        string hstr = List.at(h).fileName().toStdString();
        int p = hstr.find(".");
        QString sstr(tr(hstr.substr(p+1,hstr.length()-1).data()));

        if(sstr.compare(     "bmp" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("dib" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jpg" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jpe" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jpeg",Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jp2" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("png" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("pbm" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("pgm" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("ppm" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("sr"  ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("ras" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("tiff",Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("tif" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("avi" ,Qt::CaseInsensitive) == 0){}
        else
            List.removeAt(h);
    }

    newLineInText(tr(c) + tr(" contains: "));
    for( h = 0; h < List.size(); h++)
        newLineInText(tr("      ") + List.at(h).fileName());

    ///*** load video data ***///

    delete[] c;
    c = new char[100];
    file.open("loading_vid_directory.txt",ios_base::in);

    if(!file.is_open())
    {
        file.close();
        QString str = QFileDialog::getExistingDirectory(this, tr("open videodirectory"),"/home/peter/DA/videos/", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
        QDir dir(str);
        List = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,QDir::Name);
        file.open("loading_vid_directory.txt",ios_base::trunc |ios_base::out);
        file.close();
    }
    else if(file.is_open())
    {
        file.getline(c,100);
        file.close();
        QDir dir(tr(c));
        ListVideos = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,QDir::Name);
    }

    for( h = (ListVideos.size()-1); h >= 0; h--)
    {
        string hstr = ListVideos.at(h).fileName().toStdString();
        int p = hstr.find(".");
        QString sstr(tr(hstr.substr(p+1,hstr.length()-1).data()));

        if(sstr.compare(tr("avi")  ,Qt::CaseInsensitive) == 0){} //        else if(sstr.compare("avi" ,Qt::CaseInsensitive) == 0){}
        else
            List.removeAt(h);
    }

    loadVideoSize();
    loadVideoInBuffer();
    newLineInText(tr(c) + tr(" contains: "));
    for( h = 0; h < ListVideos.size(); h++)
        newLineInText(tr("      ") + ListVideos.at(h).fileName());

    delete[] c;
    loadImages(0);
    loadPixmaps();

    ///*** prepare cam & video tab ***///

    camDev.open(0);
    timer =  new QTimer(this);
    timerVideo =  new QTimer(this);
    timerRefreshHoughCirclesTbl =  new QTimer(this);
    timerRefreshHoughLinesTbl =  new QTimer(this);
    timerRefreshCornersTbl =  new QTimer(this);
    timerRefreshMSERTbl = new QTimer(this);
    timerRefreshFASTTbl =  new QTimer(this);
    timerRefreshORBTbl =  new QTimer(this);
    timerRefreshBRISKTbl =  new QTimer(this);
    timerRefreshFREAKTbl =  new QTimer(this);
    timerRefreshMSEREvalTbl   = new QTimer(this);

    timerRefreshHoughCirclesTblVideo =  new QTimer(this);
    timerRefreshHoughLinesTblVideo =  new QTimer(this);
    timerRefreshCornersTblVideo =  new QTimer(this);
    timerRefreshMSERTblVideo = new QTimer(this);
    timerRefreshFASTTblVideo =  new QTimer(this);
    timerRefreshORBTblVideo =  new QTimer(this);
    timerRefreshBRISKTblVideo =  new QTimer(this);
    timerRefreshFREAKTblVideo =  new QTimer(this);
    timerRefreshMSEREvalTblVideo   = new QTimer(this);
    if(camDev.isOpened() == false)
        newLineInText("No device found!");

    recordFlagVid = 0;
    recordFlagCam = 0;

    framesPS = 25;
    framesPSVid = 25;
    grabAndProcessFrame();
    grabAndProcessFrameVideo();

    timer->start(int(1000/framesPS));
    timerVideo->start(int(1000/framesPSVid));
    ui->lblFPS->setText(tr("fps: ") + QString::number(framesPS) + tr(" 1/s"));
    ui->lblFPSVid->setText(tr("fps: ") + QString::number(framesPSVid) + tr(" 1/s"));
    ui->sliderFPS->setValue(int(framesPS));
    ui->sliderFPSVid->setValue(int(framesPSVid));
    startStopGrabbingAndShowingCamera();
    startStopGrabbingAndShowingVideo();

    //** connect GUI stuff **//
    // set signalmapper for mouseevent to open single tabs
    QSMShowTabs = new QSignalMapper(this);
    connect(ui->gV_0,SIGNAL(mouseDoubleClicked()),QSMShowTabs,SLOT(map()));
    connect(ui->gV_1,SIGNAL(mouseDoubleClicked()),QSMShowTabs,SLOT(map()));
    connect(ui->gV_2,SIGNAL(mouseDoubleClicked()),QSMShowTabs,SLOT(map()));
    connect(ui->gV_3,SIGNAL(mouseDoubleClicked()),QSMShowTabs,SLOT(map()));
    connect(ui->gV_4,SIGNAL(mouseDoubleClicked()),QSMShowTabs,SLOT(map()));
    connect(ui->gV_5,SIGNAL(mouseDoubleClicked()),QSMShowTabs,SLOT(map()));
    connect(ui->gV_6,SIGNAL(mouseDoubleClicked()),QSMShowTabs,SLOT(map()));
    connect(ui->gV_7,SIGNAL(mouseDoubleClicked()),QSMShowTabs,SLOT(map()));

    QSMShowTabs->setMapping(ui->gV_0,0);
    QSMShowTabs->setMapping(ui->gV_1,1);
    QSMShowTabs->setMapping(ui->gV_2,2);
    QSMShowTabs->setMapping(ui->gV_3,3);
    QSMShowTabs->setMapping(ui->gV_4,4);
    QSMShowTabs->setMapping(ui->gV_5,5);
    QSMShowTabs->setMapping(ui->gV_6,6);
    QSMShowTabs->setMapping(ui->gV_7,7);

    connect(QSMShowTabs,SIGNAL(mapped(int)),this,SLOT(mappingSlotGVMouseEvent(int)));

    // set signalmapper for keypressevent to resize single tab images
    QSMKeyPressEvent = new QSignalMapper(this);
    connect(ui->gVColorImg,SIGNAL(keyPressed()),QSMKeyPressEvent,SLOT(map()));
    connect(ui->gVGrayImg,SIGNAL(keyPressed()),QSMKeyPressEvent,SLOT(map()));
    connect(ui->gVProcGrayImg,SIGNAL(keyPressed()),QSMKeyPressEvent,SLOT(map()));
    connect(ui->gVGrayHist,SIGNAL(keyPressed()),QSMKeyPressEvent,SLOT(map()));
    connect(ui->gVProcColorImg,SIGNAL(keyPressed()),QSMKeyPressEvent,SLOT(map()));
    connect(ui->gVColorHist,SIGNAL(keyPressed()),QSMKeyPressEvent,SLOT(map()));

    QSMKeyPressEvent->setMapping(ui->gVColorImg,0);
    QSMKeyPressEvent->setMapping(ui->gVGrayImg,1);
    QSMKeyPressEvent->setMapping(ui->gVProcGrayImg,2);
    QSMKeyPressEvent->setMapping(ui->gVGrayHist,3);
    QSMKeyPressEvent->setMapping(ui->gVProcColorImg,5);
    QSMKeyPressEvent->setMapping(ui->gVColorHist,6);

    connect(QSMKeyPressEvent,SIGNAL(mapped(int)),this,SLOT(mappingSlotGVKeyPressEvent(int)));

    // make tabs closeable
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),SLOT(changeTab(int)));

    // connect params from dialogs
    connect(dialadaptthresh,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialadaptthresh,SIGNAL(signalMaximumChanged()),this,SLOT(paramsChanged()));
    connect(dialadaptthresh,SIGNAL(signalBlSizeChanged()),this,SLOT(paramsChanged()));
    connect(dialadaptthresh,SIGNAL(signalCChanged()),this,SLOT(paramsChanged()));
    connect(dialadaptthresh,SIGNAL(signalIndexMethodChanged()),this,SLOT(paramsChanged()));
    connect(dialadaptthresh,SIGNAL(signalIndexTypeChanged()),this,SLOT(paramsChanged()));

    connect(dialblur,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialblur,SIGNAL(signalSizeXChanged()),this,SLOT(paramsChanged()));
    connect(dialblur,SIGNAL(signalSizeYChanged()),this,SLOT(paramsChanged()));
    connect(dialblur,SIGNAL(signalAnchorXChanged()),this,SLOT(paramsChanged()));
    connect(dialblur,SIGNAL(signalAnchorYChanged()),this,SLOT(paramsChanged()));
    connect(dialblur,SIGNAL(signalCbxIndexChanged()),this,SLOT(paramsChanged()));

    connect(dialcanny,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialcanny,SIGNAL(signalThreshold1Changed()),this,SLOT(paramsChanged()));
    connect(dialcanny,SIGNAL(signalThreshold2Changed()),this,SLOT(paramsChanged()));
    connect(dialcanny,SIGNAL(signalSobelSizeChanged()),this,SLOT(paramsChanged()));
    connect(dialcanny,SIGNAL(signalL2Changed()),this,SLOT(paramsChanged()));

    connect(dialcustfilt, SIGNAL(signalPressReturn()), this, SLOT(paramsChanged()));

    connect(dialcornerdetect,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialcornerdetect,SIGNAL(signalCornerFlagChanged()),this,SLOT(paramsChanged()));
    connect(dialcornerdetect,SIGNAL(signalSobelSizeChanged()),this,SLOT(paramsChanged()));
    connect(dialcornerdetect,SIGNAL(signalBlockSizeChanged()),this,SLOT(paramsChanged()));
    connect(dialcornerdetect,SIGNAL(signalBorderTypeChanged()),this,SLOT(paramsChanged()));
    connect(dialcornerdetect,SIGNAL(signalQualityChanged()),this,SLOT(paramsChanged()));

    connect(dialdilate,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialdilate,SIGNAL(signalSizeXChanged()),this,SLOT(paramsChanged()));
    connect(dialdilate,SIGNAL(signalSizeYChanged()),this,SLOT(paramsChanged()));
    connect(dialdilate,SIGNAL(signalAnchorXChanged()),this,SLOT(paramsChanged()));
    connect(dialdilate,SIGNAL(signalAnchorYChanged()),this,SLOT(paramsChanged()));
    connect(dialdilate,SIGNAL(signalBorderChanged()),this,SLOT(paramsChanged()));
    connect(dialdilate,SIGNAL(signalShapeIndexChanged()),this,SLOT(paramsChanged()));
    connect(dialdilate,SIGNAL(signalIterationsChanged()),this,SLOT(paramsChanged()));

    connect(dialerode,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialerode,SIGNAL(signalSizeXChanged()),this,SLOT(paramsChanged()));
    connect(dialerode,SIGNAL(signalSizeYChanged()),this,SLOT(paramsChanged()));
    connect(dialerode,SIGNAL(signalAnchorXChanged()),this,SLOT(paramsChanged()));
    connect(dialerode,SIGNAL(signalAnchorYChanged()),this,SLOT(paramsChanged()));
    connect(dialerode,SIGNAL(signalBorderChanged()),this,SLOT(paramsChanged()));
    connect(dialerode,SIGNAL(signalShapeIndexChanged()),this,SLOT(paramsChanged()));
    connect(dialerode,SIGNAL(signalIterationsChanged()),this,SLOT(paramsChanged()));

    connect(dialgammatrans,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialgammatrans,SIGNAL(signalGammaTransChanged()),this,SLOT(paramsChanged()));

    connect(dialgauss,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialgauss,SIGNAL(signalSizeXChanged()),this,SLOT(paramsChanged()));
    connect(dialgauss,SIGNAL(signalSizeYChanged()),this,SLOT(paramsChanged()));
    connect(dialgauss,SIGNAL(signalSigmaXChanged()),this,SLOT(paramsChanged()));
    connect(dialgauss,SIGNAL(signalSigmaYChanged()),this,SLOT(paramsChanged()));
    connect(dialgauss,SIGNAL(signalCbxIndexChanged()),this,SLOT(paramsChanged()));

    connect(dialhoughcircles,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialhoughcircles,SIGNAL(signalMethodChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughcircles,SIGNAL(signalMinDistChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughcircles,SIGNAL(signalInvRatioChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughcircles,SIGNAL(signalCannyThresholdChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughcircles,SIGNAL(signalThresholdChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughcircles,SIGNAL(signalMinRadiusChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughcircles,SIGNAL(signalMaxRadiusChanged()),this,SLOT(paramsChanged()));

    connect(dialhoughlines,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialhoughlines,SIGNAL(signalProbChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughlines,SIGNAL(signalRhoChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughlines,SIGNAL(signalRhoDivChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughlines,SIGNAL(signalThetaChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughlines,SIGNAL(signalThetaDivChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughlines,SIGNAL(signalThresholdChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughlines,SIGNAL(signalMinLengthChanged()),this,SLOT(paramsChanged()));
    connect(dialhoughlines,SIGNAL(signalMaxGapChanged()),this,SLOT(paramsChanged()));

    connect(diallaplace,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(diallaplace,SIGNAL(signalSizeChanged()),this,SLOT(paramsChanged()));
    connect(diallaplace,SIGNAL(signalScaleChanged()),this,SLOT(paramsChanged()));
    connect(diallaplace,SIGNAL(signalDeltaChanged()),this,SLOT(paramsChanged()));
    connect(diallaplace,SIGNAL(signalBorderChanged()),this,SLOT(paramsChanged()));

    connect(diallintrans,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(diallintrans, SIGNAL(signalValueLinTransChanged()),this,SLOT(paramsChanged()));

    connect(dialmedblur,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialmedblur, SIGNAL(signalMedianSizeChanged()),this,SLOT(paramsChanged()));

    connect(dialmorph, SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialmorph, SIGNAL(signalSizeXChanged()),this,SLOT(paramsChanged()));
    connect(dialmorph, SIGNAL(signalSizeYChanged()),this,SLOT(paramsChanged()));
    connect(dialmorph, SIGNAL(signalAnchorXChanged()),this,SLOT(paramsChanged()));
    connect(dialmorph, SIGNAL(signalAnchorYChanged()),this,SLOT(paramsChanged()));
    connect(dialmorph, SIGNAL(signalBorderChanged()),this,SLOT(paramsChanged()));
    connect(dialmorph, SIGNAL(signalShapeIndexChanged()),this,SLOT(paramsChanged()));
    connect(dialmorph, SIGNAL(signalIterationsChanged()),this,SLOT(paramsChanged()));
    connect(dialmorph, SIGNAL(signalOpIndexChanged()),this,SLOT(paramsChanged()));

    connect(dialscharr, SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialscharr, SIGNAL(signalDxChanged()),this,SLOT(paramsChanged()));
    connect(dialscharr, SIGNAL(signalDyChanged()),this,SLOT(paramsChanged()));
    connect(dialscharr, SIGNAL(signalScaleChanged()),this,SLOT(paramsChanged()));
    connect(dialscharr, SIGNAL(signalDeltaChanged()),this,SLOT(paramsChanged()));
    connect(dialscharr, SIGNAL(signalBorderTypeChanged()),this,SLOT(paramsChanged()));

    connect(dialsobel ,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialsobel,SIGNAL(signalDxChanged()),this,SLOT(paramsChanged()));
    connect(dialsobel,SIGNAL(signalDyChanged()),this,SLOT(paramsChanged()));
    connect(dialsobel,SIGNAL(signalSizeChanged()),this,SLOT(paramsChanged()));
    connect(dialsobel,SIGNAL(signalScaleChanged()),this,SLOT(paramsChanged()));
    connect(dialsobel,SIGNAL(signalDeltaChanged()),this,SLOT(paramsChanged()));
    connect(dialsobel,SIGNAL(signalCbxIndexChanged()),this,SLOT(paramsChanged()));

    connect(dialthresh,SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialthresh,SIGNAL(signalThreshChanged()),this,SLOT(paramsChanged()));
    connect(dialthresh,SIGNAL(signalMaxChanged()),this,SLOT(paramsChanged()));
    connect(dialthresh,SIGNAL(signalCheckStateChanged()),this,SLOT(paramsChanged()));
    connect(dialthresh,SIGNAL(signalComboIndexChanged()),this,SLOT(paramsChanged()));

    connect(dialmser, SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialmser, SIGNAL(signalDeltaChanged()),this,SLOT(paramsChanged()));
    connect(dialmser, SIGNAL(signalMinAreaChanged()),this,SLOT(paramsChanged()));
    connect(dialmser, SIGNAL(signalMaxAreaChanged()),this,SLOT(paramsChanged()));
    connect(dialmser, SIGNAL(signalMaxVariationChanged()),this,SLOT(paramsChanged()));
    connect(dialmser, SIGNAL(signalMinDiversityChanged()),this,SLOT(paramsChanged()));
    
    connect(dialfast, SIGNAL(signalPressReturn()),this,SLOT(paramsChanged()));
    connect(dialfast, SIGNAL(signalThresholdChanged()),SLOT(paramsChanged()));
    connect(dialfast, SIGNAL(signalNMSChanged()),SLOT(paramsChanged()));
    connect(dialfast, SIGNAL(signalTypeChanged()),SLOT(paramsChanged()));

    connect(dialorb, SIGNAL(signalPressReturn()), this, SLOT(paramsChanged()));
    connect(dialorb, SIGNAL(signalNFeaturesChanged()), this, SLOT(paramsChanged()));
    connect(dialorb, SIGNAL(signalScaleFactorChanged()), this, SLOT(paramsChanged()));
    connect(dialorb, SIGNAL(signalNLevelsChanged()), this, SLOT(paramsChanged()));
    connect(dialorb, SIGNAL(signalEdgeThresholdChanged()), this, SLOT(paramsChanged()));
    connect(dialorb, SIGNAL(signalFirstLevelChanged()), this, SLOT(paramsChanged()));
    connect(dialorb, SIGNAL(signalPatchSizeChanged()), this, SLOT(paramsChanged()));
    connect(dialorb, SIGNAL(signalFASTKeyPointsChanged()), this, SLOT(paramsChanged()));
    connect(dialorb, SIGNAL(signalBRISKKeyPointsChanged()), this, SLOT(paramsChanged()));

    connect(dialbrisk, SIGNAL(signalPressReturn()), this, SLOT(paramsChanged()));
    connect(dialbrisk, SIGNAL(signalsOctavesChanged()), this, SLOT(paramsChanged()));
    connect(dialbrisk, SIGNAL(signalsPatternScaleChanged()), this, SLOT(paramsChanged()));
    connect(dialbrisk, SIGNAL(signalsThreshChanged()), this, SLOT(paramsChanged()));
    connect(dialbrisk, SIGNAL(signalFASTKeyPointsChanged()), this, SLOT(paramsChanged()));
    connect(dialbrisk, SIGNAL(signalORBKeyPointsChanged()), this, SLOT(paramsChanged()));

    connect(dialfreak, SIGNAL(signalPressReturn()), this, SLOT(paramsChanged()));
    connect(dialfreak, SIGNAL(signalOrientationNormalizedChanged()),this, SLOT(paramsChanged()));
    connect(dialfreak, SIGNAL(signalScaleNormalizedChanged()), this, SLOT(paramsChanged()));
    connect(dialfreak, SIGNAL(signalPatternScaleChanged()), this, SLOT(paramsChanged()));
    connect(dialfreak, SIGNAL(signalNOctavesChanged()), this, SLOT(paramsChanged()));
    connect(dialfreak, SIGNAL(signalFASTKeyPointsChanged()), this, SLOT(paramsChanged()));
    connect(dialfreak, SIGNAL(signalORBKeyPointsChanged()), this, SLOT(paramsChanged()));
    connect(dialfreak, SIGNAL(signalBRISKKeyPointsChanged()), this, SLOT(paramsChanged()));

    connect(dialmsereval, SIGNAL(signalPressReturn()), this, SLOT(paramsChanged()));
    connect(dialmsereval, SIGNAL(signalSortBySizeChanged()), this, SLOT(paramsChanged()));
    connect(dialmsereval, SIGNAL(signalSortByHullChanged()), this, SLOT(paramsChanged()));
    connect(dialmsereval, SIGNAL(signalMinSizeChanged()), this, SLOT(paramsChanged()));
    connect(dialmsereval, SIGNAL(signalMaxSizeChanged()), this, SLOT(paramsChanged()));
    connect(dialmsereval, SIGNAL(signalMinRatioChanged()), this, SLOT(paramsChanged()));
    connect(dialmsereval, SIGNAL(signalMaxRatioChanged()), this, SLOT(paramsChanged()));
    connect(dialmsereval, SIGNAL(signalPBSaveDataPushed()), this, SLOT(saveEvaluatedMSERData()));

    /// connect menu actions ///
    // connect data menu //
    connect(ui->actionLoad,SIGNAL(triggered()),this,SLOT(loadingDatapath()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->actionReset_data,SIGNAL(triggered()),this,SLOT(resetData()));

    // connect standard menu //
    connect(ui->actionInversion,SIGNAL(triggered()),this,SLOT(invertTrans()));
    connect(ui->actionHistogram_equalization,SIGNAL(triggered()),this,SLOT(histogramEqual()));
    connect(ui->actionLinear_transformation,SIGNAL(triggered()),this,SLOT(openDialLinearTrans()));
        connect(diallintrans,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionGamma_transformation,SIGNAL(triggered()),this,SLOT(openDialGammaTrans()));
        connect(dialgammatrans,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionThreshold,SIGNAL(triggered()),this,SLOT(openDialThreshold()));
        connect(dialthresh,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionAdaptive_threshold,SIGNAL(triggered()),this,SLOT(openDialAdaptiveThreshold()));
        connect(dialadaptthresh,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    // connect filter menu //
    connect(ui->actionMean,SIGNAL(triggered()),this,SLOT(openDialMeanBlur()));
        connect(dialblur,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionMedian,SIGNAL(triggered()),this,SLOT(openDialMedianBlur()));
        connect(dialmedblur,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionGaussian,SIGNAL(triggered()),this,SLOT(openDialGaussian()));
        connect(dialgauss,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionSobel,SIGNAL(triggered()),this,SLOT(openDialSobel()));
        connect(dialsobel,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionScharr,SIGNAL(triggered()),this,SLOT(openDialScharr()));
        connect(dialscharr,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionCanny,SIGNAL(triggered()),this,SLOT(openDialCanny()));
        connect(dialcanny,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionSmall_custom_filter ,SIGNAL(triggered()),this,SLOT(openDialCustFilt()));
        connect(dialcustfilt,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionDilate ,SIGNAL(triggered()),this,SLOT(openDialDilate()));
        connect(dialdilate,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionErode ,SIGNAL(triggered()),this,SLOT(openDialErode()));
        connect(dialerode,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionMorphology_filter ,SIGNAL(triggered()),this,SLOT(openDialMorph()));
        connect(dialmorph,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));
    connect(ui->actionLaplacian ,SIGNAL(triggered()),this,SLOT(openDialLaplacian()));
        connect(diallaplace,SIGNAL(signalXDialog()),this,SLOT(confirmProcessedData()));

    // connect structures //
    connect(ui->actionLines,SIGNAL(triggered()),this,SLOT(openDialHoughLines()));
        connect(dialhoughlines,SIGNAL(signalDrawLines(bool)),this,SLOT(drawHoughLines()));
        connect(dialhoughlines,SIGNAL(signalProbChanged()),this,SLOT(resetImgProcViewAfterProbChanging()));
        connect(dialhoughlines,SIGNAL(signalChangeDrawFlag(bool)),this,SLOT(drawingStructuresLines(bool)));
        connect(dialhoughlines, SIGNAL(signalXDialog()), this, SLOT(closeHoughDialogs()));
        connect(timerRefreshHoughLinesTbl,SIGNAL(timeout()),this,SLOT(refreshTblHoughLinesSlot()));
        connect(timerRefreshHoughLinesTblVideo,SIGNAL(timeout()),this,SLOT(refreshTblHoughLinesSlot()));
    connect(ui->actionCircles,SIGNAL(triggered()),this,SLOT(openDialHoughCircles()));
        connect(dialhoughcircles,SIGNAL(signalDrawCircles()),this,SLOT(drawHoughCircles()));
        connect(dialhoughcircles,SIGNAL(signalChangeDrawFlag(bool)),this,SLOT(drawingStructuresCircles(bool)));
        connect(dialhoughcircles, SIGNAL(signalXDialog()), this, SLOT(closeHoughDialogs()));
        connect(timerRefreshHoughCirclesTbl,SIGNAL(timeout()),this,SLOT(refreshTblHoughCirclesSlot()));
        connect(timerRefreshHoughCirclesTblVideo,SIGNAL(timeout()),this,SLOT(refreshTblHoughCirclesSlot()));
    connect(ui->actionCorners,SIGNAL(triggered()),this,SLOT(openDialCornerDetect()));
        connect(dialcornerdetect,SIGNAL(signalDrawCircles()),this,SLOT(drawCornerCircles()));
        connect(dialcornerdetect,SIGNAL(signalCornerFlagChanged()),this,SLOT(resetImgProcViewAfterCornerFlagChanging()));
        connect(dialcornerdetect,SIGNAL(signalChangeDrawFlag(bool)),this,SLOT(drawingStructuresCorners(bool)));
        connect(dialcornerdetect, SIGNAL(signalXDialog()), this, SLOT(closeHoughDialogs()));
        connect(timerRefreshCornersTbl,SIGNAL(timeout()),this,SLOT(refreshTblCornersSlot()));
        connect(timerRefreshCornersTblVideo,SIGNAL(timeout()),this,SLOT(refreshTblCornersSlot()));

    // connect pushbuttons in current ROI tab //
    connect(ui->actionSelect,SIGNAL(triggered()),this,SLOT(selectROI()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openDatabase()));
    connect(ui->actionDelete_chosen_elements,SIGNAL(triggered()),this,SLOT(deleteSingleElementsInDB()));
    connect(ui->actionSave_database,SIGNAL(triggered()),this,SLOT(saveDBToFile()));
    connect(ui->pbToDB,SIGNAL(clicked()),this,SLOT(saveROItoDb()));
    
    // connect blob dialogs
    connect(ui->actionMSER,SIGNAL(triggered()),this,SLOT(openDialMSER()));
    connect(dialmser,SIGNAL(signalDrawFlagKeyPointsChanged(bool)),this,SLOT(drawMSERFeatures()));
    connect(dialmser,SIGNAL(signalDrawFlagHullsChanged(bool)),this,SLOT(drawMSERFeatures()));
    connect(dialmser,SIGNAL(signalDrawFlagEllipsesChanged(bool)),this,SLOT(drawMSERFeatures()));
    connect(dialmser,SIGNAL(signalXDialog()), this, SLOT(closeHoughDialogs()));
    connect(timerRefreshMSERTbl, SIGNAL(timeout()),this,SLOT(refreshTblMSERPointsSlot()));
    connect(timerRefreshMSERTblVideo, SIGNAL(timeout()),this,SLOT(refreshTblMSERPointsSlot()));
    
    connect(ui->actionFAST, SIGNAL(triggered()), this, SLOT(openDialFast()));
    connect(dialfast, SIGNAL(signalDrawKeyPointsFlagChanged()),this, SLOT(drawFASTFeatures()));
    connect(dialfast, SIGNAL(signalXDialog()), this, SLOT(closeHoughDialogs()));
    connect(timerRefreshFASTTbl, SIGNAL(timeout()), this, SLOT(refreshTblFASTKeyPointsSlot()));
    connect(timerRefreshFASTTblVideo, SIGNAL(timeout()), this, SLOT(refreshTblFASTKeyPointsSlot()));

    connect(ui->actionORB, SIGNAL(triggered()), this, SLOT(openDialOrb()));
    connect(dialorb, SIGNAL(signalDrawKeyPointsFlagChanged()),this, SLOT(drawORBFeatures()));
    connect(dialorb, SIGNAL(signalXDialog()), this, SLOT(closeHoughDialogs()));
    connect(timerRefreshORBTbl,SIGNAL(timeout()), this, SLOT(refreshTblORBSlot()));
    connect(timerRefreshORBTblVideo,SIGNAL(timeout()), this, SLOT(refreshTblORBSlot()));

    connect(ui->actionBRISK, SIGNAL(triggered()), this, SLOT(openDialBrisk()));
    connect(dialbrisk, SIGNAL(signalDrawKeyPointsFlagChanged()),this, SLOT(drawBRISKFeatures()));
    connect(dialbrisk, SIGNAL(signalXDialog()),this,SLOT(closeHoughDialogs()));
    connect(timerRefreshBRISKTbl,SIGNAL(timeout()),this,SLOT(refreshTblBRISKKeyPointsSlot()));
    connect(timerRefreshBRISKTblVideo,SIGNAL(timeout()),this,SLOT(refreshTblBRISKKeyPointsSlot()));

    connect(ui->actionFREAK, SIGNAL(triggered()), this, SLOT(openDialFreak()));
    connect(dialfreak, SIGNAL(signalDrawKeyPointsFlagChanged()), this, SLOT(drawFREAKFeatures()));
    connect(dialfreak, SIGNAL(signalXDialog()), this, SLOT(closeHoughDialogs()));
    connect(timerRefreshFREAKTbl, SIGNAL(timeout()), this, SLOT(refreshTblFREAKKeyPointsSlot()));
    connect(timerRefreshFREAKTblVideo, SIGNAL(timeout()), this, SLOT(refreshTblFREAKKeyPointsSlot()));

    connect(ui->actionEval_MSER, SIGNAL(triggered()), this, SLOT(openDialMSEREval()));
    connect(dialmsereval, SIGNAL(signalDrawKeyPointsFlagChanged()), this, SLOT(drawMSEREvalFeatures()));
    connect(dialmsereval, SIGNAL(signalDrawFlagHullsChanged()), this, SLOT(drawMSEREvalFeatures()));
    connect(dialmsereval, SIGNAL(signalDrawFlagEllipsesChanged()), this, SLOT(drawMSEREvalFeatures()));
    connect(dialmsereval, SIGNAL(signalXDialog()), this, SLOT(closeHoughDialogs()));
    connect(timerRefreshMSEREvalTbl, SIGNAL(timeout()), this, SLOT(refreshTblMSEREvalPointsSlot()));
    connect(timerRefreshMSEREvalTblVideo, SIGNAL(timeout()), SLOT(refreshTblMSEREvalPointsSlot()));

    // connect signalmapper from mouseevent from roidatabase
    QSMROIDBEvent = new QSignalMapper(this);
    connect(QSMROIDBEvent,SIGNAL(mapped(int)),this,SLOT(selectROIFromDB(int)));

    // connect signalmapper from keypressevents from EventGVs in tmtab
    QSMTMKeyPressEvent = new QSignalMapper(this);
    connect(QSMTMKeyPressEvent,SIGNAL(mapped(int)),this,SLOT(mappingSlotTMGVKeyPressEvent(int)));
    // connect signal to open template matching tab and connect start pb //
    connect(ui->actionOpen_tm_tab,SIGNAL(triggered()),this,SLOT(openTMTab()));
    connect(ui->actionOn_ROI,SIGNAL(triggered()),this,SLOT(TMROI()));

    // connect camwidget signals
    connect(ui->actionOpen_cam,SIGNAL(triggered()),this,SLOT(openCamTab()));
    connect(timer,SIGNAL(timeout()),this,SLOT(grabAndProcessFrame()));
    connect(ui->pbPlay,SIGNAL(clicked()),this,SLOT(startStopGrabbingAndShowingCamera()));
    connect(ui->pbRecord,SIGNAL(clicked()),this,SLOT(startStopRecordingMovieCamera()));
    connect(ui->pbChooseFrame,SIGNAL(clicked()),this,SLOT(loadCurrentVideoFrame()));
    connect(ui->sliderFPS,SIGNAL(sliderMoved(int)),this,SLOT(FPSChanged(int)));
    connect(ui->pbPopFromToolchain,SIGNAL(clicked()),this,SLOT(removeLastFunctionOfVideoToolchain()));

    // connect videowidget signals
    connect(ui->actionOpen_videotab, SIGNAL(triggered()), this, SLOT(openVideoTab()));
    connect(timerVideo,SIGNAL(timeout()),this,SLOT(grabAndProcessFrameVideo()));
    connect(ui->pbPlayVid,SIGNAL(clicked()),this,SLOT(startStopGrabbingAndShowingVideo()));
    connect(ui->pbRecordVid,SIGNAL(clicked()),this,SLOT(startStopRecordingMovieVideo()));
    connect(ui->pbChooseFrameVid,SIGNAL(clicked()),this,SLOT(loadCurrentVideoFrame()));
    connect(ui->sliderFPSVid,SIGNAL(sliderMoved(int)),this,SLOT(FPSChanged(int)));
    connect(ui->pbPopFromToolchainVid,SIGNAL(clicked()),this,SLOT(removeLastFunctionOfVideoToolchain()));
    connect(ui->sliderCurrentFramePos, SIGNAL(sliderReleased()), this, SLOT(sliderCurrentFramePosChanged()));
    connect(ui->pbNextVid, SIGNAL(clicked()),this,SLOT(nextVideo()));
    connect(ui->pbPrevVid, SIGNAL(clicked()), this, SLOT(prevVideo()));
    connect(ui->sliderFPSVid, SIGNAL(valueChanged(int)), this, SLOT(FPSChangedVid(int)));
    connect(ui->sliderCurrentFramePos, SIGNAL(sliderPressed()), this, SLOT(sliderPressedStart()));
    connect(ui->sliderCurrentFramePos, SIGNAL(sliderReleased()), this, SLOT(sliderPressedStop()));
    connect(ui->sliderCurrentFramePos, SIGNAL(sliderMoved(int)), this, SLOT(sliderCurrentFramePosChanged()));
}

EAMViewer::~EAMViewer()
{
    delete diallintrans;
    delete dialgammatrans;
    delete dialthresh;
    delete dialadaptthresh;
    delete dialblur;
    delete dialmedblur;
    delete dialgauss;
    delete dialsobel;
    delete dialdilate;
    delete dialerode;
    delete dialcustfilt;
    delete diallaplace;
    delete dialscharr;
    delete dialcanny;
    delete dialhoughlines;
    delete dialhoughcircles;
    delete dialcornerdetect;
    delete dialmser;
    delete dialfast;
    delete dialorb;
    delete dialbrisk;
    delete dialfreak;
    delete dialmsereval;

    delete simpleFilterDataValues;

    timer->stop();
    delete timer;
    timerVideo->stop();
    delete timerVideo;
    timerRefreshHoughLinesTbl->stop();
    delete timerRefreshHoughLinesTbl;
    timerRefreshHoughLinesTblVideo->stop();
    delete timerRefreshHoughLinesTblVideo;
    timerRefreshHoughCirclesTbl->stop();
    delete timerRefreshHoughCirclesTbl;
    timerRefreshHoughCirclesTblVideo->stop();
    delete timerRefreshHoughCirclesTblVideo;
    timerRefreshCornersTbl->stop();
    delete timerRefreshCornersTbl;
    timerRefreshCornersTblVideo->stop();
    delete timerRefreshCornersTblVideo;
    timerRefreshMSERTbl->stop();
    delete timerRefreshMSERTbl;
    timerRefreshMSERTblVideo->stop();
    delete timerRefreshMSERTblVideo;
    timerRefreshFASTTbl->stop();
    delete timerRefreshFASTTbl;
    timerRefreshFASTTblVideo->stop();
    delete timerRefreshFASTTblVideo;
    timerRefreshORBTbl->stop();
    delete timerRefreshORBTbl;
    timerRefreshORBTblVideo->stop();
    delete timerRefreshORBTblVideo;
    timerRefreshBRISKTbl->stop();
    delete timerRefreshBRISKTbl;
    timerRefreshBRISKTblVideo->stop();
    delete timerRefreshBRISKTblVideo;
    timerRefreshFREAKTbl->stop();
    delete timerRefreshFREAKTbl;
    timerRefreshFREAKTblVideo->stop();
    delete timerRefreshFREAKTblVideo;
    timerRefreshMSEREvalTbl->stop();
    delete timerRefreshMSERTbl;
    timerRefreshMSEREvalTblVideo->stop();
    delete timerRefreshMSERTblVideo;

    delete scene0;
    delete scene1;
    delete scene2;
    delete scene3;
    delete scene4;
    delete scene5;
    delete scene6;
    delete scene7;

    delete sceneColorImage;
    delete sceneGrayImage;
    delete sceneProcessedGrayImage;
    delete sceneGrayHistogram;
    delete sceneProcessedColorImage;
    delete sceneColorHistogram;

    delete sceneROI;
    delete sceneROIHist;

    delete ui;
    for(h = 0; h < ROIDBItems.size(); h++)
        delete ROIDBWidgetItems.at(h);
    for( int u = 0; u < TMViews.size(); u++)
    {
        QGraphicsView *GV = TMViews.at(u);
        QGraphicsScene *GS = GV->scene();
        delete GV;
        delete GS;
    }
}

/// *** GUI methods *** ///

Mat  EAMViewer::calculatehistogram(Mat in)
{
    int histSize = 256;

    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;
    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    if(in.channels() == 3)
    {
        vector<Mat> bgr_planes;
        split( in, bgr_planes);
        Mat b_hist, g_hist, r_hist;

        calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

        Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

        normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );


        for( int i = 1; i < histSize; i++ )
        {
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                             Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                             Scalar( 255, 0, 0), 2, 8, 0  );
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                             Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                             Scalar( 0, 255, 0), 2, 8, 0  );
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                             Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                             Scalar( 0, 0, 255), 2, 8, 0  );
         }

        return histImage;
    }
    else if (in.channels() == 1)
    {
        Mat g_hist;
        calcHist( &in, 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );

        Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX,-1, Mat() );

        for( int i = 1; i < histSize; i++ )
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                             Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                             Scalar( 255, 255, 255),2 , 8, 0  );

        return histImage;
    }
    return Mat();
    newLineInText("No known format!");
}

void EAMViewer::calculateEllipses(vector<vector<Point> > &BlobPoints, vector<vector<Point> > &BlobHulls,vector<RotatedRect> &BlobEllipses)
{
    BlobEllipses.clear();
    for(unsigned int h = 0; h < BlobPoints.size(); h++)
    {
        vector<Point> vec,vecHelp = BlobHulls[h];
        unsigned int vecSize = vecHelp.size();
        if( vecSize < 5)
            vec = BlobPoints[h];
        else
            vec = BlobHulls[h];

        RotatedRect box = fitEllipse( vec );
        BlobEllipses.push_back(box);
    }
}

void EAMViewer::calculateHulls(vector<vector<Point> > &BlobPoints, vector<vector<Point> > &BlobHulls)
{
    BlobHulls.clear();
    for(int h = 0; h < int(BlobPoints.size()); h++)
    {
        vector<Point> hullpoints;
        convexHull( BlobPoints[h], hullpoints);
        BlobHulls.push_back(hullpoints);
    }
}

void EAMViewer::clearROI()
{
    ROI.~Mat();
    ROIHist.~Mat();
    sceneROI->clear();
    sceneROIHist->clear();
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tbCurrentROI));
}

void EAMViewer::clearScenes()
{
    scene0->clear();
    scene1->clear();
    scene2->clear();
    scene3->clear();
    scene4->clear();
    scene5->clear();
    scene6->clear();
    scene7->clear();

    sceneColorImage->clear();
    sceneGrayImage->clear();
    sceneProcessedGrayImage->clear();
    sceneGrayHistogram->clear();
    sceneProcessedColorImage->clear();
    sceneColorHistogram->clear();
}

void EAMViewer::closeAllDialogs()
{
    closeflag = false;
    diallintrans->close();
    dialgammatrans->close();
    dialthresh->close();
    dialadaptthresh->close();
    dialblur->close();
    dialmedblur->close();
    dialgauss->close();
    dialsobel->close();
    dialdilate->close();
    dialerode->close();
    dialcustfilt->close();
    diallaplace->close();
    dialscharr->close();
    dialcanny->close();
    dialhoughlines->close();
    dialhoughcircles->close();
    dialcornerdetect->close();
    dialmser->close();
    dialfast->close();
    dialorb->close();
    dialbrisk->close();
    dialfreak->close();
    dialmsereval->close();
    closeflag = true;
}

void EAMViewer::clearTMData()
{
    int n = TMViews.size();
    for(int u = 0; u < n; u++)
    {
        EventsQGraphicsView *GV = TMViews.at(0);
        QGraphicsScene *GS = GV->scene();
        GS->clear();
        QSMTMKeyPressEvent->removeMappings(GV);
        delete GV;
        delete GS;
        TMViews.removeAt(0);
    }
}

void EAMViewer::disableTabChanging(int i)
{
    if(i != 0)
        ui->tbColorImage->setVisible(false); //->setEnabled(false);
    if(i != 1)
        ui->tbGrayImage->setVisible(false); //->setEnabled(false);
    if(i != 2)
        ui->tbProcGrayImage->setVisible(false); //->setEnabled(false);
    if(i != 3)
        ui->tbGrayHist->setVisible(false); //->setEnabled(false);
    if(i != 5)
        ui->tbProcColorImage->setVisible(false); //->setEnabled(false);
    if(i != 6)
        ui->tbColorHist->setVisible(false); //->setEnabled(false);
    if(i != 8)
        ui->tbOverview->setVisible(false); //->setEnabled(false);
    if(i != 9)
        ui->tbCurrentROI->setVisible(false); //->setEnabled(false);
    if(i != 10)
        ui->tbROIDataBase->setVisible(false); //->setEnabled(false);
    if(i != 11)
        ui->tbTemplate->setVisible(false); //->setEnabled(false);
    if(i != 12)
        ui->tbCamera->setVisible(false); //->setEnabled(false);
    if(i != 13)
        ui->tbVideo->setVisible(false); //->setEnabled(false);
}

void EAMViewer::drawBlobEllipses(vector<RotatedRect> &BlobEllipses, int thickness)
{
    if(index < 12)
    {
        RNG rng;
        for(unsigned int h = 0; h < BlobEllipses.size(); h++)
        {
            RotatedRect box = BlobEllipses[h];
            int c1 = rng.operator ()(255);
            int c2 = rng.operator ()(255);
            int c3 = rng.operator ()(255);

            if(index != 9 && index != 12 && index != 13)
                ellipse( matdrawn, box, Scalar(c1, c2, c3), thickness );
            else if(index == 9)
                ellipse( ROIdrawn, box, Scalar(c1, c2, c3), thickness );

        }
    }

    if(index >= 12)
    {
        RNG rng;
        for(unsigned int h = 0; h < BlobEllipses.size(); h++)
        {
            RotatedRect box = BlobEllipses[h];
            int c1 = rng.operator ()(255);
            int c2 = rng.operator ()(255);
            int c3 = rng.operator ()(255);
            if(index == 12)
                ellipse( camImg, box, Scalar(c1, c2, c3), thickness );
            if(index == 13)
                ellipse( vidImg, box, Scalar(c1, c2, c3), thickness );
        }
    }

    if(index != 9 && index != 12 && index != 13)
        resetSinglePic(matdrawn,2);
    if(index == 9)
        resetSinglePic(ROIdrawn,ROIIMG);

}

void EAMViewer::drawBlobHulls(vector<vector<Point> > &blobs, int thickness)
{
    if(index < 12)
    {
        RNG rng;
        for(unsigned int h = 0; h < blobs.size(); h++)
        {
            vector<Point> vec = blobs[h];
            int c1 = rng.operator ()(255);
            int c2 = rng.operator ()(255);
            int c3 = rng.operator ()(255);

            for(unsigned int i = 0; i < (vec.size() - 1); i++)
            {
                Point p1 = vec[i];
                Point p2 = vec[i + 1];

                if(index != 9 && index != 12 && index != 13)
                    line( matdrawn, p1, p2, Scalar( c1, c2, c3 ), thickness);
                else if(index == 9)
                    line( ROIdrawn, p1, p2, Scalar( c1, c2, c3 ), thickness);
            }
            Point p1 = vec[vec.size() - 1];
            Point p2 = vec[0];

            if(index != 9 && index != 12 && index != 13)
                line( matdrawn, p1, p2, Scalar( c1, c2, c3 ), thickness);
            else if(index == 9)
                line( ROIdrawn, p1, p2, Scalar( c1, c2, c3 ), thickness);
        }
    }

    if(index >= 12)
    {
        RNG rng;
        for(unsigned int h = 0; h < blobs.size(); h++)
        {            
            int c1 = rng.operator ()(255);
            int c2 = rng.operator ()(255);
            int c3 = rng.operator ()(255);
            vector<Point> vec = blobs[h];
            for(unsigned int i = 0; i < vec.size() -1 ; i++)
            {
                Point p1 = vec[i];
                Point p2 = vec[i + 1];
                if(index == 12)
                    line( camImg, p1, p2, Scalar( c1, c2, c3 ), thickness);
                if(index == 13)
                    line( vidImg, p1, p2, Scalar( c1, c2, c3 ), thickness);
            }
            Point p1 = vec[0];
            Point p2 = vec[vec.size() - 1];
            if(index == 12)
                line( camImg, p1, p2, Scalar( c1, c2, c3 ), thickness);
            if(index == 13)
                line( vidImg, p1, p2, Scalar( c1, c2, c3 ), thickness);

        }
    }

    if(index != 9 && index != 12 && index != 13)
        resetSinglePic(matdrawn,2);
    if(index == 9)
        resetSinglePic(ROIdrawn,ROIIMG);
}

void EAMViewer::drawBlobPoints(vector<vector<Point> > &blobs, int thickness)
{
    if(index < 12)
    {
        RNG rng;
        for(unsigned int h = 0; h < blobs.size(); h++)
        {
            vector<Point> vec = blobs[h];
            int c1 = rng.operator ()(255);
            int c2 = rng.operator ()(255);
            int c3 = rng.operator ()(255);
            for(unsigned int i = 0; i < vec.size(); i++)
            {
                Point p = vec[i];
                if(index != 9 && index != 12 && index != 13)
                {
                    if(i%50 == 0)
                    circle( matdrawn, p, 3, Scalar( c1, c2, c3 ), thickness );
                }
                else if(index == 9)
                    if(i%50 == 0)
                        circle( ROIdrawn, p, 3, Scalar( c1, c2, c3 ), thickness );
            }
        }
    }

    if(index >= 12)
    {
        RNG rng;
        for(unsigned int h = 0; h < blobs.size(); h++)
        {            
            int c1 = rng.operator ()(255);
            int c2 = rng.operator ()(255);
            int c3 = rng.operator ()(255);
            vector<Point> vec = blobs[h];
            for(unsigned int i = 0; i < vec.size(); i++)
            {
                Point p = vec[i];
                if(index == 12)
                    if(i%50 == 0)
                        circle( camImg, p, 4, Scalar( c1, c2, c3 ), thickness, 8, 0 );
                if(index == 13)
                    if(i%50 == 0)
                        circle( vidImg, p, 4, Scalar( c1, c2, c3 ), thickness, 8, 0 );
            }
        }
    }

    if(index != 9 && index != 12 && index != 13)
        resetSinglePic(matdrawn,2);
    if(index == 9)
        resetSinglePic(ROIdrawn,ROIIMG);
}

void EAMViewer::drawKeyPoints(vector<KeyPoint> &keyPoints)
{
    if(index < 12)
    {
            if(index != 9)
                drawKeypoints(matdrawn,keyPoints,matdrawn,Scalar(0,255,0),DrawMatchesFlags::DEFAULT);
            else if(index == 9)
                drawKeypoints(ROIdrawn,keyPoints,matdrawn,Scalar(0,255,0),DrawMatchesFlags::DEFAULT);
    }

    if(index == 12)
        drawKeypoints(camImg, keyPoints, camImg, Scalar(0,255,0),DrawMatchesFlags::DEFAULT);
    if(index == 13)
        drawKeypoints(vidImg, keyPoints, vidImg, Scalar(0,255,0),DrawMatchesFlags::DEFAULT);

    if(index != 9 && index != 12 && index != 13)
        resetSinglePic(matdrawn,2);
    if(index == 9)
        resetSinglePic(ROIdrawn,ROIIMG);
}

void EAMViewer::drawLines(vector<Vec2f> &Lines)
{
    int color = dialhoughlines->color;
    int thickness = dialhoughlines->lineThickness;

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    else if(index < 12)
        matdrawn = matbuffg.clone();

    for(unsigned int i = 0; i < Lines.size(); i++ )
    {
        Point pt1, pt2;
        double rho = Lines[i][0], theta = Lines[i][1];
            
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));

        
        if(index == 9)
            line( ROIdrawn, pt1, pt2, Scalar(color,color,color),thickness);
        if(index != 9)
            line( matdrawn, pt1, pt2, Scalar(color,color,color),thickness);
        if(index == 12)
            line( camImg, pt1, pt2, Scalar(color, color, color), thickness);
        if(index == 13)
            line( vidImg, pt1, pt2, Scalar(color, color, color), thickness);        
    }
}

void EAMViewer::drawLines(vector<Vec4i> &Lines)
{
    int color = dialhoughlines->color;
    int thickness = dialhoughlines->lineThickness;

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    else if(index < 12)
        matdrawn = matbuffg.clone();

    for(unsigned int i = 0; i < Lines.size(); i++ )
    {
        Vec4i l = Lines[i];
        Point pt1 = Point(l[0], l[1]);
        Point pt2 = Point(l[2], l[3]);

        if(index == 9)
            line( ROIdrawn, pt1, pt2, Scalar(color,color,color),thickness);
        if(index != 9)
            line( matdrawn, pt1, pt2, Scalar(color,color,color),thickness);
        if(index == 12)
            line( camImg, pt1, pt2, Scalar(color, color, color), thickness);
        if(index == 13)
            line( vidImg, pt1, pt2, Scalar(color, color, color), thickness);
    }
}

void EAMViewer::enableTabChanging()
{
    ui->tbColorImage->setEnabled(true);
    ui->tbGrayImage->setEnabled(true);
    ui->tbGrayHist->setEnabled(true);
    ui->tbProcColorImage->setEnabled(true);
    ui->tbColorHist->setEnabled(true);
    ui->tbOverview->setEnabled(true);
    ui->tbCurrentROI->setEnabled(true);
    ui->tbROIDataBase->setEnabled(true);
    ui->tbTemplate->setEnabled(true);
    ui->tbCamera->setEnabled(true);
}

void EAMViewer::evaluateMSERData()
{

    MSEREvalPoints.clear();
    MSEREvalHulls.clear();
    MSEREvalEllipses.clear();
    if(index == 9)
    {
        MSEREvalPoints  = MSERPointsROI;
        MSEREvalHulls   = MSERHullsROI;
        MSEREvalEllipses= MSEREllipsesROI;
    }
    else if(index < 12)
    {
        MSEREvalPoints  = MSERPoints;
        MSEREvalHulls   = MSERHulls;
        MSEREvalEllipses= MSEREllipses;
    }
    if(index == 12)
    {
        MSEREvalPoints = MSERPointsCam;
        MSEREvalHulls = MSERHullsCam;
        MSEREvalEllipses = MSEREllipsesCam;
    }
    if(index == 13)
    {
        MSEREvalPoints = MSERPointsVid;
        MSEREvalHulls = MSERHullsVid;
        MSEREvalEllipses = MSEREllipsesVid;
    }

    if(MSEREvalHulls.size() == 0)
        calculateHulls(MSEREvalPoints, MSEREvalHulls);
    if(MSEREvalEllipses.size() == 0) 
        calculateEllipses(MSEREvalPoints, MSEREvalHulls, MSEREvalEllipses);


    removeMSERDataOutOfIntervall();
    removeMSERDataOutOfRatioIntervall();
    if(MSEREvalSortBySize)
        sortEvalMSERDataBySize();
    if(MSEREvalSortByHull)
        sortEvalMSERDataByHulls();
    drawMSEREvalFeatures();
}

void EAMViewer::fillDataInModel(QStandardItemModel* mdl, unsigned int maxLength)
{
   if(functionFlag == 18)
   {
       unsigned int length = 0;
       if(!dialhoughlines->prob)
       {
           QStandardItem* qsi0 = new QStandardItem(tr("rho"));
           QStandardItem* qsi1 = new QStandardItem(tr("theta"));
           stItMHoughLines->setHorizontalHeaderItem(0,qsi0);
           stItMHoughLines->setHorizontalHeaderItem(1,qsi1);

           if(index == 9)
               length = calcLinesHoughROI.size();
           else if(index < 12)
               length = linesHough.size();
           else if(index == 12)
               length = calcLinesHoughCam.size();
           else if(index == 13)
               length = calcLinesHoughVideo.size();
       }
       if(dialhoughlines->prob)
       {
           QStandardItem* qsi0 = new QStandardItem(tr("x1"));
           QStandardItem* qsi1 = new QStandardItem(tr("y1"));
           QStandardItem* qsi2 = new QStandardItem(tr("x2"));
           QStandardItem* qsi3 = new QStandardItem(tr("y2"));
           stItMHoughLines->setHorizontalHeaderItem(0,qsi0);
           stItMHoughLines->setHorizontalHeaderItem(1,qsi1);
           stItMHoughLines->setHorizontalHeaderItem(2,qsi2);
           stItMHoughLines->setHorizontalHeaderItem(3,qsi3);
           if(index == 9)
               length = calcLinesHoughPROI.size();
           else if(index < 12)
               length = linesHoughP.size();
           else if(index == 12)
               length = calcLinesHoughPCam.size();
           else if(index == 13)
               length = calcLinesHoughPVideo.size();

       }

       for(unsigned int i = 0; i < length; i++)
       {
           QString hstr0, hstr1, hstr2, hstr3;
           if(!dialhoughlines->prob)
           {
               if(index == 9)
               {
                   hstr0.setNum(calcLinesHoughROI[i][0]);
                   hstr1.setNum(calcLinesHoughROI[i][1]);
               }
               else if(index < 12)
               {
                   hstr0.setNum(linesHough[i][0]);
                   hstr1.setNum(linesHough[i][1]);
               }
               if(index == 12)
               {
                   hstr0.setNum(calcLinesHoughCam[i][0]);
                   hstr1.setNum(calcLinesHoughCam[i][1]);
               }
               if(index == 13)
               {
                   hstr0.setNum(calcLinesHoughVideo[i][0]);
                   hstr1.setNum(calcLinesHoughVideo[i][1]);
               }
               mdl->setData(mdl->index(i,0),hstr0);
               mdl->setData(mdl->index(i,1),hstr1);
           }
           if(dialhoughlines->prob)
           {
               if(index == 9)
               {
                   hstr0.setNum(calcLinesHoughPROI[i][0]);
                   hstr1.setNum(calcLinesHoughPROI[i][1]);
                   hstr2.setNum(calcLinesHoughPROI[i][2]);
                   hstr3.setNum(calcLinesHoughPROI[i][3]);
               }
               else if(index < 12)
               {
                   hstr0.setNum(linesHoughP[i][0]);
                   hstr1.setNum(linesHoughP[i][1]);
                   hstr2.setNum(linesHoughP[i][2]);
                   hstr3.setNum(linesHoughP[i][3]);
               }
               if(index == 12)
               {
                   hstr0.setNum(calcLinesHoughPCam[i][0]);
                   hstr1.setNum(calcLinesHoughPCam[i][1]);
                   hstr2.setNum(calcLinesHoughPCam[i][2]);
                   hstr3.setNum(calcLinesHoughPCam[i][3]);
               }
               if(index == 13)
               {
                   hstr0.setNum(calcLinesHoughPVideo[i][0]);
                   hstr1.setNum(calcLinesHoughPVideo[i][1]);
                   hstr2.setNum(calcLinesHoughPVideo[i][2]);
                   hstr3.setNum(calcLinesHoughPVideo[i][3]);
               }
               mdl->setData(mdl->index(i,0),hstr0);
               mdl->setData(mdl->index(i,1),hstr1);
               mdl->setData(mdl->index(i,2),hstr2);
               mdl->setData(mdl->index(i,3),hstr3);
           }
       }
   }
   if(functionFlag == 19)
   {
       QStandardItem* qsi0 = new QStandardItem(tr("x"));
       QStandardItem* qsi1 = new QStandardItem(tr("y"));
       QStandardItem* qsi2 = new QStandardItem(tr("radius"));
       stItMHoughCircles->setHorizontalHeaderItem(0,qsi0);
       stItMHoughCircles->setHorizontalHeaderItem(1,qsi1);
       stItMHoughCircles->setHorizontalHeaderItem(2,qsi2);       

       if(index == 9)
       {
           for(unsigned int i = 0; i < calcCirclesHoughROI.size(); i++)
           {
               QString hstr0,hstr1,hstr2;
               hstr0.setNum(calcCirclesHoughROI[i][0]);
               hstr1.setNum(calcCirclesHoughROI[i][1]);
               hstr2.setNum(calcCirclesHoughROI[i][2]);
               mdl->setData(mdl->index(i,0),hstr0);
               mdl->setData(mdl->index(i,1),hstr1);
               mdl->setData(mdl->index(i,2),hstr2);
           }
       }
       else if(index > 12)
       {
           for(unsigned int i = 0; i < circlesHough.size(); i++)
           {
               QString hstr0,hstr1,hstr2;
               hstr0.setNum(circlesHough[i][0]);
               hstr1.setNum(circlesHough[i][1]);
               hstr2.setNum(circlesHough[i][2]);
               mdl->setData(mdl->index(i,0),hstr0);
               mdl->setData(mdl->index(i,1),hstr1);
               mdl->setData(mdl->index(i,2),hstr2);
           }
       }

       if(index == 12)
            for(unsigned int i = 0; i < calcCirclesHoughCam.size(); i++)
            {
                QString hstr0,hstr1,hstr2;
                hstr0.setNum(calcCirclesHoughCam[i][0]);
                hstr1.setNum(calcCirclesHoughCam[i][1]);
                hstr2.setNum(calcCirclesHoughCam[i][2]);
                mdl->setData(mdl->index(i,0),hstr0);
                mdl->setData(mdl->index(i,1),hstr1);
                mdl->setData(mdl->index(i,2),hstr2);
            }
       if(index == 13)
            for(unsigned int i = 0; i < calcCirclesHoughVideo.size(); i++)
            {
                QString hstr0,hstr1,hstr2;
                hstr0.setNum(calcCirclesHoughVideo[i][0]);
                hstr1.setNum(calcCirclesHoughVideo[i][1]);
                hstr2.setNum(calcCirclesHoughVideo[i][2]);
                mdl->setData(mdl->index(i,0),hstr0);
                mdl->setData(mdl->index(i,1),hstr1);
                mdl->setData(mdl->index(i,2),hstr2);
            }
   }
   if(functionFlag == 20)
   {
       QStandardItem* qsi0 = new QStandardItem(tr("x"));
       QStandardItem* qsi1 = new QStandardItem(tr("y"));
       stItMCorners->setHorizontalHeaderItem(0,qsi0);
       stItMCorners->setHorizontalHeaderItem(1,qsi1);

       unsigned int length = 0;
       if(index == 9)
           length = cornersROI.size();
       else if(index < 12)
           length = corners.size();
       else if(index == 12)
           length = cornersCam.size();
       else if(index == 13)
           length = cornersVideo.size();
       for(unsigned int i = 0; i < length; i++)
       {
           QString hstr0,hstr1;
           if(index == 9)
           {
               hstr0.setNum(cornersROI[i][0]);
               hstr1.setNum(cornersROI[i][1]);
           }
           else if(index < 12)
           {
               hstr0.setNum(corners[i][0]);
               hstr1.setNum(corners[i][1]);
           }
           if(index == 12)
           {
               hstr0.setNum(cornersCam[i][0]);
               hstr1.setNum(cornersCam[i][1]);
           }
           if(index == 13)
           {
               hstr0.setNum(cornersVideo[i][0]);
               hstr1.setNum(cornersVideo[i][1]);
           }
           mdl->setData(mdl->index(i,0),hstr0);
           mdl->setData(mdl->index(i,1),hstr1);
       }

   }
   if(functionFlag == 23)
   {
       QStandardItem* qsi0 = new QStandardItem(tr("x"));
       QStandardItem* qsi1 = new QStandardItem(tr("y"));
       mdl->setHorizontalHeaderItem(0,qsi0);
       mdl->setHorizontalHeaderItem(1,qsi1);
       unsigned int KPSize = 0;
       vector<KeyPoint> KPs;

       if(index < 12)
       {
           if(index == 9)
           {
               KPSize = FASTKeyPointsROI.size();
               KPs = FASTKeyPointsROI;
           }
           else
           {
                KPSize = FASTKeyPoints.size();
                KPs = FASTKeyPoints;
           }
       }
       if(index == 12)
       {
           KPSize = FASTKeyPointsCam.size();
           KPs = FASTKeyPointsCam;
       }

       if(index == 13)
       {
           KPSize = FASTKeyPointsVid.size();
           KPs = FASTKeyPointsVid;
       }

       for(unsigned int i = 0; i < KPSize; i++)
       {
           QString hstr0,hstr1;
           KeyPoint kp = KPs[i];
           hstr0.setNum(kp.pt.x);
           hstr1.setNum(kp.pt.y);
           mdl->setData(mdl->index(i,0),hstr0);
           mdl->setData(mdl->index(i,1),hstr1);
       }
   }
   if(functionFlag == 24)
   {
       QStandardItem* qsi0 = new QStandardItem(tr("x"));
       QStandardItem* qsi1 = new QStandardItem(tr("y"));
       mdl->setHorizontalHeaderItem(0,qsi0);
       mdl->setHorizontalHeaderItem(1,qsi1);
       unsigned int KPSize = 0;
       vector<KeyPoint> KPs;

       if(index < 12)
       {
           if(index == 9)
           {

               KPSize = ORBKeyPointsROI.size();
               KPs = ORBKeyPointsROI;
           }
           else
           {
               KPSize = ORBKeyPoints.size();
               KPs = ORBKeyPoints;
           }
       }
       if(index == 12)
       {
           KPSize = ORBKeyPointsCam.size();
           KPs = ORBKeyPointsCam;
       }

       if(index == 13)
       {
           KPSize = ORBKeyPointsVid.size();
           KPs = ORBKeyPointsVid;
       }

       for(unsigned int i = 0; i < KPSize; i++)
       {
           QString hstr0,hstr1;
           KeyPoint kp = KPs[i];
           hstr0.setNum(kp.pt.x);
           hstr1.setNum(kp.pt.y);
           mdl->setData(mdl->index(i,0),hstr0);
           mdl->setData(mdl->index(i,1),hstr1);
       }
   }
   if(functionFlag == 25)
   {
       QStandardItem* qsi0 = new QStandardItem(tr("x"));
       QStandardItem* qsi1 = new QStandardItem(tr("y"));
       mdl->setHorizontalHeaderItem(0,qsi0);
       mdl->setHorizontalHeaderItem(1,qsi1);
       unsigned int KPSize = 0;
       vector<KeyPoint> KPs;

       if(index < 12)
       {
           if(index == 9)
           {
                KPSize = BRISKKeyPointsROI.size();
                KPs = BRISKKeyPointsROI;
           }
           else
           {
               KPSize = BRISKKeyPoints.size();
               KPs = BRISKKeyPoints;
           }
       }
       if(index == 12)
       {
           KPSize = BRISKKeyPointsCam.size();
           KPs = BRISKKeyPointsCam;
       }

       if(index == 13)
       {
           KPSize = BRISKKeyPointsVid.size();
           KPs = BRISKKeyPointsVid;
       }

       for(unsigned int i = 0; i < KPSize; i++)
       {
           QString hstr0,hstr1;
           KeyPoint kp = KPs[i];
           hstr0.setNum(kp.pt.x);
           hstr1.setNum(kp.pt.y);
           mdl->setData(mdl->index(i,0),hstr0);
           mdl->setData(mdl->index(i,1),hstr1);
       }
   }
   if(functionFlag == 26)
   {
       QStandardItem* qsi0 = new QStandardItem(tr("x"));
       QStandardItem* qsi1 = new QStandardItem(tr("y"));
       mdl->setHorizontalHeaderItem(0,qsi0);
       mdl->setHorizontalHeaderItem(1,qsi1);
       unsigned int KPSize = 0;
       vector<KeyPoint> KPs;

       if(index < 12)
       {
           KPSize = FREAKKeyPoints.size();
           KPs = FREAKKeyPoints;
       }
       if(index == 12)
       {
           KPSize = FREAKKeyPointsCam.size();
           KPs = FREAKKeyPointsCam;
       }

       if(index == 13)
       {
           KPSize = FREAKKeyPointsVid.size();
           KPs = FREAKKeyPointsVid;
       }

       for(unsigned int i = 0; i < KPSize; i++)
       {
           QString hstr0,hstr1;
           KeyPoint kp = KPs[i];
           hstr0.setNum(kp.pt.x);
           hstr1.setNum(kp.pt.y);
           mdl->setData(mdl->index(i,0),hstr0);
           mdl->setData(mdl->index(i,1),hstr1);
       }
   }
   if(functionFlag == 29 || functionFlag == 30)
   {
       for(unsigned int h = 0; h < maxLength; h++)
       {
           QStandardItem* qsmHX = new QStandardItem(tr("x ") + QString::number(h));
           QStandardItem* qsmHY = new QStandardItem(tr("y ") + QString::number(h));
           mdl->setHorizontalHeaderItem(2*h    , qsmHX);
           mdl->setHorizontalHeaderItem(2*h +1 , qsmHY);
       }
       unsigned int hullSize = 0;

       if(functionFlag == 30)
           hullSize = MSEREvalHulls.size();
       else
       {
           if(index == 9)
               hullSize = MSERHullsROI.size();
           else if(index < 12)
               hullSize = MSERHulls.size();
           if(index == 12)
               hullSize = MSERHullsCam.size();
           if(index == 13)
               hullSize = MSERHullsVid.size();
       }

       for( unsigned int h = 0; h < hullSize; h++ )
       {
           QString hstr;
           QStandardItem* qsmV = new QStandardItem(tr("blob ") + hstr.setNum(h));
           mdl->setVerticalHeaderItem(h, qsmV);
           vector<Point> r;
           if(functionFlag == 30)
               r = MSEREvalHulls[h];
           else
           {
               if(index == 9)
                   r = MSERHullsROI[h];
               else if(index < 12)
                   r = MSERHulls[h];
               if(index == 12)
                   r = MSERHullsCam[h];
               if(index == 13)
                   r = MSERHullsVid[h];
           }

           for(unsigned int i = 0; i < r.size(); i++)
           {
               Point p = r[i];
               mdl->setData(mdl->index(int(h), int(2*i)    ) , QString::number(p.x));
               mdl->setData(mdl->index(int(h), int(2*i + 1)) , QString::number(p.y));
           }
           r.clear();
       }

   }
}

void EAMViewer::loadImages(int n)
{
    for( int h =0;h < 8; h++)
        zf[h] = 1;

    int f,b;
    f = n + 1;
    b = n - 1;

    if(n == 0)
        b = List.size() - 1;
    if(n == List.size() - 1)
        f = 0;

    img0 = imread(List.at(n).filePath().toStdString().data(),-1);
    img1 = imread(List.at(n).filePath().toStdString().data(),0);
    img2 = img1.clone();
    img3 = calculatehistogram(img2);
    img4 = imread(List.at(b).filePath().toStdString().data(),-1);
    img5 = img0.clone();
    img6 = calculatehistogram(img5);
    img7 = imread(List.at(f).filePath().toStdString().data(),-1);

    h0 = img0.rows;
    w0 = img0.cols;
    matbuffg = img2.clone();
    mattempg = img2.clone();
    matbuffc = img5.clone();
    mattempc = img5.clone();
}

void EAMViewer::loadVideoInBuffer()
{  
    if(!vidDev.open(ListVideos.at(VidNum).absoluteFilePath().toStdString()) == false)
    {
        newLineInText(tr("no video file found"));
        return;
    }
    while(true)
    {
        if(vidDev.read(vidImg) == false)
            break;
        VideoBuffer.push_back(vidImg.clone());
    }    
}

bool EAMViewer::loadVideoSize()
{
    ui->tbVideo->setDisabled(true);
    currentVideoFrame = 0;
    vidSize = 0;
    bool b = vidDev.open(ListVideos.at(VidNum).absoluteFilePath().toStdString());
    if(!b)
        return false;
    vidSize  = vidDev.get(CV_CAP_PROP_FRAME_COUNT);
    if(vidSize == 0)
    {
        while(true)
        {
            Mat img;
            if(vidDev.read(img) == false)
                break;
            vidSize++;
        }
        vidDev.set( CV_CAP_PROP_POS_FRAMES, 0);
    }
    ui->sliderCurrentFramePos->setMaximum(vidSize);
    ui->sliderCurrentFramePos->setValue(0);
    ui->tbVideo->setEnabled(true);
    return true;
}

void EAMViewer::loadVideoUntilFramePos()
{
    for(unsigned int h = 0; h <= currentVideoFrame; h++)
        vidDev.grab();
    vidDev.retrieve(vidImg);
}

void EAMViewer::loadPixmaps()
{
    pm[0] = QPixmap::fromImage(matToQImage(img0));
    pm[1] = QPixmap::fromImage(matToQImage(img1));
    pm[2] = QPixmap::fromImage(matToQImage(img2));
    pm[3] = QPixmap::fromImage(matToQImage(img3));
    pm[4] = QPixmap::fromImage(matToQImage(img4));
    pm[5] = QPixmap::fromImage(matToQImage(img5));
    pm[6] = QPixmap::fromImage(matToQImage(img6));
    pm[7] = QPixmap::fromImage(matToQImage(img7));

    QRect rect = geometry();

    clearScenes();

    scene0->addPixmap(pm[0].scaled(rect.width()*3/4,rect.height()*3/4));
    scene1->addPixmap(pm[1].scaled(rect.width()*1/4,rect.height()*1/4));
    scene2->addPixmap(pm[2].scaled(rect.width()*1/4,rect.height()*1/4));
    scene3->addPixmap(pm[3].scaled(rect.width()*1/4,rect.height()*1/4));
    scene4->addPixmap(pm[4].scaled(rect.width()*1/4,rect.height()*1/4));
    scene5->addPixmap(pm[5].scaled(rect.width()*1/4,rect.height()*1/4));
    scene6->addPixmap(pm[6].scaled(rect.width()*1/4,rect.height()*1/4));
    scene7->addPixmap(pm[7].scaled(rect.width()*1/4,rect.height()*1/4));

    int h0 = img0.rows;
    int w0 = img0.cols;

    sceneColorImage->addPixmap(pm[0].scaled(w0*zf[0],h0*zf[0]));
    sceneGrayImage->addPixmap(pm[1].scaled(w0*zf[1],h0*zf[1]));
    sceneProcessedGrayImage->addPixmap(pm[2].scaled(w0*zf[2],h0*zf[2]));
    sceneGrayHistogram->addPixmap(pm[3].scaled(w0*zf[3],h0*zf[3]));
    sceneProcessedColorImage->addPixmap(pm[5].scaled(w0*zf[5],h0*zf[5]));
    sceneColorHistogram->addPixmap(pm[6].scaled(w0*zf[6],h0*zf[6]));

}

QImage EAMViewer::matToQImage(Mat &mat )
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
    newLineInText(tr("No known format."));
    return QImage();
}

void EAMViewer::newLineInText(QString text)
{
    QString hstr;
    hstr = hstr.setNum(nline) + tr(". ") + text;
    ui->textEdit->append(hstr);
    nline++;
}

void EAMViewer::nextPic()
{
    closeAllDialogs();
    clearROI();
    PicNum++;
    if(PicNum == List.size())
        PicNum = 0;
    loadImages(PicNum);
    loadPixmaps();
    newLineInText(tr("loaded  ") + List.at(PicNum).fileName());
}

void EAMViewer::previousPic()
{
    closeAllDialogs();
    clearROI();
    PicNum--;
    if(PicNum == -1)
        PicNum = List.size() - 1;
    loadImages(PicNum);
    loadPixmaps();
    newLineInText(tr("loaded  ") + List.at(PicNum).fileName());
}

void EAMViewer::refreshTblBRISKKeyPoints(vector<KeyPoint> &keyPoints)
{
    delete stItBRISK;
    stItBRISK = new QStandardItemModel(keyPoints.size(),2);
    fillDataInModel(stItBRISK);
    dialbrisk->addModel(stItBRISK);
}

void EAMViewer::refreshCornersTbldata(vector<Vec2i> &corn)
{
    delete stItMCorners;
    stItMCorners =  new QStandardItemModel(corn.size(),2,this);
    fillDataInModel(stItMCorners);
    dialcornerdetect->addModel(stItMCorners);
}

void EAMViewer::refreshHoughCirclesTbldata(vector<Vec3f> &cHough)
{
    delete stItMHoughCircles;
    stItMHoughCircles = new QStandardItemModel(cHough.size(),3,this);
    fillDataInModel(stItMHoughCircles);
    dialhoughcircles->addModel(stItMHoughCircles);
}

void EAMViewer::refreshHoughLinesTbldata(vector<Vec2f> &lHough)
{
    delete stItMHoughLines;
    stItMHoughLines = new QStandardItemModel(lHough.size(),2);
    fillDataInModel(stItMHoughLines);
    dialhoughlines->addModel(stItMHoughLines);
}

void EAMViewer::refreshHoughLinesPTbldata(vector<Vec4i> &lHoughP)
{
    delete stItMHoughLines;
    stItMHoughLines = new QStandardItemModel(lHoughP.size(),4,this);
    fillDataInModel(stItMHoughLines);
    dialhoughlines->addModel(stItMHoughLines);
}

void EAMViewer::refreshTblFASTKeyPoints(vector<KeyPoint> &keyPoints)
{
    delete stItFAST;
    stItFAST = new QStandardItemModel(keyPoints.size(),2);
    fillDataInModel(stItFAST);
    dialfast->addModel(stItFAST);
}

void EAMViewer::refreshTblFREAKKeyPoints(vector<KeyPoint> &keyPoints)
{
    delete stItFREAK;
    stItFREAK = new QStandardItemModel(keyPoints.size(),2);
    fillDataInModel(stItFREAK);
    dialfreak->addModel(stItFREAK);
}

void EAMViewer::refreshTblMSERPoints(vector<vector<Point> > &blobs)
{

    delete stItMSER;
    unsigned int maxLength = 0;
    for( unsigned int h = 0; h < blobs.size(); h++ )
    {
        vector<Point> r = blobs[h];
        if( maxLength < r.size())
            maxLength = r.size();
    }

    stItMSER = new QStandardItemModel(blobs.size(), maxLength, this);
    fillDataInModel( stItMSER, maxLength);
    dialmser->addModell(stItMSER);

}

void EAMViewer::refreshTblMSEREvalPoints(vector<vector<Point> > &blobs)
{

    delete stItMSEREval;
    unsigned int maxLength = 0;
    for( unsigned int h = 0; h < blobs.size(); h++ )
    {
        vector<Point> r = blobs[h];
        if( maxLength < r.size())
            maxLength = r.size();
    }

    stItMSEREval = new QStandardItemModel(blobs.size(), maxLength, this);
    fillDataInModel( stItMSEREval, maxLength);
    dialmsereval->addModel(stItMSEREval);

}

void EAMViewer::refreshTblORBKeyPoints(vector<KeyPoint> &keyPoints)
{
    delete stItORB;
    stItORB = new QStandardItemModel(keyPoints.size(),2);
    fillDataInModel(stItORB);
    dialorb->addModel(stItORB);
}

void EAMViewer::removeEdgePoints(vector<Point> &points)
{
    for(unsigned int h = 0; h < points.size(); h++)
    {
        Point p = points[h];
        if(p.x < 5)
            points.erase(points.begin() + h);
    }
}

void EAMViewer::removeEdgePoints(vector<vector<Point> > &blobs)
{
    vector<vector<Point> > bl(blobs);
    blobs.clear();
    for(unsigned int i = 0; i < bl.size(); i++)
    {
        vector<Point> vecBlob = bl[i];
        vector<Point> vec;
        for(unsigned int h = 0; h < vecBlob.size(); h++)
        {
            Point p = vecBlob[h];
            if(p.y > 100 )
                vec.push_back(p);
        }
        if(vec.size() != 0)
            blobs.push_back(vec);
    }
}

void EAMViewer::removeMSERDataOutOfIntervall()
{
    vector<vector<Point>> help1, help2;
    vector<RotatedRect> help3;
    double AMax = 0;
    vector<double> vecA, helpA;
    for(unsigned int h = 0; h < MSEREvalPoints.size(); h++)
    {
        RotatedRect rec = MSEREvalEllipses[h];
        Point2f vertices[4];
        rec.points(vertices);

        double l1 = sqrt(double((vertices[1].x - vertices[0].x)*(vertices[1].x - vertices[0].x)) + double((vertices[1].y - vertices[0].y)*(vertices[1].y - vertices[0].y)))/2.0;
        double l2 = sqrt(double((vertices[2].x - vertices[1].x)*(vertices[2].x - vertices[1].x)) + double((vertices[2].y - vertices[1].y)*(vertices[2].y - vertices[1].y)))/2.0;
        double A = pi*l1*l2;
        if(AMax < A)
            AMax = A;
        vecA.push_back(A);
    }
    for(unsigned int h = 0; h < vecA.size(); h++)
    {
        double A = vecA[h]/AMax;
        helpA.push_back(A);
    }

    vecA = helpA;
    for(unsigned int h = 0; h < vecA.size(); h++)
        if((vecA[h] > MSEREvalMinSize) && (vecA[h] < MSEREvalMaxSize) )
        {
            help1.push_back(MSEREvalPoints[h]);
            help2.push_back(MSEREvalHulls[h]);
            help3.push_back(MSEREvalEllipses[h]);
        }
    MSEREvalPoints.clear();
    MSEREvalHulls.clear();
    MSEREvalEllipses.clear();
    MSEREvalPoints = help1;
    MSEREvalHulls = help2;
    MSEREvalEllipses = help3;
}

void EAMViewer::removeMSERDataOutOfRatioIntervall()
{
    vector<vector<Point>> help1, help2;
    vector<RotatedRect> help3;
    for(unsigned int h = 0; h < MSEREvalEllipses.size(); h++)
    {
        RotatedRect rec = MSEREvalEllipses[h];
        Point2f vertices[4];
        rec.points(vertices);
        double l1 = sqrt(double((vertices[1].x* - vertices[0].x)*(vertices[1].x* - vertices[0].x)) + double((vertices[1].y - vertices[0].y)*(vertices[1].y - vertices[0].y))  );
        double l2 = sqrt(double((vertices[2].x* - vertices[1].x)*(vertices[2].x* - vertices[1].x)) + double((vertices[2].y - vertices[1].y)*(vertices[2].y - vertices[1].y))  );
        double ratio = 0;
        if(l1 < l2)
            ratio = l1/l2;
        else
            ratio = l2/l1;

        if(ratio >= MSEREvalMinRatio && ratio <= MSEREvalMaxRatio )
        {
            help1.push_back(MSEREvalPoints[h]);
            help2.push_back(MSEREvalHulls[h]);
            help3.push_back(MSEREvalEllipses[h]);
        }
    }
    MSEREvalPoints.clear();
    MSEREvalHulls.clear();
    MSEREvalEllipses.clear();
    MSEREvalPoints = help1;
    MSEREvalHulls = help2;
    MSEREvalEllipses = help3;
}

void EAMViewer::resetSinglePic(Mat img, int i)
{
    if(i < ROIIMG)
        pm[i] = QPixmap::fromImage(matToQImage(img));
    if(i == ROIIMG)
        pmROI[0] = QPixmap::fromImage(matToQImage(img));
    if(i == ROIHIST)
        pmROI[1] = QPixmap::fromImage(matToQImage(img));

    QRect rect = geometry();

    if(i == 0)
    {
         scene0->clear();
         sceneColorImage->clear();
         scene0->addPixmap(pm[0].scaled(rect.width()*3/4,rect.height()*3/4));
         sceneColorImage->addPixmap(pm[0].scaled(w0*zf[0],h0*zf[0]));
    }
    if(i == 1)
    {
        scene1->clear();
        sceneGrayImage->clear();
        scene1->addPixmap(pm[1].scaled(rect.width()*1/4,rect.height()*1/4));
        sceneGrayImage->addPixmap(pm[1].scaled(w0*zf[1],h0*zf[1]));
    }
    if(i == 2)
    {
        scene2->clear();
        sceneProcessedGrayImage->clear();
        scene2->addPixmap(pm[2].scaled(rect.width()*1/4,rect.height()*1/4));
        sceneProcessedGrayImage->addPixmap(pm[2].scaled(w0*zf[2],h0*zf[2]));
    }
    if(i == 3)
    {
        scene3->clear();
        sceneGrayHistogram->clear();
        scene3->addPixmap(pm[3].scaled(rect.width()*1/4,rect.height()*1/4));
        sceneGrayHistogram->addPixmap(pm[3].scaled(w0*zf[3],h0*zf[3]));
    }
    if(i == 5)
    {
        scene5->clear();
        sceneProcessedColorImage->clear();
        scene5->addPixmap(pm[5].scaled(rect.width()*1/4,rect.height()*1/4));
        sceneProcessedColorImage->addPixmap(pm[5].scaled(w0*zf[5],h0*zf[5]));
    }
    if(i == 6)
    {
        scene6->clear();
        sceneColorHistogram->clear();
        scene6->addPixmap(pm[6].scaled(rect.width()*1/4,rect.height()*1/4));
        sceneColorHistogram->addPixmap(pm[6].scaled(w0*zf[6],h0*zf[6]));
    }
    if(i == ROIIMG)
    {
        sceneROI->clear();
        sceneROI->addPixmap(pmROI[0]);
    }
    if(i == ROIHIST)
    {
        rect = ui->gVROI->geometry();
        sceneROIHist->clear();
        sceneROIHist->addPixmap(pmROI[1].scaled(rect.width()/2,rect.height()/2));
    }

}

void EAMViewer::resizeEvent(QResizeEvent *)
{
    loadPixmaps();
}

void EAMViewer::showTMData(Mat &result, int k)
{
    if(ui->cBxMode->currentIndex() == 0)
        newLineInText(tr("matchTemplate(sqdiff);"));
    if(ui->cBxMode->currentIndex() == 1)
        newLineInText(tr("matchTemplate(sqdiff_normed);"));
    if(ui->cBxMode->currentIndex() == 2)
        newLineInText(tr("matchTemplate(ccorr);"));
    if(ui->cBxMode->currentIndex() == 3)
        newLineInText(tr("matchTemplate(ccorr_normed);"));
    if(ui->cBxMode->currentIndex() == 4)
        newLineInText(tr("matchTemplate(ccoeff);"));
    if(ui->cBxMode->currentIndex() == 5)
        newLineInText(tr("matchTemplate(ccoeff_normed);"));

    EventsQGraphicsView *GV = new EventsQGraphicsView(this);
    QGraphicsScene *GS = new QGraphicsScene(this);
    GV->setScene(GS);
    QPixmap pmGV =QPixmap::fromImage(matToQImage(result));
    GS->addPixmap(pmGV);
    pmTM.push_back(pmGV);
    QRect geo = ui->scrollArea2->geometry();
    GV->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
    GV->setMinimumHeight(geo.height());
    GV->setMaximumHeight(geo.height());
    connect(GV,SIGNAL(keyPressed()),QSMTMKeyPressEvent,SLOT(map()));
    QSMTMKeyPressEvent->setMapping(GV,k);
    ui->scrollArea2->widget()->layout()->addWidget(GV);
    TMViews.push_back(GV);
    ui->tabWidget->addTab(ui->tbTemplate,tr("template matching"));
    ui->tabWidget->setCurrentWidget(ui->tbTemplate);
}

void EAMViewer::sortEvalMSERDataByHulls()
{
    vector<vector<Point> > firsthulltree, points, hulls;
    vector<RotatedRect> ellipses;
    for( unsigned int h = 0; h < MSEREvalHulls.size(); h++)
    {
        vector<Point> vec1 = MSEREvalHulls[h];
        for( unsigned int i = 0; i < MSEREvalHulls.size(); i++)
        {
            vector<Point> vec2 = MSEREvalHulls[i];
            boost::dynamic_bitset<> bs(int(vec2.size()));
            for(unsigned int h = 0; h < vec2.size(); h++)
                if(pointPolygonTest(vec1,vec2[h], false) != -1)
                    bs.set(h, true);
            float hullmatch = float(bs.count())/float(vec2.size());
            bool b = false;
            if(hullmatch > 0.8)
                b = true;
            else
                b = false;

            if(b && (i != h))
                break;
            if(i == MSEREvalHulls.size() - 1)
            {
                firsthulltree.push_back(vec2);
                points.push_back(MSEREvalPoints[h]);
                hulls.push_back(MSEREvalHulls[h]);
                ellipses.push_back(MSEREvalEllipses[h]);
            }
        }
    }
    MSEREvalPoints.clear();
    MSEREvalHulls.clear();
    MSEREvalEllipses.clear();
    MSEREvalPoints = points;
    MSEREvalHulls = hulls;
    MSEREvalEllipses = ellipses;

}

void EAMViewer::sortEvalMSERDataBySize()
{
    unsigned int vvsize = MSEREvalPoints.size();
    unsigned int sortArray[vvsize], sizes[vvsize];

    for(unsigned int h = 0; h < vvsize; h++)
    {
        vector<Point> vec = MSEREvalPoints[h];
        sortArray[h] = vec.size();
        sizes[h] = h;
    }
    bool b = true; unsigned int helpInt = 0;
    while (b)
    {
        unsigned int i = 0;
        for(unsigned int h = 0; h < vvsize-1; h++)
        {
            if(sortArray[h] > sortArray[h+1])
            {
                helpInt = sortArray[h];
                sortArray[h] = sortArray[h+1];
                sortArray[h+1] = helpInt;
                helpInt = sizes[h];
                sizes[h] = sizes[h+1];
                sizes[h+1] = helpInt;
            }
            else
                i++;
            if(i == vvsize - 1)
                b = false;
        }
    }
    vector<vector<Point>> help1(MSEREvalPoints), help2(MSEREvalHulls);
    vector<RotatedRect> help3(MSEREvalEllipses);

    MSEREvalPoints.clear();
    MSEREvalHulls.clear();
    MSEREvalEllipses.clear();

    for(unsigned int h = 0; h < vvsize; h++)
    {
        vector<Point> r = help1[sizes[h]];
        vector<Point> s = help2[sizes[h]];
        RotatedRect rec = help3[sizes[h]];
        MSEREvalPoints.push_back(r);
        MSEREvalHulls.push_back(s);
        MSEREvalEllipses.push_back(rec);
    }
}

/// *** methods for imageprocessing *** ///
void EAMViewer::adaptivethreshold(Mat &img,int maxVal, int method,int threshType,int blockSize,double offset)
{
    adaptiveThreshold(img,img,maxVal,method,threshType,blockSize,offset);
}

void EAMViewer::canny(Mat &img, int threshold1, int threshold2,int sobelSize, bool L2)
{
    Canny(img,img,threshold1,threshold2,sobelSize,L2);
}

void EAMViewer::calcHoughCircles(Mat &img, vector<Vec3f> &cHough, int method, double invRatio, double minDist, double cannyThreshold, double threshold, int minRadius, int maxRadius)
{
    Mat procImg = img.clone();
    if(procImg.channels() > 1)
        cvtColor(procImg, procImg, CV_BGR2GRAY);
    HoughCircles(procImg,cHough,method,invRatio,minDist,cannyThreshold,threshold,minRadius,maxRadius);
}

void EAMViewer::calcHoughLines(Mat &img, vector<Vec2f> &lHough ,double rho, double rhoDiv, int threshold, double theta, double thetaDiv )
{
    Mat procImg = img.clone();
    if(procImg.channels() > 1)
        cvtColor(procImg, procImg, CV_BGR2GRAY);
    HoughLines(procImg,lHough,rho,theta,threshold,rhoDiv,thetaDiv);
}

void EAMViewer::calcHoughLinesP(Mat &img,vector<Vec4i> &lHoughP, double rho, double theta, int threshold, double minLength, double maxGap)
{
    Mat procImg = img.clone();
    if(procImg.channels() > 1)
        cvtColor(procImg, procImg, CV_BGR2GRAY);
    HoughLinesP(procImg,lHoughP,rho,theta,threshold,minLength,maxGap);
}

void EAMViewer::cornerdetect(Mat &img, vector<Vec2i> &corn, int blockSize, int sobelSize, int cornerFlag, int border, int quality, InputArray mask)
{
    Mat procImg = img.clone();
    if(procImg.channels() > 1)
        cvtColor(procImg, procImg, CV_BGR2GRAY);
    Mat imgcorner = Mat::zeros( img.size(), CV_32FC1 );
    if(cornerFlag == true)
    {
        Mat harris = Mat ( img.size(), CV_32FC(6) );
        cornerEigenValsAndVecs( procImg, harris, blockSize, sobelSize, border );
        for( int j = 0; j < img.rows; j++ )
            for( int i = 0; i < img.cols; i++ )
            {
              float lambda_1 = harris.at<Vec6f>( j, i)[0];
              float lambda_2 = harris.at<Vec6f>( j, i)[1];
              imgcorner.at<float>(j,i) = lambda_1*lambda_2 - 0.04*pow( ( lambda_1 + lambda_2 ), 2 );
            }
    }
    if(cornerFlag == false)
        cornerMinEigenVal( procImg,imgcorner,blockSize,sobelSize,border);

    corn.clear();
    double minVal, maxVal;
    minMaxLoc( imgcorner, &minVal, &maxVal, 0, 0, mask );
    float Val = minVal + (maxVal - minVal )*quality/100;
    for( int j = 0; j < imgcorner.rows; j++ )
        for( int i = 0; i < imgcorner.cols; i++ )
            if( imgcorner.at<float>(j,i) > float(Val) )
            {
                Vec2i vec(i,j);
                corn.push_back(vec);
            }

}

void EAMViewer::dilate(Mat &img,int shape, int sizeX, int sizeY,int anchorX, int anchorY, int iterations,int border)
{
    cv::Size size;
    size.width = sizeX;
    size.height = sizeY;

    Point point;
    point.x = anchorX;
    point.y = anchorY;

    Mat element = getStructuringElement(shape,size,point);
    cv::dilate(img,img,element,cv::Point(-1,-1),iterations,border);
}

void EAMViewer::erode(Mat &img,int shape, int sizeX, int sizeY,int anchorX, int anchorY, int iterations,int border)
{
    cv::Size size;
    size.width = sizeX;
    size.height = sizeY;

    Point point;
    point.x = anchorX;
    point.y = anchorY;

    Mat element = getStructuringElement(shape,size,point);
    cv::erode(img,img,element,cv::Point(-1,-1),iterations,border);
}

void EAMViewer::gammatransformation(Mat &img, int i)
{
    int LUT[256];
    if(i != 0)
    {
        float val = static_cast<float>(i)/500.0;
        for(int h = 0; h < 256; h++)
        {
            LUT[h] = static_cast<int>(static_cast<float>(h)*exp(val));
            if(LUT[h] > 255)
                LUT[h] = 255;
            if(LUT[h] < 0)
                LUT[h] = 0;
        }
        uchar* data = img.data;
        for(int h = 0; h < img.rows*img.cols*img.channels(); h++)
            data[h] = LUT[data[h]];
    }
}

void EAMViewer::gaussianblur( Mat &img, int sizeX, int sizeY, float sigmaX, float sigmaY, int border)
{
    cv::Size size;
    size.width = sizeX;
    size.height = sizeY;
    GaussianBlur(img,img,size,sigmaX,sigmaY,border);
}

void EAMViewer::histogramequalization( Mat &img)
{
    equalizeHist(img,img);
}

void EAMViewer::inversion( Mat &img)
{
    int LUT[256];
    for(int h = 0; h < 256; h++)
        LUT[h] = 255 - h;
    uchar* data = img.data;
    for(int h = 0; h < img.rows*img.cols*img.channels(); h++)
        data[h] = LUT[data[h]];
}

void EAMViewer::laplacian(Mat &img,int size, double scale, double delta, int border)
{
    Laplacian(img,img,img.depth(),size,scale,delta,border);
}

void EAMViewer::lineartransformation(Mat &img, int i)
{
    int LUT[256];
    for(int h = 0; h < 256; h++)
    {
        LUT[h] = h + i;
        if(LUT[h]< 0)
            LUT[h] = 0;
        if(LUT[h]> 255)
            LUT[h] = 255;
    }
    uchar* data = img.data;
    for(int h = 0; h < img.rows*img.cols*img.channels(); h++)
        data[h] = LUT[data[h]];
}

Mat  EAMViewer::templatematching(Mat &img, Mat &roi, int mode)
{
    int result_cols =  img.cols - roi.cols + 1;
    int result_rows = img.rows - roi.rows + 1;

    Mat result;
    result.create( result_cols, result_rows, CV_32FC1 );
    matchTemplate(img,roi,result,mode);

    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat());
    result.convertTo(result,CV_8UC1,255,0);
    return result;
}

void EAMViewer::meanblur(Mat &img,int sizeX, int sizeY, int anchorX, int anchorY, int border)
{
    cv::Size size;
    size.width = sizeX;
    size.height = sizeY;
    Point point;
    point.x = anchorX;
    point.y = anchorY;

    blur(img,img,size,point,border);
}

void EAMViewer::medianblur(Mat &img, int size)
{
    medianBlur(img,img,size);
}

void EAMViewer::morphologyfilter(Mat &img, int opMethod, int shape, int sizeX, int sizeY,int anchorX, int anchorY, int iterations,int border)
{
    cv::Size size;
    size.width = sizeX;
    size.height = sizeY;

    Point point;
    point.x = anchorX;
    point.y = anchorY;

    Mat element = getStructuringElement(shape,size,point);
    morphologyEx(img,img,opMethod,element,point,iterations,border);
}

void EAMViewer::scharr(Mat &img, int dx, int dy, double scale, double delta, int border)
{
    Scharr(img,img,img.depth(),dx,dy,scale,delta,border);
}

void EAMViewer::simpleFilter(Mat &img,int X, int Y, int anchorX, int anchorY, double delta, double* data, int border)
{
    Mat filter = Mat( Y,X,CV_64F,data);
    Point point;
    point.x = anchorX;
    point.y = anchorY;
    filter2D(img,img,img.depth(),filter,point,delta,border);
}

void EAMViewer::sobel(Mat &img,int dx, int dy, int size, double scale, double delta, int border)
{
    Sobel(img,img,img.depth(),dx,dy,size,scale,delta,border);
}

void EAMViewer::threshold(Mat &img, double thres, double maxVal, int mode)
{
    cv::threshold(img,img,thres,maxVal,mode);
}

void EAMViewer::simpleBackgroundSubstraction(Mat &img, Mat &imgBG)
{
    Mat diffImg = img - imgBG;
    img.copyTo(img, diffImg);
}
//-------------------------------------------------------------//

/// *** methods of videoprocessing *** ///
//-------------------------------------------------------------//

bool EAMViewer::checkIfCurrentFcnIsAlreadyInToolchain(int i)
{
    if(processingToolchainIndex.size() < 2)
        return false;
    for(unsigned int u = 0; u < processingToolchainIndex.size() - 2; u++)
    {
        if(processingToolchainIndex.at(u) == i)
            return true;
    }
    return false;
}

bool EAMViewer::checkIfCurrentFcnIsAlreadyInVideoToolchain(int i)
{
    if(processingVideoToolchainIndex.size() < 2)
        return false;
    for(unsigned int u = 0; u < processingVideoToolchainIndex.size() - 2; u++)
    {
        if(processingVideoToolchainIndex.at(u) == i)
            return true;
    }
    return false;
}

void EAMViewer::chooseFcnForVidProcessing(int i)
{
    if(index == 12)
    {
        if(i == 1)
            inversion(camImg);
        if(camImg.channels() == 1)
            if(i == 2)
                histogramequalization(camImg);
        if(i == 3)
            lineartransformation(camImg,linearTransformationValue);
        if(i == 4)
            gammatransformation(camImg,gammaTransformationValue);
        if(i == 5)
            threshold(camImg,threshValue,threshMaxValValue,threshModeValue);
        if(i == 6)
        {
            if(camImg.channels() > 1)
                cvtColor(camImg, camImg,CV_BGR2GRAY);
            adaptivethreshold(camImg,adaptThreshMaxValValue,adaptThreshMethodValue,adaptThreshTypeValue,adaptThreshBlockSizeValue,adaptThreshOffsetValue);
        }
        if(i == 7)
            meanBlurFE->apply(camImg,camImg);
        if(i == 8)
            medianblur(camImg,medianBlurSizeValue);
        if(i == 9)
        {
            gaussianFE->apply(camImg,camImg);
        }
        if(i == 10)
        {
            sobelFE->apply(camImg,camImg);
            camImg = camImg*sobelScaleValue + sobelDeltaValue;
        }
        if(i == 11)
        {
            laplaceFE->apply(camImg,camImg);
            camImg = camImg*laplaceScaleValue + laplaceDeltaValue;
        }
        if(i == 12)
        {
            scharrFE->apply(camImg,camImg);
            camImg = camImg*scharrScaleValue + scharrDeltaValue;
        }
        if(i == 13)
            canny(camImg,cannyThreshold1Values,cannyThreshold2Values,cannySobelSize,cannyL2Value);
        if(i == 14)
            simpleFilter(camImg,simpleFilterXValue,simpleFilterYValue,simpleFilterAnchorXValue,simpleFilterAnchorYValue,simpleFilterDeltaValue,simpleFilterDataValues,simpleFilterBorderValue);
        if(i == 15)
            for(h = 0; h < dilateIterationsValue;h++)
                DilateFE->apply(camImg,camImg);
        if(i == 16)
            for(h = 0; h < erodeIterationsValue;h++)
                ErodeFE->apply(camImg,camImg);
        if(i == 17)
            morphologyfilter(camImg, morphologyFilterOpMethodValue,morphologyFilterShapeValue,morphologyFilterSizeXValue,morphologyFilterSizeYValue,morphologyFilterAnchorXValue,morphologyFilterAnchorYValue,morphologyFilterIterationsValue,morphologyFilterBorderValue);
        if(i == 18)
        {
            if(camImg.channels() > 1)
                cvtColor(camImg, camImg,CV_BGR2GRAY);
            else if(camImg.channels() == 1)
                camImg = camImg.clone();
            if(calcHoughLinesPropValue == false)
            {
                calcLinesHoughCam.clear();
                calcHoughLines(camImg,calcLinesHoughCam,calcHoughLinesRhoValue,calcHoughLinesRhoDivValue,calcHoughLinesThresholdValue,calcHoughLinesThetaValue,calcHoughLinesThetaDivValue);
            }
            if(calcHoughLinesPropValue == true)
            {
                calcLinesHoughPCam.clear();
                calcHoughLinesP(camImg,calcLinesHoughPCam,calcHoughLinesPRhoValue,calcHoughLinesPThetaValue,calcHoughLinesPThresholdValue,calcHoughLinesPMinLengthValue,calcHoughLinesPMaxGapValue);
            }
            drawHoughLines();
        }
        if(i == 19)
        {
            if(camImg.channels() > 1)
                cvtColor(camImg, camImg,CV_BGR2GRAY);
            else if(camImg.channels() == 1)
                camImg = camImg.clone();
            calcHoughCircles(camImg, calcCirclesHoughCam,calcHoughCirclesMethodValue,calcHoughCirclesInvRatioValue,calcHoughCirclesMinDistValue,calcHoughCirclesCannyThresholdValue,calcHoughCirclesThresholdValue,calcHoughCirclesMinRadiusValue,calcHoughCirclesMaxRadiusValue);
            if(dialhoughcircles->drawFlag == true)
                drawHoughCircles();
        }
        if(i == 20)
        {
            if(camImg.channels() > 1)
                cvtColor(camImg, camImg,CV_BGR2GRAY);
            else if(camImg.channels() == 1)
                camImg = camImg.clone();
            cornerdetect(camImg,cornersCam,cornerDetectBlockSizeValue,cornerDetectSobelSizeValue,cornerDetectCornerFlagValue,cornerDetectBorderValue,cornerDetectQualityValue,Mat());
            if(dialcornerdetect->drawFlag)
                drawCornerCircles();
        }
        if(i == 21)
        {
            Mat RoiImg = ROIDBItems.at(chosenRoi).RoiImg;
            if(camImg.channels() == 1 && RoiImg.channels() == 3)
                cvtColor(RoiImg,RoiImg,CV_BGR2GRAY);
            if(camImg.channels() == 3 && RoiImg.channels() == 1)
                cvtColor(camImg,camImg,CV_BGR2GRAY);

            camImg = templatematching(camImg,RoiImg,currentTMMode);
        }
        if(i == 23)
        {
            FASTKeyPointsCam.clear();
            if(camImg.channels() > 1)
                cvtColor(camImg, camImgProc,CV_BGR2GRAY);
            FASTX(camImgProc, FASTKeyPointsCam, FASTThreshold, FASTNMS, FASTType);
            drawFASTFeatures();
        }
        if(i == 24)
        {
            ORBDescriptorsCam.release();
            ORBKeyPointsCam.clear();

            if(dialorb->FASTKeyPoints == true)
            {
                ORBKPFlagCam = true;
                ORBKeyPointsCam = FASTKeyPointsCam;
            }
            else if(dialorb->BRISKKeyPoints == true)
            {
                ORBKPFlagCam = true;
                ORBKeyPointsCam = BRISKKeyPointsCam;
            }
            else
                ORBKPFlagCam = false;
            if(camImg.channels() > 1)
                cvtColor(camImg, camImgProc, CV_BGR2GRAY);
            FtORBCam(camImgProc, Mat(),ORBKeyPointsCam, ORBDescriptorsCam, ORBKPFlagCam);
            drawORBFeatures();
        }
        if(i == 25)
        {
            BRISKDescriptorsCam.release();
            BRISKKeyPointsCam.clear();

            if(dialbrisk->FASTKeyPoints == true)
            {
                BRISKKPFlagCam = true;
                BRISKKeyPointsCam = FASTKeyPointsCam;
            }
            if(dialbrisk->ORBKeyPoints == true)
            {
                BRISKKPFlagCam = true;
                BRISKKeyPointsCam = ORBKeyPointsCam;
            }
            else
                BRISKKPFlagCam = false;

            if(camImg.channels() > 1)
                cvtColor(camImg, camImgProc, CV_BGR2GRAY);
            FtBRISKCam(camImgProc, Mat(),BRISKKeyPointsCam, BRISKDescriptorsCam, BRISKKPFlagCam);
            drawBRISKFeatures();
        }
        if(i == 26)
        {
            FREAKDescriptorsCam.release();
            FREAKKeyPointsCam.clear();
            if(dialfreak->FASTKeyPoints == true)
                FREAKKeyPointsCam = FASTKeyPointsCam;
            if(dialfreak->ORBKeyPoints == true)
                FREAKKeyPointsCam = ORBKeyPointsCam;
            if(dialfreak->BRISKKeyPoints == true)
                FREAKKeyPointsCam = BRISKKeyPointsCam;
            if(camImg.channels() > 1)
                cvtColor(camImg, camImgProc, CV_BGR2GRAY);
            FtFREAKCam.compute(camImgProc, FREAKKeyPointsCam, FREAKDescriptorsCam);
            drawFREAKFeatures();
        }
        if(i == 29)
        {
            MSERPointsCam.clear();
            if(camImg.channels() > 1)
                cvtColor(camImg, camImgProc,CV_BGR2GRAY);
            FtMSERCam(camImgProc, MSERPointsCam);
            calculateHulls(MSERPointsCam, MSERHullsCam);
            drawMSERFeatures();
        }
        if(i == 30)
        {


            evaluateMSERData();
        }
    }
    if(index == 13)
    {
        if(i == 1)
            inversion(vidImg);
        if(vidImg.channels() == 1)
            if(i == 2)
                histogramequalization(vidImg);
        if(i == 3)
            lineartransformation(vidImg,linearTransformationValue);
        if(i == 4)
            gammatransformation(vidImg,gammaTransformationValue);
        if(i == 5)
            threshold(vidImg,threshValue,threshMaxValValue,threshModeValue);
        if(i == 6)
        {
            if(vidImg.channels() > 1)
                cvtColor(vidImg, vidImg,CV_BGR2GRAY);
            adaptivethreshold(vidImg,adaptThreshMaxValValue,adaptThreshMethodValue,adaptThreshTypeValue,adaptThreshBlockSizeValue,adaptThreshOffsetValue);
        }
        if(i == 7)
            meanBlurFE->apply(vidImg,vidImg);
        if(i == 8)
            medianblur(vidImg,medianBlurSizeValue);
        if(i == 9)
            gaussianFE->apply(vidImg,vidImg);
        if(i == 10)
        {
            sobelFE->apply(vidImg,vidImg);
            vidImg = vidImg*sobelScaleValue + sobelDeltaValue;
        }
        if(i == 11)
        {
            laplaceFE->apply(vidImg,vidImg);
            vidImg = vidImg*laplaceScaleValue + laplaceDeltaValue;
        }
        if(i == 12)
        {
            scharrFE->apply(vidImg,vidImg);
            vidImg = vidImg*scharrScaleValue + scharrDeltaValue;
        }
        if(i == 13)
            canny(vidImg,cannyThreshold1Values,cannyThreshold2Values,cannySobelSize,cannyL2Value);
        if(i == 14)
            simpleFilter(vidImg,simpleFilterXValue,simpleFilterYValue,simpleFilterAnchorXValue,simpleFilterAnchorYValue,simpleFilterDeltaValue,simpleFilterDataValues,simpleFilterBorderValue);
        if(i == 15)
            for(h = 0; h < dilateIterationsValue;h++)
                DilateFE->apply(vidImg,vidImg);
        if(i == 16)
            for(h = 0; h < erodeIterationsValue;h++)
                ErodeFE->apply(vidImg,vidImg);
        if(i == 17)
            morphologyfilter(vidImg, morphologyFilterOpMethodValue,morphologyFilterShapeValue,morphologyFilterSizeXValue,morphologyFilterSizeYValue,morphologyFilterAnchorXValue,morphologyFilterAnchorYValue,morphologyFilterIterationsValue,morphologyFilterBorderValue);
        if(i == 18)
        {
            if(vidImg.channels() > 1)
                cvtColor(vidImg, vidImg,CV_BGR2GRAY);
            else if(vidImg.channels() == 1)
                vidImg = vidImg.clone();
            if(calcHoughLinesPropValue == false)
            {
                calcLinesHoughVideo.clear();
                calcHoughLines(vidImg,calcLinesHoughVideo,calcHoughLinesRhoValue,calcHoughLinesRhoDivValue,calcHoughLinesThresholdValue,calcHoughLinesThetaValue,calcHoughLinesThetaDivValue);
            }
            if(calcHoughLinesPropValue == true)
            {
                calcLinesHoughPVideo.clear();
                calcHoughLinesP(vidImg,calcLinesHoughPVideo,calcHoughLinesPRhoValue,calcHoughLinesPThetaValue,calcHoughLinesPThresholdValue,calcHoughLinesPMinLengthValue,calcHoughLinesPMaxGapValue);
            }
            if(dialhoughlines->drawFlag == true)
                drawHoughLines();
        }
        if(i == 19)
        {
            if(vidImg.channels() > 1)
                cvtColor(vidImg, vidImg,CV_BGR2GRAY);
            else if(vidImg.channels() == 1)
                vidImg = vidImg.clone();
            calcHoughCircles(vidImg, calcCirclesHoughVideo,calcHoughCirclesMethodValue,calcHoughCirclesInvRatioValue,calcHoughCirclesMinDistValue,calcHoughCirclesCannyThresholdValue,calcHoughCirclesThresholdValue,calcHoughCirclesMinRadiusValue,calcHoughCirclesMaxRadiusValue);
            if(dialhoughcircles->drawFlag == true)
                drawHoughCircles();
        }
        if(i == 20)
        {
            if(vidImg.channels() > 1)
                cvtColor(vidImg, vidImg,CV_BGR2GRAY);
            else if(vidImg.channels() == 1)
                vidImg = vidImg.clone();
            cornerdetect(vidImg,cornersVideo,cornerDetectBlockSizeValue,cornerDetectSobelSizeValue,cornerDetectCornerFlagValue,cornerDetectBorderValue,cornerDetectQualityValue,Mat());
            if(dialcornerdetect->drawFlag)
                drawCornerCircles();
        }
        if(i == 21)
        {
            Mat RoiImg = ROIDBItems.at(chosenRoi).RoiImg;
            if(vidImg.channels() == 1 && RoiImg.channels() == 3)
                cvtColor(RoiImg,RoiImg,CV_BGR2GRAY);
            if(vidImg.channels() == 3 && RoiImg.channels() == 1)
                cvtColor(vidImg,vidImg,CV_BGR2GRAY);

            vidImg = templatematching(vidImg,RoiImg,currentTMMode);
        }
        if(i == 23)
        {
            FASTKeyPointsVid.clear();
            if(vidImg.channels() > 1)
                cvtColor(vidImg, vidImgProc,CV_BGR2GRAY);
            FASTX(vidImgProc, FASTKeyPointsVid, FASTThreshold, FASTNMS, FASTType);
            drawFASTFeatures();
        }        
        if(i == 24)
        {
            ORBKeyPointsVid.clear();
            ORBDescriptorsVid.release();

            if(dialorb->FASTKeyPoints == true)
            {
                ORBKPFlagVid = true;
                ORBKeyPointsVid = FASTKeyPointsVid;
            }
            else if(dialorb->BRISKKeyPoints == true)
            {
                ORBKPFlagVid = true;
                ORBKeyPointsVid = BRISKKeyPointsVid;
            }
            else
                ORBKPFlagVid = false;


            if(vidImg.channels() > 1)
                cvtColor(vidImg, vidImgProc, CV_BGR2GRAY);
            FtORBCam(vidImgProc, Mat(),ORBKeyPointsVid, ORBDescriptorsVid, ORBKPFlagVid);
            drawORBFeatures();
        }
        if(i == 25)
        {
            BRISKKeyPointsVid.clear();
            BRISKDescriptorsVid.release();

            if(dialbrisk->FASTKeyPoints == true)
            {
                BRISKKPFlagVid = true;
                BRISKKeyPointsVid = FASTKeyPointsVid;
            }
            if(dialbrisk->ORBKeyPoints == true)
            {
                BRISKKPFlagVid = true;
                BRISKKeyPointsVid = ORBKeyPointsVid;
            }
            else
                BRISKKPFlagVid = false;
            if(vidImg.channels() > 1)
                cvtColor(vidImg, vidImgProc, CV_BGR2GRAY);
            FtBRISKCam(vidImgProc, Mat(),BRISKKeyPointsVid, BRISKDescriptorsVid, BRISKKPFlag);
            drawBRISKFeatures();
        }
        if(i == 26)
        {
            FREAKDescriptorsVid.release();
            FREAKKeyPointsVid.clear();
            if(dialfreak->FASTKeyPoints == true)
                FREAKKeyPointsVid = FASTKeyPointsVid;
            if(dialfreak->ORBKeyPoints == true)
                FREAKKeyPointsVid = ORBKeyPointsVid;
            if(dialfreak->BRISKKeyPoints == true)
                FREAKKeyPointsVid = BRISKKeyPointsVid;
            if(vidImg.channels() > 1)
                cvtColor(vidImg, vidImgProc, CV_BGR2GRAY);
            FtFREAKVid.compute(vidImgProc, FREAKKeyPointsVid, FREAKDescriptorsVid);
            drawFREAKFeatures();
        }
        if(i == 29)
        {
            MSERPointsVid.clear();
            if(vidImg.channels() > 1)
                cvtColor(vidImg, vidImgProc,CV_BGR2GRAY);
            FtMSERVid(vidImgProc, MSERPointsVid);
            calculateHulls(MSERPointsVid, MSERHullsVid);
            drawMSERFeatures();
        }
        if(i == 30)
        {



            evaluateMSERData();
        }
    }
}

void EAMViewer::initDilate(Mat &img, int shape, int sizeX, int sizeY,int anchorX, int anchorY, int border)
{

   cv::Size size;
   size.width = sizeX;
   size.height = sizeY;

   Point point;
   point.x = anchorX;
   point.y = anchorY;
   Mat element = getStructuringElement(shape,size,point);
   DilateFE = createMorphologyFilter(MORPH_DILATE,img.type(),element,point,border);
}

void EAMViewer::initErode(Mat &img, int shape, int sizeX, int sizeY, int anchorX, int anchorY, int border)
{
    cv::Size size;
    size.width = sizeX;
    size.height = sizeY;

    Point point;
    point.x = anchorX;
    point.y = anchorY;
    Mat element = getStructuringElement(shape,size,point);
    ErodeFE = createMorphologyFilter(MORPH_ERODE,img.type(),element,point,border);
}

void EAMViewer::initGaussian(Mat &img,int sizeX, int sizeY, int sigmaX, int sigmaY, int border)
{
    cv::Size size;
    size.width = sizeX;
    size.height = sizeY;
    gaussianFE = createGaussianFilter(img.type(),size,sigmaX,sigmaY,border);
}

void EAMViewer::initLaplacian(Mat &img,int size,int border)
{
    Mat kx, ky;
    getDerivKernels(kx,ky,2,2,size);
    laplaceFE = createSeparableLinearFilter(img.type(),img.type(),kx,ky,Point(-1,1),0,border,border);
}

void EAMViewer::initMeanBlur(Mat &img,int sizeX, int sizeY, int anchorX, int anchorY, int border)
{
    cv::Size size;
    size.width = sizeX;
    size.height = sizeY;
    Point point;
    point.x = anchorX;
    point.y = anchorY;
    meanBlurFE = createBoxFilter(img.type(),img.type(),size,point,true,border);
}

void EAMViewer::initScharr(Mat &img,int dx, int dy, int border)
{
   Mat kx, ky;
   getDerivKernels(kx,ky,dx,dy,CV_SCHARR);
   scharrFE = createSeparableLinearFilter(img.type(),img.type(),kx,ky,Point(-1,1),0,border);
}

void EAMViewer::initSobel(Mat &img,int dx, int dy, int size, int border)
{
    sobelFE = createDerivFilter(img.type(),img.type(),dx,dy,size,border);
}

void EAMViewer::changeLineOfVideoTextEdit(QString qstr)
{
    removeLastLineFromVideoTextEdit();
    addLineToVideoTextEdit(qstr);
}

void EAMViewer::addLineToVideoTextEdit(QString qstr)
{
    if(index == 12)
        ui->textEditVideo->append(qstr);
    if(index == 13)
        ui->textEditVideoVid->append(qstr);
}

void EAMViewer::removeLastLineFromVideoTextEdit()
{
    if(index == 12)
    {
        ui->textEditVideo->setFocus();
        QTextCursor storeCursorPos = ui->textEditVideo->textCursor();
        ui->textEditVideo->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->textEditVideo->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
        ui->textEditVideo->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
        ui->textEditVideo->textCursor().removeSelectedText();
        ui->textEditVideo->textCursor().deletePreviousChar();
        ui->textEditVideo->setTextCursor(storeCursorPos);  
    }
    if(index == 13)
    {  
        ui->textEditVideoVid->setFocus();
        QTextCursor storeCursorPos = ui->textEditVideoVid->textCursor();
        ui->textEditVideoVid->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->textEditVideoVid->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
        ui->textEditVideoVid->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
        ui->textEditVideoVid->textCursor().removeSelectedText();
        ui->textEditVideoVid->textCursor().deletePreviousChar();
        ui->textEditVideoVid->setTextCursor(storeCursorPos);
    }
}

void EAMViewer::validateCurrentFcn( int i, QString hstr)
{
    if(index == 12)
    {
        if(i == 7)
            initMeanBlur(camImg,meanBlurSizeX,meanBlurSizeY,meanBlurAnchorX,meanBlurAnchorY,meanBlurBorder);
        if(i == 9)
            initGaussian(camImg,gaussianSizeX,gaussianSizeY,gaussianSigmaX,gaussianSigmaY,gaussianBorder);
        if(i == 10)
            initSobel(camImg,sobelDx,sobelDy,sobelSize,sobelBorder);
        if(i == 11)
            initLaplacian(camImg,laplaceSize,laplaceBorderValue);
        if(i == 12)
            initScharr(camImg,scharrDx,scharrDy,scharrBorderValue);
        if(i == 15)
            initDilate(camImg,dilateShape,dilateSizeX,dilateSizeY,dilateAnchorX,dilateAnchorY,dilateBorder);
        if(i == 16)
            initErode(camImg,erodeShape,erodeSizeX,erodeSizeY,erodeAnchorX,erodeAnchorY,erodeBorder);
        if(i == 24)
        {
            timer->stop();
            FtORBCam = ORB(ORBNFeatures,ORBScaleFactor, ORBNLevels,ORBEdgethreshold,ORBFirstLevel, 2, ORB::HARRIS_SCORE, ORBPatchSize);
            timer->start(40);
        }
        if(i == 25)
        {
            timer->stop();
            FtBRISKCam = BRISK(BRISKThresh, BRISKOctaves, BRISKPatternScale);
            timer->start(40);
        }
        if(i == 26)
        {
            timer->stop();
            FREAK FtFREAKCam(FREAKOrientationNormalization, FREAKScaleNormalized, FREAKPatternScale, FREAKNOctaves);
            timer->start(40);
        }
        if(i == 29)
        {
            timer->stop();
            FtMSERCam = MSER( MSERDelta, MSERMinArea, MSERMaxArea,MSERMaxVariation ,MSERMinDiversity);
            timer->start(40);
        }
        if(checkIfCurrentFcnIsAlreadyInToolchain(i) == false)
        {
            int fcnFlag = 0;
            if(processingToolchainIndex.size() > 0)
                fcnFlag = processingToolchainIndex.at(processingToolchainIndex.size()-1);
            if(fcnFlag != i)
            {
                processingToolchainIndex.push_back(i);
                addLineToVideoTextEdit(hstr);
            }
            else if(fcnFlag == i)
                changeLineOfVideoTextEdit(hstr);
        }
        else if(checkIfCurrentFcnIsAlreadyInToolchain(i) == true)
        {
            newLineInText(tr("This function is already in the toolchain."));
            return;
        }
    }
    if(index == 13)
    {
        if(i == 7)
            initMeanBlur(vidImg,meanBlurSizeX,meanBlurSizeY,meanBlurAnchorX,meanBlurAnchorY,meanBlurBorder);
        if(i == 9)
            initGaussian(vidImg,gaussianSizeX,gaussianSizeY,gaussianSigmaX,gaussianSigmaY,gaussianBorder);
        if(i == 10)
            initSobel(vidImg,sobelDx,sobelDy,sobelSize,sobelBorder);
        if(i == 11)
            initLaplacian(vidImg,laplaceSize,laplaceBorderValue);
        if(i == 12)
            initScharr(vidImg,scharrDx,scharrDy,scharrBorderValue);
        if(i == 15)
            initDilate(vidImg,dilateShape,dilateSizeX,dilateSizeY,dilateAnchorX,dilateAnchorY,dilateBorder);
        if(i == 16)
            initErode(vidImg,erodeShape,erodeSizeX,erodeSizeY,erodeAnchorX,erodeAnchorY,erodeBorder);
        if(i == 24)
        {
            timer->stop();
            FtORBVid = ORB(ORBNFeatures,ORBScaleFactor, ORBNLevels,ORBEdgethreshold,ORBFirstLevel, 2, ORB::HARRIS_SCORE, ORBPatchSize);
            timer->start(40);
        }
        if(i == 25)
        {
            timer->stop();
            FtBRISKVid = BRISK(BRISKThresh, BRISKOctaves, BRISKPatternScale);
            timer->start(40);
        }
        if(i == 26)
        {
            timer->stop();
            FREAK FtFREAKVid(FREAKOrientationNormalization, FREAKScaleNormalized, FREAKPatternScale, FREAKNOctaves);
            timer->start(40);
        }
        if(i == 29)
        {
            timer->stop();
            FtMSERVid = MSER( MSERDelta, MSERMinArea, MSERMaxArea,MSERMaxVariation ,MSERMinDiversity);
            timer->start(40);
        }
        if(checkIfCurrentFcnIsAlreadyInVideoToolchain(i) == false)
        {
            int fcnFlag = 0;
            if(processingVideoToolchainIndex.size() > 0)
                fcnFlag = processingVideoToolchainIndex.at(processingVideoToolchainIndex.size()-1);
            if(fcnFlag != i)
            {
                processingVideoToolchainIndex.push_back(i);
                addLineToVideoTextEdit(hstr);
            }
            else if(fcnFlag == i)
                changeLineOfVideoTextEdit(hstr);
        }
        else if(checkIfCurrentFcnIsAlreadyInToolchain(i) == true)
        {
            newLineInText(tr("This function is already in the toolchain."));
            return;
        }
    }

}

//-------------------------------------------------------------//

/// *** EAMViewer slots *** ///
//-------------------------------------------------------------//

void EAMViewer::calcVidProcessingTime()
{
    //int val = int ((endTime - startTime) / CLOCKS_PER_SEC);

}

void EAMViewer::changeTab(int i)
{
    closeAllDialogs();
    QString str = ui->tabWidget->tabText(i);
    if(str.compare("color image",Qt::CaseInsensitive) == 0)
        index = 0;
    if(str.compare("gray image",Qt::CaseInsensitive) == 0)
        index = 1;
    if(str.compare("processed gray",Qt::CaseInsensitive) == 0)
        index = 2;
    if(str.compare("gray histogram",Qt::CaseInsensitive) == 0)
        index = 3;
    if(str.compare("processed color",Qt::CaseInsensitive) == 0)
        index = 5;
    if(str.compare("color histogram",Qt::CaseInsensitive) == 0)
        index = 6;
    if(str.compare("image overview",Qt::CaseInsensitive) == 0)
        index = 8;
    if(str.compare("current roi",Qt::CaseInsensitive) == 0)
        index = 9;
    if(str.compare("roi database",Qt::CaseInsensitive) == 0)
        index = 10;
    if(str.compare("template matching",Qt::CaseInsensitive) == 0)
        index = 11;
    if(str.compare("camera",Qt::CaseInsensitive) == 0)
        index = 12;
    if(str.compare("video",Qt::CaseInsensitive) == 0)
        index = 13;
}

void EAMViewer::confirmProcessedData()
{
    enableTabChanging();
    if(closeflag == true)
        if((index != 9) || (index != 12) || (index != 13))
        {
            img2 = mattempg.clone();
            img5 = mattempc.clone();
        }
}

void EAMViewer::closeTab(int ID)
{
    closeAllDialogs();
    QString str = ui->tabWidget->tabText(ID);
    if(str.compare("image overview",Qt::CaseInsensitive) != 0)
        ui->tabWidget->removeTab(ID);
}

void EAMViewer::closeHoughDialogs()
{
    enableTabChanging();
    if((closeflag == true) || (index >= 12))
    {
        ROI = ROIBuff.clone();
        resetSinglePic(ROI, ROIIMG);
    }
    if((closeflag == true) && (index < 12))
    {
        mattempg = matbuffg.clone();
        resetSinglePic(mattempg,2);
    }
}

void EAMViewer::deleteSingleElementsInDB()
{
    vector<int>chosenDbIndex;
    FormROIDataBase *FRDB;
    for(h = ROIDBItems.size() -1; h >= 0 ; h--)
    {
        FRDB = ROIDBWidgetItems.at(h);
        if(FRDB->checkedChooseBox == true)
            chosenDbIndex.push_back(h);

        disconnect(FRDB,SIGNAL(doubleClicked()),QSMROIDBEvent,SLOT(map()));
        QSMROIDBEvent->removeMappings(FRDB);
        ui->scrollArea->widget()->layout()->removeWidget(FRDB);
        delete FRDB;
        ROIDBWidgetItems.removeAt(h);
    }

    for( unsigned int u = 0; u <= chosenDbIndex.size(); u--)
        ROIDBItems.removeAt(chosenDbIndex.at(u));

    for(h = 0; h <  ROIDBItems.size(); h++)
    {
        FRDB = new FormROIDataBase(this,ROIDBItems.at(h));
        QRect rec = FRDB->geometry();
        FRDB->setMinimumHeight(rec.height()*1.5);
        FRDB->setMaximumHeight(rec.height()*1.5);
        FRDB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
        connect(FRDB,SIGNAL(doubleClicked()),QSMROIDBEvent,SLOT(map()));
        QSMROIDBEvent->setMapping(FRDB,h);
        ROIDBWidgetItems.append(FRDB);
        ui->scrollArea->widget()->layout()->addWidget(FRDB);
    }
}

void EAMViewer::paramsChanged()
{
    if(functionFlag == 3)
    {
        linearTransformationValue  = diallintrans->sliderValueLinTrans;
        QString qstr;
        QString hstr = tr("lineartransformation(") + qstr.setNum(linearTransformationValue) + tr(");");
        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                lineartransformation(mattempg, linearTransformationValue);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                lineartransformation(mattempc, linearTransformationValue);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                lineartransformation(ROI, linearTransformationValue);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        else if(index == 12)
            validateCurrentFcn(functionFlag,hstr);
    }
    if(functionFlag == 4)
    {
        gammaTransformationValue = dialgammatrans->valueGammaTrans;
        QString qstr, hstr = tr("gammatransformation(") + qstr.setNum(gammaTransformationValue) + tr(");");
        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                gammatransformation(mattempg, gammaTransformationValue);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                gammatransformation(mattempc, gammaTransformationValue);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                gammatransformation(ROI, gammaTransformationValue);
                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }           
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(functionFlag,hstr);
    }
    if(functionFlag == 5)
    {        
        threshValue  = double(dialthresh->sliderValueThreshold);
        threshMaxValValue = double(dialthresh->sliderValueMaximum);
        threshModeValue = dialthresh->comboIndex;
        threshOtsuValue = dialthresh->chbxState;
        QString hstr, hstr1, hstr2;
        hstr = tr("threshold(") + hstr1.setNum(threshValue) + tr(",") + hstr2.setNum(threshMaxValValue) + tr(",");

        if(threshModeValue == THRESH_BINARY)
            hstr = hstr + tr("thresh_binary");
        if(threshModeValue == THRESH_BINARY_INV)
            hstr = hstr + tr("thresh_binary_inv");
        if(threshModeValue == THRESH_TRUNC)
            hstr = hstr + tr("thresh_trunc");
        if(threshModeValue == THRESH_TOZERO)
            hstr = hstr + tr("thresh_tozero");
        if(threshModeValue == THRESH_TOZERO_INV)
            hstr = hstr + tr("thresh_tozero_inv");

        if(threshOtsuValue == true)
            hstr = hstr + tr(" || thresh_otsu");

        hstr = hstr + tr(");");
        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                if(threshOtsuValue == true)
                    threshold(mattempg, threshValue, threshMaxValValue, threshModeValue || 8);
                if(threshOtsuValue == false)
                    threshold(mattempg, threshValue, threshMaxValValue, threshModeValue);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                if(threshOtsuValue == true)
                    threshold(mattempc, threshValue, threshMaxValValue, threshModeValue || 8);
                if(threshOtsuValue == false)
                    threshold(mattempc, threshValue, threshMaxValValue, threshModeValue);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                if(threshOtsuValue == true)
                    threshold(ROI, threshValue, threshMaxValValue, threshModeValue || 8);
                if(threshOtsuValue == false)
                    threshold(ROI, threshValue, threshMaxValValue, threshModeValue);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        if(index >= 12)
            validateCurrentFcn(functionFlag,hstr);
    }
    if(functionFlag == 6)
    {
        adaptThreshMaxValValue      = dialadaptthresh->sliderValueMaximum;
        adaptThreshMethodValue      = dialadaptthresh->comboboxIndexMethod;
        adaptThreshOffsetValue      = dialadaptthresh->sliderValueC;
        adaptThreshTypeValue        = dialadaptthresh->comboboxIndexType;
        adaptThreshBlockSizeValue   = dialadaptthresh->sliderValueBlocksize;

        QString hstr, hstr1, hstr2, hstr3;
        hstr = tr("adaptthresh(") + hstr1.setNum(adaptThreshMaxValValue) + tr(",") ;
        if(adaptThreshMethodValue == CV_ADAPTIVE_THRESH_MEAN_C)
            hstr = hstr + tr("adaptthresh_mean_c,");
        if(adaptThreshMethodValue == CV_ADAPTIVE_THRESH_GAUSSIAN_C)
            hstr = hstr + tr("adaptthresh_gaussian_c,");
        if(adaptThreshTypeValue == THRESH_BINARY)
            hstr = hstr + tr("thresh_bin,");
        if(adaptThreshTypeValue == THRESH_BINARY_INV)
            hstr = hstr + tr("thresh_bin_inv,");

        hstr = hstr + hstr2.setNum(adaptThreshBlockSizeValue) + tr(",") + hstr3.setNum(adaptThreshOffsetValue) + tr(");");

        if(index < 12)
        {
            if(index != 9)
            {
                mattempg = matbuffg.clone();
                adaptivethreshold(mattempg, adaptThreshMaxValValue, adaptThreshMethodValue, adaptThreshTypeValue, adaptThreshBlockSizeValue, adaptThreshOffsetValue);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 9))
            {
                ROI = ROIBuff.clone();
                if(ROI.channels() > 1)
                    cvtColor(ROI,ROI,CV_BGR2GRAY);
                adaptivethreshold(ROI,adaptThreshMaxValValue, adaptThreshMethodValue, adaptThreshTypeValue, adaptThreshBlockSizeValue, adaptThreshOffsetValue);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }

            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(functionFlag,hstr);
    }
    if(functionFlag == 7)
    {
        meanBlurSizeX = dialblur->sliderValueSizeX;
        meanBlurSizeY = dialblur->sliderValueSizeY;
        meanBlurAnchorX = dialblur->sliderValueAnchorX;
        meanBlurAnchorY = dialblur->sliderValueAnchorY;
        meanBlurBorder = dialblur->cbxIndex;

        QString hstr, hstr1, hstr2, hstr3, hstr4;
        hstr = tr("meanblur(") + hstr1.setNum(meanBlurSizeX) + tr(",") + hstr2.setNum(meanBlurSizeY) + tr(",")
            + hstr3.setNum(meanBlurAnchorX) + tr(",") + hstr4.setNum(meanBlurAnchorY) + tr(",");

        if(meanBlurBorder == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant);");
        if(meanBlurBorder == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate);");
        if(meanBlurBorder == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect);");
        if(meanBlurBorder == BORDER_REFLECT_101)
            hstr = hstr + tr("border_reflect_101);");
        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                meanblur(mattempg, meanBlurSizeX, meanBlurSizeY, meanBlurAnchorX, meanBlurAnchorY, meanBlurBorder);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                meanblur(mattempc, meanBlurSizeX, meanBlurSizeY, meanBlurAnchorX, meanBlurAnchorY, meanBlurBorder);
                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                meanblur(ROI, meanBlurSizeX, meanBlurSizeY, meanBlurAnchorX, meanBlurAnchorY, meanBlurBorder);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        if(index >= 12)
            validateCurrentFcn(functionFlag,hstr);
    }
    if(functionFlag == 8)
    {
        medianBlurSizeValue = dialmedblur->sliderValueMedianSize;
        QString hstr1, hstr = tr("medianblur(")+  hstr1.setNum(medianBlurSizeValue) +  tr (");");

        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                medianblur(mattempg, medianBlurSizeValue);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                medianblur(mattempc, medianBlurSizeValue);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                medianblur(ROI,medianBlurSizeValue);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(functionFlag, hstr);
    }
    if(functionFlag == 9)
    {
        gaussianSizeX = dialgauss->sliderValueSizeX;
        gaussianSizeY = dialgauss->sliderValueSizeY;
        gaussianSigmaX = dialgauss->sliderValueSigmaX;
        gaussianSigmaY = dialgauss->sliderValueSigmaY;
        gaussianBorder = dialgauss->cbxIndex;
        QString hstr, hstr1, hstr2, hstr3, hstr4;
        hstr = tr("gaussianblur(") + hstr1.setNum(gaussianSizeX) + tr(",") + hstr2.setNum(gaussianSizeY) + tr(",")
           + hstr3.setNum(gaussianSigmaX) + tr(",") + hstr4.setNum(gaussianSigmaY) + tr(",");

        if(gaussianBorder == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant);");
        if(gaussianBorder == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate);");
        if(gaussianBorder == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect);");
        if(gaussianBorder == BORDER_REFLECT_101)
            hstr = hstr + tr("border_reflect_101);");


        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                gaussianblur(mattempg, gaussianSizeX, gaussianSizeY, gaussianSigmaX, gaussianSigmaY, gaussianBorder);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                gaussianblur(mattempc, gaussianSizeX, gaussianSizeY, gaussianSigmaX, gaussianSigmaY, gaussianBorder);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                gaussianblur(mattempc, gaussianSizeX, gaussianSizeY, gaussianSigmaX, gaussianSigmaY, gaussianBorder);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(functionFlag,hstr);
    }
    if(functionFlag == 10)
    {
        sobelDx = dialsobel->spinValueDx;
        sobelDy = dialsobel->spinValueDy;
        sobelSize = dialsobel->spinValueSize;
        sobelDeltaValue = dialsobel->spinValueDelta;
        sobelScaleValue = dialsobel->spinValueScale;
        sobelBorder = dialsobel->cbxIndex;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5;
        hstr = tr("sobel(") + hstr1.setNum(sobelDx) + tr(",") + hstr2.setNum(sobelDy) + tr(",")
           + hstr3.setNum(sobelSize) + tr(",") + hstr4.setNum(sobelScaleValue) + tr(",") + hstr5.setNum(sobelDeltaValue) + tr(",");

        if(sobelBorder == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant);");
        if(sobelBorder == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate);");
        if(sobelBorder == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect);");
        if(sobelBorder == BORDER_REFLECT_101)
            hstr = hstr + tr("border_reflect_101);");
        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                sobel(mattempg, sobelDx, sobelDy, sobelSize, sobelScaleValue, sobelDeltaValue, sobelBorder);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                sobel(mattempc, sobelDx, sobelDy, sobelSize, sobelScaleValue, sobelDeltaValue, sobelBorder);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                sobel(ROI, sobelDx, sobelDy, sobelSize, sobelScaleValue, sobelDeltaValue, sobelBorder);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(functionFlag,hstr);
    }
    if(functionFlag == 11)
    {

        laplaceSize = diallaplace->size;
        laplaceScaleValue = diallaplace->scale;
        laplaceDeltaValue = diallaplace->delta;
        laplaceBorderValue = diallaplace->border;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5;
        hstr = tr("laplacian(") + hstr1.setNum(laplaceSize) + tr(",") + hstr2.setNum(laplaceScaleValue) + tr(",")
           + hstr3.setNum(laplaceDeltaValue) + tr(",");

        if(laplaceBorderValue == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant);");
        if(laplaceBorderValue == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate);");
        if(laplaceBorderValue == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect);");
        if(laplaceBorderValue == BORDER_REFLECT_101)
            hstr = hstr + tr("border_reflect_101);");

        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                laplacian(mattempg, laplaceSize, laplaceScaleValue, laplaceDeltaValue, laplaceBorderValue);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                laplacian(mattempc, laplaceSize, laplaceScaleValue, laplaceDeltaValue, laplaceBorderValue);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                laplacian(ROI, laplaceSize, laplaceScaleValue, laplaceDeltaValue, laplaceBorderValue);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(functionFlag,hstr);
    }
    if(functionFlag == 12)
    {        
        scharrDx = dialscharr->dx;
        scharrDy = dialscharr->dy;
        scharrScaleValue = dialscharr->scale;
        scharrDeltaValue = dialscharr->delta;
        scharrBorderValue = dialscharr->borderType;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5;
        hstr = tr("scharr(") + hstr1.setNum(scharrDx) + tr(",") + hstr2.setNum(scharrDy) + tr(",")
           + hstr3.setNum( scharrScaleValue) + tr(",") + hstr4.setNum(scharrDeltaValue) + tr(",");

        if(scharrBorderValue == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant);");
        if(scharrBorderValue == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate);");
        if(scharrBorderValue == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect);");
        if(scharrBorderValue == BORDER_REFLECT_101)
            hstr = hstr + tr("border_reflect_101);");
        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                scharr(mattempg, scharrDx, scharrDy, scharrScaleValue, scharrDeltaValue, scharrBorderValue);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                scharr(mattempc, scharrDx, scharrDy, scharrScaleValue, scharrDeltaValue, scharrBorderValue);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                scharr(ROI, scharrDx, scharrDy, scharrScaleValue, scharrDeltaValue, scharrBorderValue);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(12,hstr);
    }
    if(functionFlag == 13)
    {

        cannyThreshold1Values = dialcanny->threshold1;
        cannyThreshold2Values = dialcanny->threshold2;
        cannySobelSize = dialcanny->sobelSize;
        cannyL2Value = dialcanny->L2;

        QString hstr, hstr1, hstr2, hstr3;
        hstr = tr("canny(") + hstr1.setNum(cannyThreshold1Values) + tr(",") + hstr2.setNum(cannyThreshold2Values) + tr(",")
           + hstr3.setNum(cannySobelSize) + tr(",");

        if(cannyL2Value == true)
            hstr = hstr + tr("true);");
        if(cannyL2Value == false)
            hstr = hstr + tr("false);");


        if(index < 12)
        {
            if(index != 9)
            {
                mattempg = matbuffg.clone();
                canny(mattempg, cannyThreshold1Values, cannyThreshold2Values, cannySobelSize, cannyL2Value);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                if(ROI.channels() > 1)
                    cvtColor(ROI,ROI,CV_BGR2GRAY);
                canny(ROI, cannyThreshold1Values, cannyThreshold2Values, cannySobelSize, cannyL2Value);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
                ROItoDBFlag[5] = 1;
            }
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(13,hstr);
    }
    if(functionFlag == 14)
    {
        simpleFilterXValue          = dialcustfilt->x;
        simpleFilterYValue          = dialcustfilt->y;
        simpleFilterAnchorXValue    = dialcustfilt->anchorX;
        simpleFilterAnchorYValue    = dialcustfilt->anchorY;
        simpleFilterDeltaValue      = dialcustfilt->delta;
        simpleFilterBorderValue     = dialcustfilt->border;
        simpleFilterDataValues      = dialcustfilt->returnDataPointer();

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5;
        hstr = tr("simplefilter(") + hstr1.setNum(simpleFilterXValue) + tr(",") + hstr2.setNum(simpleFilterYValue) + tr(",")
           + hstr3.setNum(simpleFilterAnchorXValue) + tr(",") + hstr4.setNum(simpleFilterAnchorYValue) + tr(",") + hstr5.setNum(simpleFilterDeltaValue)
           + tr(",") + tr("data[],");

        if(simpleFilterBorderValue == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant);");
        if(simpleFilterBorderValue == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate);");
        if(simpleFilterBorderValue == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect);");
        if(simpleFilterBorderValue == BORDER_REFLECT_101)
            hstr = hstr + tr("border_reflect_101);");

        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                simpleFilter(mattempg, simpleFilterXValue, simpleFilterYValue, simpleFilterAnchorXValue, simpleFilterAnchorYValue, simpleFilterDeltaValue, simpleFilterDataValues, simpleFilterBorderValue);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                simpleFilter(mattempc, simpleFilterXValue, simpleFilterYValue, simpleFilterAnchorXValue, simpleFilterAnchorYValue, simpleFilterDeltaValue, simpleFilterDataValues, simpleFilterBorderValue);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                simpleFilter(ROI, simpleFilterXValue, simpleFilterYValue, simpleFilterAnchorXValue, simpleFilterAnchorYValue, simpleFilterDeltaValue, simpleFilterDataValues, simpleFilterBorderValue);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }

            delete simpleFilterDataValues;
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(14,hstr);
    }
    if(functionFlag == 15)
    {
        dilateShape   =  dialdilate->shape;
        dilateSizeX   =  dialdilate->sizeX;
        dilateSizeY   =  dialdilate->sizeY;
        dilateAnchorX =  dialdilate->anchorX;
        dilateAnchorY =  dialdilate->anchorY;;
        dilateIterationsValue = dialdilate->iterations;
        dilateBorder  =  dialdilate->border;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5, hstr6, hstr7;

        if(dilateShape == MORPH_RECT)
            hstr1 = tr("morph_rect,");
        if(dilateShape == MORPH_CROSS)
            hstr1 = tr("morph_cross,");
        if(dilateShape == MORPH_ELLIPSE)
            hstr1 = tr("morph_ellipse,");

        hstr = tr("dilate(") + hstr1 + tr(",") + hstr3.setNum(dilateSizeX) + tr(",")
           + hstr4.setNum(dilateSizeY) + tr(",") + hstr5.setNum(dilateAnchorX) + tr(",") + hstr6.setNum(dilateAnchorY)
           + tr(",") + hstr7.setNum(dilateIterationsValue) + tr(",");

        if(dilateBorder == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant);");
        if(dilateBorder == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate);");
        if(dilateBorder == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect);");
        if(dilateBorder == BORDER_REFLECT_101)
            hstr = hstr + tr("border_reflect_101);");

        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                dilate(mattempg, dilateShape, dilateSizeX, dilateSizeY, dilateAnchorX, dilateAnchorY, dilateIterationsValue, dilateBorder);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 7)|(index == 8))
            {
                mattempc = matbuffc.clone();
                dilate(mattempc, dilateShape, dilateSizeX, dilateSizeY, dilateAnchorX, dilateAnchorY, dilateIterationsValue, dilateBorder);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                dilate(ROI, dilateShape, dilateSizeX, dilateSizeY, dilateAnchorX, dilateAnchorY, dilateIterationsValue, dilateBorder);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(15,hstr);
    }
    if(functionFlag == 16)
    {
        erodeShape   =  dialerode->shape;
        erodeSizeX   =  dialerode->sizeX;
        erodeSizeY   =  dialerode->sizeY;
        erodeAnchorX =  dialerode->anchorX;
        erodeAnchorY =  dialerode->anchorY;;
        erodeIterationsValue = dialerode->iterations;
        erodeBorder  =  dialerode->border;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5, hstr6, hstr7;

        if(erodeShape == MORPH_RECT)
            hstr1 = tr("morph_rect,");
        if(erodeShape == MORPH_CROSS)
            hstr1 = tr("morph_cross,");
        if(erodeShape == MORPH_ELLIPSE)
            hstr1 = tr("morph_ellipse,");

        hstr = tr("erode(") + hstr1 + tr(",") + hstr3.setNum(erodeSizeX) + tr(",")
           + hstr4.setNum(erodeSizeY) + tr(",") + hstr5.setNum(erodeAnchorX) + tr(",") + hstr6.setNum(erodeAnchorY)
           + tr(",") + hstr7.setNum(erodeIterationsValue) + tr(",");

        if(erodeBorder == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant);");
        if(erodeBorder == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate);");
        if(erodeBorder == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect);");
        if(erodeBorder == BORDER_REFLECT_101)
        hstr = hstr + tr("border_reflect_101);");

        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                erode(mattempg, erodeShape, erodeSizeX,erodeSizeY, erodeAnchorX, erodeAnchorY, erodeIterationsValue, erodeBorder);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                erode(mattempc, erodeShape, erodeSizeX,erodeSizeY, erodeAnchorX, erodeAnchorY, erodeIterationsValue, erodeBorder);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                erode(ROI, erodeShape, erodeSizeX,erodeSizeY, erodeAnchorX, erodeAnchorY, erodeIterationsValue, erodeBorder);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        else if(index >= 12)
            validateCurrentFcn(16,hstr);
    }
    if(functionFlag == 17)
    {
        morphologyFilterOpMethodValue   = dialmorph->opMethod;
        morphologyFilterShapeValue      = dialmorph->shape;
        morphologyFilterSizeXValue      = dialmorph->sizeX;
        morphologyFilterSizeYValue      = dialmorph->sizeY;
        morphologyFilterAnchorXValue    = dialmorph->anchorX;
        morphologyFilterAnchorYValue    = dialmorph->anchorY;
        morphologyFilterIterationsValue = dialmorph->iterations;
        morphologyFilterBorderValue     = dialmorph->border;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5, hstr6, hstr7, hstr8;

        if(morphologyFilterOpMethodValue == MORPH_OPEN)
            hstr1 = tr("open,");
        if(morphologyFilterOpMethodValue == MORPH_CLOSE)
            hstr1 = tr("close,");
        if(morphologyFilterOpMethodValue == MORPH_GRADIENT)
            hstr1 = tr("gradient,");
        if(morphologyFilterOpMethodValue == MORPH_TOPHAT)
            hstr1 = tr("tophat,");
        if(morphologyFilterOpMethodValue == MORPH_BLACKHAT)
            hstr1 = tr("blackhat,");

        if(morphologyFilterShapeValue == MORPH_RECT)
            hstr2 = tr("morph_rect,");
        if(morphologyFilterShapeValue == MORPH_CROSS)
            hstr2 = tr("morph_cross,");
        if(morphologyFilterShapeValue == MORPH_ELLIPSE)
            hstr2 = tr("morph_ellipse,");

        hstr = tr("morphtrans(") + hstr1 + hstr2 + hstr3.setNum(morphologyFilterSizeXValue) + tr(",")
           + hstr4.setNum(morphologyFilterSizeYValue) + tr(",") + hstr5.setNum(morphologyFilterAnchorXValue) + tr(",") + hstr6.setNum(morphologyFilterAnchorYValue)
           + tr(",") + hstr7.setNum(morphologyFilterIterationsValue) + tr(",");

        if(morphologyFilterBorderValue == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant);");
        if(morphologyFilterBorderValue == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate);");
        if(morphologyFilterBorderValue == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect);");
        if(morphologyFilterBorderValue == BORDER_REFLECT_101)
            hstr = hstr + tr("border_reflect_101);");

        if(index < 12)
        {
            if((index == 1)|(index == 2)|(index == 3))
            {
                mattempg = matbuffg.clone();
                morphologyfilter(mattempg, morphologyFilterOpMethodValue, morphologyFilterShapeValue, morphologyFilterSizeXValue, morphologyFilterSizeYValue, morphologyFilterAnchorXValue, morphologyFilterAnchorYValue, morphologyFilterIterationsValue, morphologyFilterBorderValue);

                img3 = calculatehistogram(mattempg);
                resetSinglePic(mattempg,2);
                resetSinglePic(img3,3);
            }
            if((index == 0)|(index == 5)|(index == 6)|(index == 8))
            {
                mattempc = matbuffc.clone();
                morphologyfilter(mattempc, morphologyFilterOpMethodValue, morphologyFilterShapeValue, morphologyFilterSizeXValue, morphologyFilterSizeYValue, morphologyFilterAnchorXValue, morphologyFilterAnchorYValue, morphologyFilterIterationsValue, morphologyFilterBorderValue);

                img6 = calculatehistogram(mattempc);
                resetSinglePic(mattempc,5);
                resetSinglePic(img6,6);
            }
            if(index == 9)
            {
                ROI = ROIBuff.clone();
                morphologyfilter(ROI, morphologyFilterOpMethodValue, morphologyFilterShapeValue, morphologyFilterSizeXValue, morphologyFilterSizeYValue, morphologyFilterAnchorXValue, morphologyFilterAnchorYValue, morphologyFilterIterationsValue, morphologyFilterBorderValue);

                ROIHist = calculatehistogram(ROI);
                resetSinglePic(ROI,ROIIMG);
                resetSinglePic(ROIHist,ROIHIST);
            }
            newLineInText(hstr);
        }
        if(index >= 12)
            validateCurrentFcn(17,hstr);
    }
    if(functionFlag == 18)
    {
        calcHoughLinesPropValue         = dialhoughlines->prob;
        calcHoughLinesRhoValue          = dialhoughlines->rho;
        calcHoughLinesRhoDivValue       = dialhoughlines->rhoDiv;
        calcHoughLinesThresholdValue    = dialhoughlines->threshold;
        calcHoughLinesThetaValue        = dialhoughlines->theta;
        calcHoughLinesThetaDivValue     = dialhoughlines->thetaDiv;
        calcHoughLinesPRhoValue         = dialhoughlines->rho;
        calcHoughLinesPThetaValue       = dialhoughlines->theta;
        calcHoughLinesPThresholdValue   = dialhoughlines->threshold;
        calcHoughLinesPMinLengthValue   = dialhoughlines->minLength;
        calcHoughLinesPMaxGapValue      = dialhoughlines->maxGap;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5;
        if(calcHoughLinesPropValue == false)
            hstr = tr("calchoughlines(") + hstr1.setNum(calcHoughLinesRhoValue) + tr(",") + hstr2.setNum(calcHoughLinesRhoDivValue) + tr(",") + hstr3.setNum(calcHoughLinesThresholdValue) + tr(",")
               + hstr4.setNum(calcHoughLinesThetaValue) + tr(",") + hstr5.setNum(calcHoughLinesThetaDivValue) + tr(");");
        if(calcHoughLinesPropValue == true)
            hstr = tr("calchoughlinesp(") + hstr1.setNum(calcHoughLinesPRhoValue) + tr(",") + hstr2.setNum(calcHoughLinesPThetaValue) + tr(",") + hstr3.setNum(calcHoughLinesPThresholdValue) + tr(",")
                + hstr4.setNum(calcHoughLinesPMinLengthValue) + tr(",") + hstr5.setNum(calcHoughLinesPMaxGapValue) + tr(");");

        if(index < 12)
        {
            if(dialhoughlines->prob == false)
            {
                if(index == 9)
                {
                    calcLinesHoughROI.clear();
                    ROI = ROIBuff.clone();
                    if(ROI.channels() > 1)
                        cvtColor(ROI,ROI,CV_BGR2GRAY);
                    calcHoughLines(ROI, calcLinesHoughROI, calcHoughLinesRhoValue, calcHoughLinesRhoDivValue, calcHoughLinesThresholdValue, calcHoughLinesThetaValue,calcHoughLinesThetaDivValue);
                    refreshHoughLinesTbldata(calcLinesHoughROI);
                }
                else if(index < 12)
                {
                    linesHough.clear();
                    calcHoughLines(mattempg,linesHough, calcHoughLinesRhoValue, calcHoughLinesRhoDivValue, calcHoughLinesThresholdValue, calcHoughLinesThetaValue,calcHoughLinesThetaDivValue);
                    refreshHoughLinesTbldata(linesHough);
                }
            }
            if(dialhoughlines->prob == true)
            {

                if(index == 9)
                {
                    calcLinesHoughPROI.clear();
                    if(ROI.channels() > 1)
                        cvtColor(ROI,ROI,CV_BGR2GRAY);
                    ROI = ROIBuff.clone();
                    calcHoughLinesP(ROI,calcLinesHoughPROI,calcHoughLinesPRhoValue, calcHoughLinesPThetaValue, calcHoughLinesPThresholdValue, calcHoughLinesPMinLengthValue, calcHoughLinesPMaxGapValue);
                    refreshHoughLinesPTbldata(calcLinesHoughPROI);
                }
                else if(index < 12)
                {
                    linesHoughP.clear();
                    calcHoughLinesP(mattempg,linesHoughP,calcHoughLinesPRhoValue,calcHoughLinesPThetaValue,calcHoughLinesPThresholdValue, calcHoughLinesPMinLengthValue, calcHoughLinesPMaxGapValue);
                    refreshHoughLinesPTbldata(linesHoughP);
                }
            }

            drawHoughLines();
            newLineInText(hstr);
        }
        if(index >= 12)
        {
            validateCurrentFcn(18,hstr);
            if(index == 12)
                timerRefreshHoughLinesTbl->start(1000);
            if(index == 13)
                timerRefreshHoughLinesTblVideo->start(1000);
        }
    }
    if(functionFlag == 19)
    {
        calcHoughCirclesMethodValue = dialhoughcircles->method;
        calcHoughCirclesInvRatioValue = dialhoughcircles->invRatio;
        calcHoughCirclesMinDistValue = dialhoughcircles->minDist;
        calcHoughCirclesCannyThresholdValue = dialhoughcircles->cannyThreshold;
        calcHoughCirclesThresholdValue = dialhoughcircles->threshold;
        calcHoughCirclesMinRadiusValue = dialhoughcircles->minRadius;
        calcHoughCirclesMaxRadiusValue = dialhoughcircles->maxRadius;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5, hstr6, hstr7;
        hstr = tr("calchoughcircles(") + hstr1.setNum(calcHoughCirclesMethodValue) + tr(",") + hstr2.setNum(calcHoughCirclesInvRatioValue) + tr(",") + hstr3.setNum(calcHoughCirclesMinDistValue) + tr(",")
           + hstr4.setNum(calcHoughCirclesCannyThresholdValue) + tr(",") + hstr5.setNum(calcHoughCirclesThresholdValue) + tr(",")
           + hstr6.setNum(calcHoughCirclesMinRadiusValue) + tr(",") + hstr7.setNum(calcHoughCirclesMaxRadiusValue) + tr(");");        

        if(index < 12)
        {
            if(index == 9)
            {
                calcCirclesHoughROI.clear();
                if(ROI.channels() > 1)
                    cvtColor(ROI,ROI,CV_BGR2GRAY);
                ROI = ROIBuff.clone();
                calcHoughCircles(ROI, calcCirclesHoughROI, calcHoughCirclesMethodValue, calcHoughCirclesInvRatioValue, calcHoughCirclesMinDistValue, calcHoughCirclesCannyThresholdValue, calcHoughCirclesThresholdValue, calcHoughCirclesMinRadiusValue, calcHoughCirclesMaxRadiusValue);
                refreshHoughCirclesTbldata(calcCirclesHoughROI);
            }
            else if(index < 12)
            {
                circlesHough.clear();
                calcHoughCircles( mattempg, circlesHough, calcHoughCirclesMethodValue, calcHoughCirclesInvRatioValue, calcHoughCirclesMinDistValue, calcHoughCirclesCannyThresholdValue, calcHoughCirclesThresholdValue, calcHoughCirclesMinRadiusValue, calcHoughCirclesMaxRadiusValue);
                refreshHoughCirclesTbldata(circlesHough);
            }

            newLineInText(hstr);
            if(dialhoughcircles->drawFlag == true)
                drawHoughCircles();
        }
        else if(index >= 12)
        {
            if(index == 12)
                timerRefreshHoughCirclesTbl->start(1000);
            if(index == 13)
                timerRefreshHoughCirclesTblVideo->start(1000);
            validateCurrentFcn(19,hstr);
        }
    }
    if(functionFlag == 20)
    {
        bool    harris    = dialcornerdetect->harris;
        bool    shiTomasi = dialcornerdetect->shiTomasi;
        cornerDetectSobelSizeValue = dialcornerdetect->sobelSize;
        cornerDetectBlockSizeValue = dialcornerdetect->blockSize;
        cornerDetectBorderValue    = dialcornerdetect->borderType;
        cornerDetectQualityValue   = dialcornerdetect->quality;
        cornerDetectCornerFlagValue = true;
        if(harris == true && shiTomasi == false)
            cornerDetectCornerFlagValue = true;
        else if(harris == false && shiTomasi == true)
            cornerDetectCornerFlagValue = false;

        QString hstr, hstr1, hstr2, hstr3, hstr4;
        if( harris == 1)
            hstr3 = tr("harris");
        if( shiTomasi == 1)
            hstr3 = tr("shitomasi");

        hstr = tr("cornerdetect(") + hstr1.setNum(cornerDetectBlockSizeValue) + tr(",") + hstr2.setNum(cornerDetectSobelSizeValue) + tr(",") + hstr3 + tr(",");

        if(cornerDetectBorderValue == BORDER_CONSTANT)
            hstr = hstr + tr("border_constant,");
        if(cornerDetectBorderValue == BORDER_REPLICATE)
            hstr = hstr + tr("border_replicate,");
        if(cornerDetectBorderValue == BORDER_REFLECT)
            hstr = hstr + tr("border_reflect,");
        if(cornerDetectBorderValue == BORDER_REFLECT_101)
            hstr = hstr + tr("border_reflect_101,");

        hstr = hstr + hstr4.setNum(cornerDetectQualityValue) + tr(");");

        if(index < 12)
        {
            if(index < 9)
            {
                cornerdetect(mattempg, corners, cornerDetectBlockSizeValue,cornerDetectSobelSizeValue, cornerDetectCornerFlagValue, cornerDetectBorderValue, cornerDetectQualityValue,Mat());
                refreshCornersTbldata(corners);
            }
            if(index == 9)
            {
                if(ROI.channels() > 1)
                    cvtColor(ROI,ROI,CV_BGR2GRAY);
                ROI = ROIBuff.clone();
                cornerdetect(ROI, cornersROI, cornerDetectBlockSizeValue,cornerDetectSobelSizeValue, cornerDetectCornerFlagValue, cornerDetectBorderValue, cornerDetectQualityValue,Mat());
                refreshCornersTbldata(cornersROI);
            }
            if(dialcornerdetect->drawFlag == true)
                drawCornerCircles();
            newLineInText(hstr);

        }
        else if(index >= 12)
        {            
            validateCurrentFcn(20,hstr);
            if(index == 12)
                timerRefreshCornersTbl->start(1000);
            if(index == 13)
                timerRefreshCornersTblVideo->start(1000);
        }
    }
    if(functionFlag == 23)
    {
        FASTThreshold = dialfast->threshold;
        FASTNMS = dialfast->NMS;
        FASTType = dialfast->type;

        QString hstr, hstr1, hstr2;
        hstr = tr("fast(") + hstr1.setNum(FASTThreshold) + tr(" ,") + hstr2.setNum(FASTNMS) + tr(" ,");

        if(FASTType == 0 )
            hstr = hstr + tr("5_8);");
        if(FASTType == 1 )
            hstr = hstr + tr("7_12);");
        if(FASTType == 2 )
            hstr = hstr + tr("9_16);");

        if(index < 12)
        {
            FASTKeyPoints.clear();
            if(index == 9)
            {
                if(ROI.channels() > 1)
                    cvtColor(ROI,ROI,CV_BGR2GRAY);
                FASTX(ROI, FASTKeyPointsROI, FASTThreshold, FASTNMS, FASTType);
                refreshTblFASTKeyPoints(FASTKeyPointsROI);
            }
            if(index != 9)
            {
                FASTX(mattempg, FASTKeyPoints, FASTThreshold, FASTNMS, FASTType);
                refreshTblFASTKeyPoints(FASTKeyPoints);
            }

            drawFASTFeatures();
            newLineInText(hstr);
        }
        if(index >= 12)
        {
            validateCurrentFcn(functionFlag, hstr);
            if(index == 12)
                timerRefreshFASTTbl->start(1000);
            if(index == 13)
                timerRefreshFASTTblVideo->start(1000);
        }
    }
    if(functionFlag == 24)
    {
        ORBNFeatures = dialorb->nFeatures;
        ORBPatchSize = dialorb->patchSize;
        ORBNLevels = dialorb->nLevels;
        ORBEdgethreshold = dialorb->edgeThreshold;
        ORBScaleFactor = dialorb->scaleFactor;
        ORBFirstLevel = dialorb->firstLevel;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5, hstr6;
        hstr = tr("orb(") + hstr1.setNum(ORBNFeatures) + tr(" ,") + hstr2.setNum(ORBScaleFactor) + tr(" ,") + hstr3.setNum(ORBNLevels) + tr(" ,")
                + hstr4.setNum(ORBEdgethreshold) + tr(" ,") + hstr5.setNum(ORBFirstLevel) + tr(" ,") + hstr6.setNum(ORBPatchSize) + tr(");");

        if(index < 12)
        {
            ORB FtORB = ORB(ORBNFeatures,ORBScaleFactor, ORBNLevels,ORBEdgethreshold,ORBFirstLevel, 2, ORB::HARRIS_SCORE, ORBPatchSize);
            ORBKeyPoints.clear();

            if(dialorb->FASTKeyPoints == true)
            {
                if(index == 9)
                {
                    ORBKPFlag = true;
                    ORBKeyPointsROI = FASTKeyPointsROI;
                }
                else
                {
                    ORBKPFlag = true;
                    ORBKeyPoints = FASTKeyPoints;
                }
            }
            else if(dialorb->BRISKKeyPoints == true)
            {
                if(index == 9)
                {
                    ORBKPFlag = true;
                    ORBKeyPointsROI = BRISKKeyPointsROI;
                }
                else
                {
                    ORBKPFlag = true;
                    ORBKeyPoints = BRISKKeyPoints;
                }
            }
            else
                ORBKPFlag = false;

            ORBDescriptors.release();
            if(index == 9)
            {

                if(ROI.channels() > 1)
                    cvtColor(ROI,ROI,CV_BGR2GRAY);
                ROI = ROIBuff.clone();
                FtORB(ROI, Mat(), ORBKeyPointsROI, ORBDescriptorsROI, ORBKPFlag);
                refreshTblORBKeyPoints(ORBKeyPointsROI);

            }
            if(index != 9)
            {
                FtORB(mattempg, Mat(), ORBKeyPoints, ORBDescriptors, ORBKPFlag);                
                refreshTblORBKeyPoints(ORBKeyPoints);
            }

            drawORBFeatures();
            newLineInText(hstr);
        }
        if(index >= 12)
        {
            validateCurrentFcn(functionFlag, hstr);
            if(index == 12)
                timerRefreshORBTbl->start(1000);
            if(index == 13)
                timerRefreshORBTblVideo->start(1000);
        }
    }
    if(functionFlag == 25)
    {
        BRISKThresh = dialbrisk->thresh;
        BRISKOctaves = dialbrisk->octaves;
        BRISKPatternScale = dialbrisk->patternScale;

        QString hstr, hstr1, hstr2, hstr3;
        hstr = tr("brisk(") + hstr1.setNum(BRISKThresh) + tr(" ,") + hstr2.setNum(BRISKOctaves) + tr(" ,") + hstr3.setNum(BRISKPatternScale) + tr(");");
        if(index < 12)
        {
            BRISK FtBRISK = BRISK(BRISKThresh, BRISKOctaves, BRISKPatternScale);
            BRISKKeyPoints.clear();

            BRISKDescriptors.release();
            if(dialbrisk->FASTKeyPoints == true)
            {
                BRISKKeyPoints = FASTKeyPoints;
                BRISKKPFlag= true;
            }
            if(dialbrisk->ORBKeyPoints == true)
            {
                BRISKKeyPoints = ORBKeyPoints;
                BRISKKPFlag = true;
            }
            else
                BRISKKPFlag = false;

            if(index == 9)
            {
                if(ROI.channels() > 1)
                    cvtColor(ROI,ROI,CV_BGR2GRAY);
                ROI = ROIBuff.clone();
                FtBRISK(ROI, Mat(), BRISKKeyPointsROI, BRISKDescriptorsROI, BRISKKPFlag);
                refreshTblBRISKKeyPoints(BRISKKeyPointsROI);
            }
            if(index != 9)
            {
                FtBRISK(mattempg, Mat(), BRISKKeyPoints, BRISKDescriptors, BRISKKPFlag);
                refreshTblBRISKKeyPoints(BRISKKeyPoints);
            }

            drawBRISKFeatures();
            newLineInText(hstr);

        }
        if(index >= 12)
        {
            validateCurrentFcn(functionFlag, hstr);
            if(index == 12)
                timerRefreshORBTbl->start(1000);
            if(index == 13)
                timerRefreshORBTblVideo->start(1000);
        }
    }
    if(functionFlag == 26)
    {
        FREAKOrientationNormalization = dialfreak->orientationNormalized;
        FREAKScaleNormalized = dialfreak->scaleNormalized;
        FREAKNOctaves = dialfreak->nOctaves;
        FREAKPatternScale = dialfreak->patternScale;

        QString hstr, hstr1, hstr2, hstr3, hstr4;
        hstr = tr("freak(") + hstr1.setNum(FREAKOrientationNormalization) + tr(" ,") + hstr2.setNum(FREAKScaleNormalized) + tr(" ,") + hstr3.setNum(FREAKNOctaves) + tr(" ,") + hstr4.setNum(FREAKPatternScale) + tr(");");
        if(index < 12)
        {
            if(dialfreak->FASTKeyPoints == true)
            {
                if(index == 9)
                    FREAKKeyPoints = FASTKeyPoints;
                else
                    FREAKKeyPointsROI = FASTKeyPointsROI;
            }
            if(dialfreak->ORBKeyPoints == true)
            {
                if(index == 9)
                    FREAKKeyPoints = ORBKeyPoints;
                else
                    FREAKKeyPointsROI = ORBKeyPointsROI;
            }
            if(dialfreak->BRISKKeyPoints == true)
            {
                if(index == 9)
                    FREAKKeyPoints = BRISKKeyPoints;
                else
                    FREAKKeyPointsROI = BRISKKeyPointsROI;
            }
            FREAK FtFREAK(FREAKOrientationNormalization, FREAKScaleNormalized, FREAKPatternScale, FREAKNOctaves);
            if(index == 9)
            {
                if(ROI.channels() > 1)
                    cvtColor(ROI,ROI,CV_BGR2GRAY);
                ROI = ROIBuff.clone();
                FtFREAK.compute(ROI, FREAKKeyPointsROI, FREAKDescriptorsROI);
                refreshTblFREAKKeyPoints(FREAKKeyPointsROI);
            }
            if(index != 9)
            {
                FtFREAK.compute(mattempg, FREAKKeyPoints, FREAKDescriptors);
                refreshTblFREAKKeyPoints(FREAKKeyPoints);
            }
            drawFREAKFeatures();
            newLineInText(hstr);
        }
        if(index >= 12)
        {
            validateCurrentFcn(functionFlag, hstr);
            if(index == 12)
                timerRefreshFREAKTbl->start(1000);
            if(index == 13)
                timerRefreshFREAKTblVideo->start(1000);
        }
    }
    if(functionFlag == 29)
    {
        MSERDelta = dialmser->delta;
        MSERMinArea = dialmser->minArea;
        MSERMaxArea = dialmser->maxArea;
        MSERMaxVariation = dialmser->maxVariation;
        MSERMinDiversity = dialmser->minDiversity;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5;
        hstr = tr("mser(") + hstr1.setNum(MSERDelta) + tr(" ,") + hstr2.setNum(MSERMinArea) + tr(" ,") + hstr3.setNum(MSERMaxArea) + tr(" ,") 
                + hstr4.setNum(MSERMaxVariation) + tr(" ,") + hstr5.setNum(MSERMinDiversity) + tr(");");

        if(index < 12)
        {
            FtMSER  = MSER( MSERDelta, MSERMinArea, MSERMaxArea,MSERMaxVariation ,MSERMinDiversity);
            MSERPoints.clear();
            if(index == 9)
            {
                if(ROI.channels() > 1)
                    cvtColor(ROI,ROI,CV_BGR2GRAY);
                ROI = ROIBuff.clone();
                FtMSER.operator ()(ROI, MSERPointsROI, Mat());
                calculateHulls(MSERPointsROI, MSERHullsROI);
                refreshTblMSERPoints(MSERHullsROI);
            }
            if(index != 9)
            {
                FtMSER(mattempg, MSERPoints, Mat());
                calculateHulls(MSERPoints, MSERHulls);
                refreshTblMSERPoints(MSERHulls);
            }

            drawMSERFeatures();
            newLineInText(hstr);
        }

        if(index >= 12)
        {
            validateCurrentFcn(functionFlag, hstr);
            if(index == 12)
                timerRefreshMSERTbl->start(1000);
            if(index == 13)
                timerRefreshMSERTblVideo->start(1000);
        }
    }
    if(functionFlag == 30)
    {
        MSEREvalSortBySize  = dialmsereval->sortBySize;
        MSEREvalSortByHull  = dialmsereval->sortByHull;
        MSEREvalMinSize     = dialmsereval->minSize;
        MSEREvalMaxSize     = dialmsereval->maxSize;
        MSEREvalMinRatio    = dialmsereval->minRatio;
        MSEREvalMaxRatio    = dialmsereval->maxRatio;

        QString hstr, hstr1, hstr2, hstr3, hstr4, hstr5, hstr6;
        hstr = tr("msereval(") + hstr1.setNum(MSEREvalSortBySize) + tr(" ,") + hstr2.setNum(MSEREvalSortByHull) + tr(" ,") + hstr3.setNum(MSEREvalMinSize) + tr(" ,")
                + hstr4.setNum(MSEREvalMaxSize) + tr(" ,") + hstr5.setNum(MSEREvalMinRatio) + tr(" ,") + hstr6.setNum(MSEREvalMaxRatio) + tr(");");

        evaluateMSERData();
        if(index < 12)
            refreshTblMSEREvalPoints(MSEREvalHulls);
        newLineInText(hstr);
        if(index >= 12)
        {
            validateCurrentFcn(functionFlag, hstr);
            if(index == 12)
                timerRefreshMSEREvalTbl->start(1000);
            if(index == 13)
                timerRefreshMSEREvalTblVideo->start(1000);
        }
    }
}

void EAMViewer::drawBRISKFeatures()
{
    if(dialbrisk->drawKeyPointsFlag)
    {
        if(index != 9 && index != 12)
            cvtColor(mattempg,matdrawn, COLOR_GRAY2BGR);

        if(index == 9)
            cvtColor( ROIdrawn, ROIBuff, COLOR_GRAY2BGR);

        if((index < 12) && (index != 9))
            drawKeyPoints(BRISKKeyPoints);

        if(index == 12)
            drawKeyPoints(BRISKKeyPointsCam);

        if(index == 13)
            drawKeyPoints(BRISKKeyPointsVid);
    }
    else
    {
        if(index != 9 && index != 12 && index != 13)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
    }
}

void EAMViewer::drawFASTFeatures()
{
    if(dialfast->drawKeyPointsFlag)
    {
        if(index != 9 && index != 12)
            cvtColor(mattempg,matdrawn, COLOR_GRAY2BGR);

        if(index == 9)
            cvtColor( ROIdrawn, ROIBuff, COLOR_GRAY2BGR);

        if((index < 12) && (index != 9))
            drawKeyPoints(FASTKeyPoints);

        if(index == 12)
            drawKeyPoints(FASTKeyPointsCam);

        if(index == 13)
            drawKeyPoints(FASTKeyPointsVid);
    }
    else
    {
        if(index != 9 && index != 12 && index != 13)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
    }
}

void EAMViewer::drawCornerCircles()
{
    int color = dialcornerdetect->color;
    int thickness = dialcornerdetect->lineThickness;

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    if(index != 9 && index != 12)
        matdrawn = matbuffg.clone();

    if(index == 9)
        for(unsigned int i = 0; i < cornersROI.size(); i++)
            circle( ROIdrawn, Point(cornersROI[i][0],cornersROI[i][1]),4,Scalar( color, color, color ), thickness, 8, 0 );
    else if(index < 12)
        for(unsigned int i = 0; i < corners.size(); i++)
                circle( matdrawn, Point(corners[i][0],corners[i][1]),4,Scalar( color, color, color ), thickness, 8, 0 );    

    if(index == 12)
        for(unsigned int i = 0; i < cornersCam.size(); i ++)
            circle(camImg, Point(cornersCam[i][0],cornersCam[i][1]),4,Scalar( color, color, color ), thickness, 8, 0 );
    if(index == 13)
        for(unsigned int i = 0; i < cornersVideo.size(); i ++)
            circle(vidImg, Point(cornersVideo[i][0],cornersVideo[i][1]),4,Scalar( color, color, color ), thickness, 8, 0 );

    if(index != 9 && index != 12 && index != 13)
        resetSinglePic(matdrawn,2);
    if(index == 9)
        resetSinglePic(ROIdrawn,ROIIMG);
}

void EAMViewer::drawFREAKFeatures()
{
    if(dialfreak->drawKeyPointsFlag == true)
    {
        if(index != 9 && index != 12)
            cvtColor(mattempg,matdrawn, COLOR_GRAY2BGR);

        if(index == 9)
            cvtColor( ROIdrawn, ROIBuff, COLOR_GRAY2BGR);

        if((index < 12) && (index != 9))
            drawKeyPoints(FREAKKeyPoints);

        if(index == 12)
            drawKeyPoints(FREAKKeyPointsCam);

        if(index == 13)
            drawKeyPoints(FREAKKeyPointsVid);
    }
    else
    {
        if(index != 9 && index != 12 && index != 13)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
    }
}

void EAMViewer::drawMSERFeatures()
{
    if(index != 9 && index != 12 && index != 13)
        cvtColor(mattempg,matdrawn, COLOR_GRAY2BGR);

    if(index == 9)
        cvtColor( ROIdrawn, ROIBuff, COLOR_GRAY2BGR);

    bool drawnFlag = false;
    int thickness = dialmser->lineThickness;
    if(dialmser->drawFlagKeyPoints == true)
    {
        if(index == 9)
        {
            drawBlobPoints(MSERPointsROI, thickness);
            drawnFlag = true;
        }
        if(index != 12)
        {
            drawBlobPoints(MSERPoints, thickness);
            drawnFlag = true;
        }
        if(index == 12)
            drawBlobPoints(MSERPointsCam, thickness);
        if(index == 13)
            drawBlobPoints(MSERPointsVid, thickness);
    }
    if(dialmser->drawFlagHulls == true)
    {
        if(index == 9)
        {
            drawBlobHulls(MSERHullsROI, thickness);
            drawnFlag = true;
        }
        else if(index < 12)
        {
            drawBlobHulls(MSERHulls, thickness);
            drawnFlag = true;
        }
        if(index == 12)
            drawBlobHulls(MSERHullsCam, thickness);
        if(index == 13)
            drawBlobHulls(MSERHullsVid, thickness);
    }
    if(dialmser->drawFlagEllipses)
    {
        if(index == 9)
        {
            calculateEllipses(MSERPointsROI, MSERHullsROI, MSEREllipsesROI);
            drawBlobEllipses(MSEREllipsesROI, thickness);
            drawnFlag = true;
        }
        else if(index < 12)
        {
            calculateEllipses(MSERPoints, MSERHulls, MSEREllipses);
            drawBlobEllipses(MSEREllipses, thickness);
            drawnFlag = true;
        }
        if(index == 12)
        {
            calculateEllipses(MSERPointsCam, MSERHullsCam, MSEREllipsesCam);
            drawBlobEllipses(MSEREllipsesCam, thickness);
        }
        if(index == 13)
        {
            calculateEllipses(MSERPointsVid, MSERHullsVid, MSEREllipsesVid);
            drawBlobEllipses(MSEREllipsesVid, thickness);
        }
    }

    if(drawnFlag == false)
    {
        if(index != 9 && index != 12 && index != 13)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
    }
}

void EAMViewer::drawMSEREvalFeatures()
{
    if(index != 9 && index != 12 && index != 13)
        cvtColor(mattempg,matdrawn, COLOR_GRAY2BGR);

    if(index == 9)
        cvtColor( ROIdrawn, ROIBuff, COLOR_GRAY2BGR);

    bool drawnFlag = false;
    int thickness = dialmsereval->thickness;
    if(dialmsereval->drawFlagKeyPoints == true)
    {
        drawBlobPoints(MSEREvalPoints, thickness);
        if(index < 12)
            drawnFlag = true;
    }
    if(dialmsereval->drawFlagHulls == true)
    {
        drawBlobHulls(MSEREvalHulls, thickness);
        if(index < 12)
            drawnFlag = true;
    }
    if(dialmsereval->drawFlagEllipses)
    {

        drawBlobEllipses(MSEREvalEllipses, thickness);
        if(index < 12)
            drawnFlag = true;
    }

    if(drawnFlag == false)
    {
        if(index != 9 && index != 12 && index != 13)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
    }
}

void EAMViewer::drawORBFeatures()
{
    if(dialorb->drawKeyPointsFlag)
    {
        if(index != 9 && index != 12)
            cvtColor(mattempg,matdrawn, COLOR_GRAY2BGR);

        if(index == 9)
            cvtColor( ROIdrawn, ROIBuff, COLOR_GRAY2BGR);

        if((index < 12) && (index != 9))
            drawKeyPoints(ORBKeyPoints);

        if(index == 12)
            drawKeyPoints(ORBKeyPointsCam);

        if(index == 13)
            drawKeyPoints(ORBKeyPointsVid);
    }
    else
    {
        if(index != 9 && index != 12 && index != 13)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
    }
}

void EAMViewer::drawingStructuresCircles(bool b)
{
    if(b == true)
        drawHoughCircles();
    if(b == false)
    {
        if(index != 9 && index != 12 && index != 13)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
    }
}

void EAMViewer::drawingStructuresCorners(bool b)
{
    if(b == true)
        drawCornerCircles();
    if(b == false)
    {
        if(index != 9 && index != 12 && index != 13)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
    }
}

void EAMViewer::drawingStructuresLines(bool b)
{
    if(b == true)
        drawHoughLines();
    if(b == false)
    {
        if(index != 9 && index != 12 && index != 13)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
    }
}

void EAMViewer::drawHoughLines()
{
    if(index == 9)
    {
        if(!dialhoughlines->prob)
            drawLines(calcLinesHoughROI);
        if(dialhoughlines->prob)
            drawLines(calcLinesHoughPROI);
    }
    else if(index < 12)
    {
        if(!dialhoughlines->prob)
            drawLines(linesHough);
        if(dialhoughlines->prob)
            drawLines(linesHoughP);
    }
    else if(index == 12)
    {
        if(!dialhoughlines->prob)
            drawLines(calcLinesHoughCam);
        if(dialhoughlines->prob)
            drawLines(calcLinesHoughPCam);
    }
    else if(index == 13)
    {
        if(!dialhoughlines->prob)
            drawLines(calcLinesHoughVideo);
        if(dialhoughlines->prob)
            drawLines(calcLinesHoughPVideo);
    }

    if(index != 9 && index != 12 && index != 13)
        resetSinglePic(matdrawn,2);
    if(index == 9)
        resetSinglePic(ROIdrawn,ROIIMG);
}

void EAMViewer::drawHoughCircles()
{
    int color = dialhoughcircles->color;
    int thickness = dialhoughcircles->lineThickness;

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    else if(index < 12)
        matdrawn = matbuffg.clone();
    if(index == 9)
    {
        for(unsigned int i = 0; i < calcCirclesHoughROI.size(); i++)
        {
            Point center(cvRound(calcCirclesHoughROI[i][0]), cvRound(calcCirclesHoughROI[i][1]));
            int radius = cvRound(calcCirclesHoughROI[i][2]);
            circle( ROIdrawn, center, radius, Scalar(color,color,color), thickness, 8, 0 );
        }
    }
    else if(index < 12)
    {
        for(unsigned int i = 0; i < circlesHough.size(); i++)
        {
            Point center(cvRound(circlesHough[i][0]), cvRound(circlesHough[i][1]));
            int radius = cvRound(circlesHough[i][2]);
            circle( matdrawn, center, radius, Scalar(color,color,color), thickness, 8, 0 );
        }
    }
    if(index == 12)
        for(unsigned int i = 0; i < calcCirclesHoughCam.size(); i++)
        {
            Point center(cvRound(calcCirclesHoughCam[i][0]), cvRound(calcCirclesHoughCam[i][1]));
            int radius = cvRound(calcCirclesHoughCam[i][2]);
            circle( camImg, center, radius, Scalar(color,color,color), thickness, 8, 0 );
        }
    if(index == 13)
        for(unsigned int i = 0; i < calcCirclesHoughVideo.size(); i++)
        {
            Point center(cvRound(calcCirclesHoughVideo[i][0]), cvRound(calcCirclesHoughVideo[i][1]));
            int radius = cvRound(calcCirclesHoughVideo[i][2]);
            circle( vidImg, center, radius, Scalar(color,color,color), thickness, 8, 0 );
        }
    if(index != 9 && index != 12 && index != 13)
        resetSinglePic(matdrawn,2);
    if(index == 9)
        resetSinglePic(ROIdrawn,ROIIMG);
}

void EAMViewer::FPSChanged(int i)
{
    framesPS = float(i);
    timer->stop();
    timer->start(int(1000/framesPS));
    ui->lblFPS->setText(tr("fps: ") + QString::number(framesPS) + tr(" 1/s"));
    ui->sliderFPS->setValue(i);
}

void EAMViewer::FPSChangedVid(int i)
{
    framesPSVid = float(i);
    timerVideo->stop();
    timerVideo->start(int(1000/framesPSVid));
    ui->lblFPSVid->setText(tr("fps: ") + QString::number(framesPSVid) + tr(" 1/s"));
    ui->sliderFPSVid->setValue(i);
}

void EAMViewer::grabAndProcessFrame()
{
    double startTime = clock();

    camDev.read(camImg);
    if(camImg.empty())
    {
        newLineInText(tr("No data from device"));
        startStopGrabbingAndShowingCamera();
        return;
    }
    camImgProc = camImg.clone();
    for(unsigned int h = 0; h < processingToolchainIndex.size(); h++)
        chooseFcnForVidProcessing(processingToolchainIndex.at(h));
    showMat = camImg.clone();


    if(recordFlagCam == true )
    {
        VW.write(camImg);
        writingVidSize++;
    }

    if(showMat.channels() > 1)
    {
        cvtColor(showMat,showMat,CV_BGR2RGB);
        qImg = QImage((uchar*)showMat.data,showMat.cols,showMat.rows,showMat.step,QImage::Format_RGB888);
    }
    else if(showMat.channels() == 1)
        qImg = QImage((uchar*)showMat.data,showMat.cols,showMat.rows,showMat.step,QImage::Format_Indexed8);

    ui->lblOrig->setPixmap(QPixmap::fromImage(qImg));

    double endTime = clock();
    double timeDuration = (endTime - startTime)/CLOCKS_PER_SEC;
    numCam++;
    if(numCam%10 == 0)
    {
        int fps = int(1/timeDuration);
        if(framesPSVid > fps)
            FPSChangedVid(fps);
        numCam = 0;
    }
}

void EAMViewer::grabAndProcessFrameVideo()
{
    double startTime = clock();

    vidDev.read(vidImg);
    vidImgProc = vidImg.clone();
    for(unsigned int h = 0; h < processingVideoToolchainIndex.size(); h++)
        chooseFcnForVidProcessing(processingVideoToolchainIndex.at(h));
    if(vidImg.empty())
    {
        newLineInText(tr("No data from file"));
        startStopGrabbingAndShowingVideo();
        return;
    }
    showMatVideo = vidImg.clone();
    if(timerVideo->isActive())
        sliderCurrentFramePosChanged(false);
    currentVideoFrame++;

    if(recordFlagVid == true )
        VW.write(vidImg);

    if(showMatVideo.channels() > 1)
    {
        cvtColor(showMatVideo,showMatVideo,CV_BGR2RGB);
        qImgVid = QImage((uchar*)showMatVideo.data,showMatVideo.cols,showMatVideo.rows,showMatVideo.step,QImage::Format_RGB888);
    }
    else if(showMatVideo.channels() == 1)
        qImgVid = QImage((uchar*)showMatVideo.data,showMatVideo.cols,showMatVideo.rows,showMatVideo.step,QImage::Format_Indexed8);
   ui->lblOrigVid->setPixmap(QPixmap::fromImage(qImgVid));

   double endTime = clock();
   double timeDuration = (endTime - startTime)/CLOCKS_PER_SEC;
   numVid++;
   if(numVid%10 == 0)
   {
       int fps = int(1/timeDuration);
       if(framesPSVid > fps)
           FPSChangedVid(fps);
       numVid = 0;
   }
   if(currentVideoFrame == vidSize)
   {
       startStopGrabbingAndShowingVideo();
       vidDev.set(CV_CAP_PROP_POS_FRAMES, 0);
       currentVideoFrame = 0;
       ui->sliderCurrentFramePos->setValue(0);
   }
}

void EAMViewer::histogramEqual()
{
    functionFlag = 2;
    QString hstr = tr("histogramequalization();");
    if(index >= 12)
    {
        validateCurrentFcn(functionFlag, hstr);
    }
    else if((index != 9))
    {
        matbuffg = img2.clone();
        histogramequalization(img2);
        img3 = calculatehistogram(img2);

        resetSinglePic(img2,2);
        resetSinglePic(img3,3);
        newLineInText(hstr);
    }
    else
    {
        if(ROI.channels() > 1)
            cvtColor(ROI,ROI,CV_BGR2GRAY);
        histogramequalization(ROI);
        ROIHist = calculatehistogram(ROI);

        resetSinglePic(ROI,ROIIMG);
        resetSinglePic(ROIHist,ROIHIST);
        newLineInText(hstr);
    }
}

void EAMViewer::invertTrans()
{
    functionFlag = 1;
    QString hstr = tr("inversion();");
    if((index == 1)|(index == 2)|(index == 3))
    {
        inversion(img2);
        resetSinglePic(img2,2);
        img3 = calculatehistogram(img2);
        resetSinglePic(img3,3);
        newLineInText(hstr);
    }
    if((index == 0)|(index == 5)|(index == 6)|(index == 8))
    {
        inversion(img5);
        resetSinglePic(img5,5);
        img6 = calculatehistogram(img5);
        resetSinglePic(img6,6);
        newLineInText(hstr);
    }
    if(index == 9)
    {
        inversion(ROI);
        ROIHist = calculatehistogram(ROI);
        resetSinglePic(ROI,ROIIMG);
        resetSinglePic(ROIHist,ROIHIST);
        newLineInText(hstr);
    }
    if(index >= 12)
        validateCurrentFcn(functionFlag,hstr);


}

void EAMViewer::lastSettings()
{
    if((index == 0)|(index == 5)|(index == 6)|(index == 8))
    {
        img5 = matbuffc.clone();
        img6 = calculatehistogram(img5);
        resetSinglePic(img5,5);
        resetSinglePic(img6,6);
    }
    if((index == 1)|(index == 2)|(index == 3))
    {
        img2 = matbuffg.clone();
        img3 = calculatehistogram(img2);
        resetSinglePic(img2,2);
        resetSinglePic(img3,3);
    }
    if(index == 9)
    {
        ROI = ROIBuff.clone();
        ROIHist = calculatehistogram(ROI);
        resetSinglePic(ROI,ROIIMG);
        resetSinglePic(ROIHist,ROIHIST);
    }
}

void EAMViewer::loadCurrentVideoFrame()
{
    fstream file;
    char* c = new char[1000];
    file.open("loading_directory.txt",ios_base::in);

    file.getline(c,1000);
    QString qstr = tr(c) + tr("/frame.jpg");
    if(index == 12)
        imwrite(qstr.toStdString().data(),camImg);
    if(index == 13)
        imwrite(qstr.toStdString().data(),vidImg);
    file.close();
    List.clear();
    QDir dir(tr(c));
    List = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,QDir::Name);
    for( h = (List.size()-1); h >= 0; h--)
    {
        string hstr = List.at(h).fileName().toStdString();
        int p = hstr.find(".");
        QString sstr(tr(hstr.substr(p+1,hstr.length()-1).data()));
        if(sstr.compare(tr("bmp")  ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("dib" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jpg" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jpe" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jpeg",Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jp2" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("png" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("pbm" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("pgm" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("ppm" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("sr"  ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("ras" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("tiff",Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("tif" ,Qt::CaseInsensitive) == 0){}
        else
            List.removeAt(h);
    }
    for( h = 0; h < List.size(); h++)
        if(List.at(h).fileName().compare("frame.jpg",Qt::CaseInsensitive) == 0)

    loadImages(h);
    loadPixmaps();
    newLineInText(tr(c) + tr(" contains: "));
    for( h = 0; h < List.size(); h++)
        newLineInText(tr("      ") + List.at(h).fileName());

    ui->tabWidget->setCurrentWidget(ui->tbOverview);
}

void EAMViewer::loadingDatapath()
{
    closeAllDialogs();
    List.clear();

    PicNum = 0;
    QString str = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home/peter/DA/pics/", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDir dir(str);
    List = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,QDir::Name);

    for( h = (List.size()-1); h >= 0; h--)
    {
        string hstr = List.at(h).fileName().toStdString();
        int p = hstr.find(".");
        QString sstr(tr(hstr.substr(p+1,hstr.length()-1).data()));

        if(sstr.compare(tr("bmp")  ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("dib" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jpg" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jpe" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jpeg",Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("jp2" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("png" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("pbm" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("pgm" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("ppm" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("sr"  ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("ras" ,Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("tiff",Qt::CaseInsensitive) == 0){}
        else if(sstr.compare("tif" ,Qt::CaseInsensitive) == 0){}
        else
            List.removeAt(h);
    }

    fstream file;
    file.open("loading_directory.txt",ios_base::trunc |ios_base::out);
    file << str.toStdString().data() << endl;
    file.close();

    clearROI();
    loadImages(0);
    loadPixmaps();
}

void EAMViewer::loadingDatapathVideos()
{
    closeAllDialogs();
    ListVideos.clear();
    VidNum = 0;
    QString str = QFileDialog::getExistingDirectory(this, tr("Open Video Directory"),"/home/peter/DA/videos/", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDir dir(str);
    List = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,QDir::Name);

    for( h = (List.size()-1); h >= 0; h--)
    {
        string hstr = List.at(h).fileName().toStdString();
        int p = hstr.find(".");
        QString sstr(tr(hstr.substr(p+1,hstr.length()-1).data()));

        if(sstr.compare("avi"  ,Qt::CaseInsensitive) == 0){}
        else
            List.removeAt(h);
    }

    fstream file;
    file.open("loading_vid_directory.txt",ios_base::trunc |ios_base::out);
    file << str.toStdString().data() << endl;
    file.close();
    VidNum = 0;
    loadVideoInBuffer();

    clearROI();
}

void EAMViewer::mappingSlotGVMouseEvent(int i)
{
    if(i == 0)
    {
        ui->tabWidget->addTab(ui->tbColorImage,tr("color image"));
        ui->tabWidget->setCurrentWidget(ui->tbColorImage);
    }
    if(i == 1)
    {
        ui->tabWidget->addTab(ui->tbGrayImage,tr("gray image"));
        ui->tabWidget->setCurrentWidget(ui->tbGrayImage);
    }
    if(i == 2)
    {
        ui->tabWidget->addTab(ui->tbProcGrayImage,tr("processed gray"));
        ui->tabWidget->setCurrentWidget(ui->tbProcGrayImage);
    }
    if(i == 3)
    {
        ui->tabWidget->addTab(ui->tbGrayHist,tr("gray histogram"));
        ui->tabWidget->setCurrentWidget(ui->tbGrayHist);
    }
    if(i == 4)
    {
        previousPic();
    }
    if(i == 5)
    {
        ui->tabWidget->addTab(ui->tbProcColorImage,tr("processed color"));
        ui->tabWidget->setCurrentWidget(ui->tbProcColorImage);
    }
    if(i == 6)
    {
        ui->tabWidget->addTab(ui->tbColorHist,tr("color histogram"));
        ui->tabWidget->setCurrentWidget(ui->tbColorHist);
    }
    if(i == 7)
        nextPic();
}

void EAMViewer::mappingSlotGVKeyPressEvent(int i)
{
    if(i == 0)
    {
        zf[i] = ui->gVColorImg->zoomfactor;
        sceneColorImage->clear();
        sceneColorImage->addPixmap(pm[i].scaled(w0*zf[i],h0*zf[i]));
    }
    if(i == 1)
    {
        zf[i] = ui->gVGrayImg->zoomfactor;
        sceneGrayImage->clear();
        sceneGrayImage->addPixmap(pm[i].scaled(w0*zf[i],h0*zf[i]));
    }
    if(i == 2)
    {
        zf[i] = ui->gVProcGrayImg->zoomfactor;
        sceneProcessedGrayImage->clear();
        sceneProcessedGrayImage->addPixmap(pm[i].scaled(w0*zf[i],h0*zf[i]));
    }
    if(i == 3)
    {
        zf[i] = ui->gVGrayHist->zoomfactor;
        sceneGrayHistogram->clear();
        sceneGrayHistogram->addPixmap(pm[i].scaled(w0*zf[i],h0*zf[i]));
    }
    if(i == 5)
    {
        zf[i] = ui->gVProcColorImg->zoomfactor;
        sceneProcessedColorImage->clear();
        sceneProcessedColorImage->addPixmap(pm[i].scaled(w0*zf[i],h0*zf[i]));
    }
    if(i == 6)
    {
        zf[i] = ui->gVColorHist->zoomfactor;
        sceneColorHistogram->clear();
        sceneColorHistogram->addPixmap(pm[i].scaled(w0*zf[i],h0*zf[i]));
    }
}

void EAMViewer::mappingSlotTMGVKeyPressEvent(int i)
{
    float z = TMViews.at(i)->zoomfactor;
    QPixmap pixmapTM = pmTM.at(i);
    QSize sizePm = pixmapTM.size();
    TMViews.at(i)->scene()->clear();
    TMViews.at(i)->scene()->addPixmap(pixmapTM.scaled(sizePm.width() * z,sizePm.height()*z));
}

void EAMViewer::nextVideo()
{
    if(timerVideo->isActive())
        startStopGrabbingAndShowingVideo();
    ui->tbVideo->setEnabled(false);
    VidNum--;
    if(VidNum == -1)
        VidNum = ListVideos.size() - 1;
    vidDev.release();
    loadVideoSize();
    vidFlag = 1;
    grabAndProcessFrameVideo();
    vidFlag = 0;
    ui->tbVideo->setEnabled(true);
}

void EAMViewer::openCamTab()
{
    ui->tabWidget->addTab(ui->tbCamera,tr("camera"));
    ui->tabWidget->setCurrentWidget(ui->tbCamera);
    index = 12;
}

void EAMViewer::openDatabase()
{
    ui->tabWidget->addTab(ui->tbROIDataBase,tr("roi database"));
    ui->tabWidget->setCurrentWidget(ui->tbROIDataBase);
}

void EAMViewer::openDialAdaptiveThreshold()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 6;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialadaptthresh->show();
}

void EAMViewer::openDialBrisk()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 25;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    if(index != 9 && index != 12)
        matdrawn = matbuffg.clone();

    dialbrisk->show();

}

void EAMViewer::openDialCanny()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 13;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();

    dialcanny->show();
}

void EAMViewer::openDialCustFilt()
{
    closeAllDialogs();
    functionFlag = 14;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialcustfilt->show();
}

void EAMViewer::openDialCornerDetect()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 20;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialcornerdetect->show();
}

void EAMViewer::openDialDilate()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 15;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialdilate->show();
}

void EAMViewer::openDialErode()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 16;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialerode->show();
}

void EAMViewer::openDialFast()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 23;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    if(index != 9 && index != 12)
        matdrawn = matbuffg.clone();

    dialfast->show();
}

void EAMViewer::openDialFreak()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 26;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    if(index != 9 && index != 12)
        matdrawn = matbuffg.clone();

    dialfreak->show();
}

void EAMViewer::openDialGammaTrans()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 4;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialgammatrans->show();
}

void EAMViewer::openDialGaussian()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 9;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
        dialgauss->X = img2.cols;
        dialgauss->Y = img2.rows;
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
        dialgauss->X = img2.cols;
        dialgauss->Y = img2.rows;
    }
    if(index == 9)
    {
        ROIBuff = ROI.clone();

        dialgauss->X = ROI.cols;
        dialgauss->Y = ROI.rows;
    }
    if(index == 12)
    {
        dialgauss->X = camImg.cols;
        dialgauss->Y = camImg.rows;
    }
    dialgauss->showSlot();
    dialgauss->show();
}

void EAMViewer::openDialHoughCircles()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 19;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialhoughcircles->show();
}

void EAMViewer::openDialHoughLines()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 18;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialhoughlines->show();
}

void EAMViewer::openDialLaplacian()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 11;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    diallaplace->show();
}

void EAMViewer::openDialLinearTrans()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 3;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    diallintrans->show();
}

void EAMViewer::openDialMeanBlur()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 7;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
        dialblur->X = img2.cols;
        dialblur->Y = img2.rows;
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
        dialblur->X = img2.cols;
        dialblur->Y = img2.rows;
    }
    if(index == 9)
    {
        ROIBuff = ROI.clone();
        dialblur->X = ROI.cols;
        dialblur->Y = ROI.rows;
    }
    if(index == 12)
    {
        dialblur->X = camImg.cols;
        dialblur->Y = camImg.rows;
    }

    dialblur->showSlot();
    dialblur->show();
}

void EAMViewer::openDialMedianBlur()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 8;
    matbuffg = img2.clone();
    mattempg = img2.clone();
    matbuffc = img5.clone();
    mattempc = img5.clone();
    ROIBuff = ROI.clone();

    if(index == 12)
    {
        if(camImg.cols > camImg.rows)
            dialmedblur->K = camImg.rows;
        else
            dialmedblur->K = camImg.cols;
    }
    else if(index == 13)
    {
        if(vidImg.cols > vidImg.rows)
            dialmedblur->K = vidImg.rows;
        else
            dialmedblur->K = vidImg.cols;
    }
    else if(index == 9)
    {
        if(ROI.cols > ROI.rows)
            dialmedblur->K = ROI.rows;
        else
            dialmedblur->K = ROI.cols;
    }
    if(index < 12 && index != 9)
    {
        if(img2.cols > img2.rows)
            dialmedblur->K = img2.rows;
        else
            dialmedblur->K = img2.cols;
    }

    dialmedblur->showSlot();
    dialmedblur->show();
}

void EAMViewer::openDialMorph()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 17;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialmorph->show();
}

void EAMViewer::openDialMSER()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 29;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    if(index != 9 && index != 12 && index != 13 )
        matdrawn = matbuffg.clone();

    dialmser->show();
}

void EAMViewer::openDialMSEREval()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 30;
    if(dialmser->drawFlagKeyPoints)
        dialmser->drawFlagKeyPoints = false;
    if(dialmser->drawFlagHulls)
        dialmser->drawFlagHulls = false;
    if(dialmser->drawFlagEllipses)
        dialmser->drawFlagEllipses = false;
    if(index == 9)
    {
        MSEREvalPoints  = MSERPointsROI;
        MSEREvalHulls   = MSERHullsROI;
        MSEREvalEllipses= MSEREllipsesROI;
    }
    else if(index < 12)
    {
        MSEREvalPoints  = MSERPoints;
        MSEREvalHulls   = MSERHulls;
        MSEREvalEllipses= MSEREllipses;
    }
    if(index == 12)
    {
        MSEREvalPoints = MSERPointsCam;
        MSEREvalHulls = MSERHullsCam;
        MSEREvalEllipses = MSEREllipsesCam;
    }
    if(index == 13)
    {
        MSEREvalPoints = MSERPointsVid;
        MSEREvalHulls = MSERHullsVid;
        MSEREvalEllipses = MSEREllipsesVid;
    }
    drawMSEREvalFeatures();
    refreshTblMSEREvalPoints(MSEREvalHulls);
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    if(index != 9 && index != 12 && index != 13 )
        matdrawn = matbuffg.clone();

    dialmsereval->show();
}

void EAMViewer::openDialOrb()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 24;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();

    if(index == 9)
        ROIdrawn = ROIBuff.clone();
    if(index != 9 && index != 12 && index != 13 )
        matdrawn = matbuffg.clone();

    dialorb->show();
}

void EAMViewer::openDialScharr()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 12;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialscharr->show();
}

void EAMViewer::openDialSobel()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 10;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialsobel->show();
}

void EAMViewer::openDialThreshold()
{
    closeAllDialogs();
    disableTabChanging(index);
    functionFlag = 5;
    if((index == 1)||(index == 2)||(index == 3))
    {
        matbuffg = img2.clone();
        mattempg = img2.clone();
    }
    if((index == 0)||(index == 5)||(index == 6)||(index == 8))
    {
        matbuffc = img5.clone();
        mattempc = img5.clone();
    }
    if(index == 9)
        ROIBuff = ROI.clone();
    dialthresh->show();
}

void EAMViewer::openTMTab()
{
    ui->tabWidget->addTab(ui->tbTemplate,tr("template matching"));
    ui->tabWidget->setCurrentWidget(ui->tbTemplate);
}

void EAMViewer::openVideoTab()
{
    ui->tabWidget->addTab(ui->tbVideo,tr("video"));
    ui->tabWidget->setCurrentWidget(ui->tbVideo);
    index = 13;
}

void EAMViewer::prevVideo()
{
    if(timerVideo->isActive())
        startStopGrabbingAndShowingVideo();
    ui->tbVideo->setEnabled(false);
    VidNum++;
    if(VidNum == ListVideos.size())
        VidNum = 0; 
    vidDev.release();
    loadVideoSize();
    vidFlag = 1;
    grabAndProcessFrameVideo();
    vidFlag = 0;
    ui->tbVideo->setEnabled(true);
}

void EAMViewer::refreshTblBRISKKeyPointsSlot()
{
    if(index == 12)
        refreshTblBRISKKeyPoints(BRISKKeyPointsCam);
    if(index == 13)
        refreshTblBRISKKeyPoints(BRISKKeyPointsVid);
}

void EAMViewer::refreshTblFASTKeyPointsSlot()
{
    if(index == 12)
        refreshTblFASTKeyPoints(FASTKeyPointsCam);
    if(index == 13)
        refreshTblFASTKeyPoints(FASTKeyPointsVid);
}

void EAMViewer::refreshTblFREAKKeyPointsSlot()
{
    if(index == 12)
        refreshTblFREAKKeyPoints(FREAKKeyPointsCam);
    if(index == 13)
        refreshTblFREAKKeyPoints(FREAKKeyPointsVid);
}

void EAMViewer::refreshTblCornersSlot()
{
    if(index == 12)
        refreshCornersTbldata(cornersCam);
    if(index == 13)
        refreshCornersTbldata(cornersVideo);
}

void EAMViewer::refreshTblHoughLinesSlot()
{
    if(index == 12)
    {
        if(calcHoughLinesPropValue == true)
            refreshHoughLinesPTbldata(calcLinesHoughPCam);
        if(calcHoughLinesPropValue == false)
            refreshHoughLinesTbldata(calcLinesHoughCam);
    }
    if(index == 13)
    {
        if(calcHoughLinesPropValue == true)
            refreshHoughLinesPTbldata(calcLinesHoughPVideo);
        if(calcHoughLinesPropValue == false)
            refreshHoughLinesTbldata(calcLinesHoughVideo);
    }
}

void EAMViewer::refreshTblHoughCirclesSlot()
{
    if(index == 12)
        refreshHoughCirclesTbldata(calcCirclesHoughCam);
    if(index == 13)
        refreshHoughCirclesTbldata(calcCirclesHoughVideo);
}

void EAMViewer::refreshTblMSERPointsSlot()
{
    if(index == 12)
        refreshTblMSERPoints(MSERHullsCam);
    if(index == 13)
        refreshTblMSERPoints(MSERHullsVid);
}

void EAMViewer::refreshTblMSEREvalPointsSlot()
{
    refreshTblMSEREvalPoints(MSEREvalHulls);
}

void EAMViewer::refreshTblORBSlot()
{
    if(index == 12)
        refreshTblORBKeyPoints(ORBKeyPointsCam);
    if(index == 13)
        refreshTblORBKeyPoints(ORBKeyPointsVid);
}

void EAMViewer::removeLastFunctionOfVideoToolchain()
{
    if(index == 12)
        if(processingToolchainIndex.size() > 0)
        {
            if(processingToolchainIndex.at(processingToolchainIndex.size()-1) == 18)
                timerRefreshHoughLinesTbl->stop();
            if(processingToolchainIndex.at(processingToolchainIndex.size()-1) == 19)
                timerRefreshHoughCirclesTbl->stop();
            if(processingToolchainIndex.at(processingToolchainIndex.size()-1) == 20)
                timerRefreshCornersTbl->stop();
            if(processingToolchainIndex.at(processingToolchainIndex.size()-1) == 23)
                timerRefreshMSERTbl->stop();
            if(processingToolchainIndex.at(processingToolchainIndex.size()-1) == 24)
                timerRefreshORBTbl->stop();
            if(processingToolchainIndex.at(processingToolchainIndex.size()-1) == 29)
                timerRefreshFASTTbl->stop();
            if(timerRefreshORBTbl->isActive() == true)
                timerRefreshORBTbl->stop();
            if(timerRefreshBRISKTbl->isActive() == true)
                timerRefreshBRISKTbl->stop();
            if(timerRefreshFREAKTbl->isActive() == true)
                timerRefreshFREAKTbl->stop();
            if(timerRefreshMSEREvalTbl->isActive() == true)
                timerRefreshMSEREvalTbl->stop();

            processingToolchainIndex.pop_back();
            removeLastLineFromVideoTextEdit();
        }
    if(index == 13)
        if(processingVideoToolchainIndex.size() > 0)
        {
            if(processingVideoToolchainIndex.at(processingVideoToolchainIndex.size()-1) == 18)
                timerRefreshHoughLinesTblVideo->stop();
            if(processingVideoToolchainIndex.at(processingVideoToolchainIndex.size()-1) == 19)
                timerRefreshHoughCirclesTblVideo->stop();
            if(processingVideoToolchainIndex.at(processingVideoToolchainIndex.size()-1) == 20)
                timerRefreshCornersTblVideo->stop();
            if(processingVideoToolchainIndex.at(processingVideoToolchainIndex.size()-1) == 23)
                timerRefreshMSERTblVideo->stop();
            if(processingVideoToolchainIndex.at(processingVideoToolchainIndex.size()-1) == 24)
                timerRefreshORBTblVideo->stop();
            if(processingVideoToolchainIndex.at(processingVideoToolchainIndex.size()-1) == 29)
                timerRefreshFASTTblVideo->stop();
            if(timerRefreshORBTblVideo->isActive() == true)
                timerRefreshORBTblVideo->stop();
            if(timerRefreshBRISKTblVideo->isActive() == true)
                timerRefreshBRISKTblVideo->stop();
            if(timerRefreshFREAKTblVideo->isActive() == true)
                timerRefreshFREAKTblVideo->stop();
            if(timerRefreshMSEREvalTblVideo->isActive())
                timerRefreshMSEREvalTblVideo->stop();

            processingVideoToolchainIndex.pop_back();
            removeLastLineFromVideoTextEdit();
        }
}

void EAMViewer::resetData()
{
    newLineInText(tr("   -------------- reset data --------------   "));
    img5 = img0.clone();
    img2 = img1.clone();
    img3 = calculatehistogram(img2);
    img6 = calculatehistogram(img5);

    clearROI();
    loadPixmaps();
}

void EAMViewer::resetImgProcViewAfterCornerFlagChanging()
{
    if(index < 12)
    {
        if(index != 9)
            resetSinglePic(mattempg, 2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
        if(dialcornerdetect->drawFlag == true)
            drawCornerCircles();
    }
}

void EAMViewer::resetImgProcViewAfterProbChanging()
{
    if(index < 12)
    {
        if(index != 9)
            resetSinglePic(mattempg,2);
        if(index == 9)
            resetSinglePic(ROI,ROIIMG);
        if(dialhoughlines->drawFlag == true)
            drawHoughLines();
        if(dialhoughlines->prob == true)
            refreshHoughLinesPTbldata(linesHoughP);
        if(dialhoughlines->prob == false)
            refreshHoughLinesTbldata(linesHough);
    }
}

void EAMViewer::save()
{
    QString qstrc = tr("color/processedcolor_") + List.at(PicNum).fileName();
    QString qstrg = tr("gray/processedgray_") + List.at(PicNum).fileName();
    imwrite(qstrc.toStdString().data(),img5);
    imwrite(qstrg.toStdString().data(),img2);
}

void EAMViewer::saveEvaluatedMSERData()
{
    if(index == 9)
    {
        MSERPointsROI   = MSEREvalPoints;
        MSERHullsROI    = MSEREvalHulls;
        MSEREllipsesROI = MSEREvalEllipses;
    }
    else if(index < 12)
    {
        MSERPoints      = MSEREvalPoints;
        MSERHulls       = MSEREvalHulls;
        MSEREllipses    = MSEREvalEllipses;
    }
    if(index == 12)
    {
        MSERPointsCam   = MSEREvalPoints;
        MSERHullsCam    = MSEREvalHulls;
        MSEREllipsesCam = MSEREvalEllipses;
    }
    if(index == 13)
    {
        MSERPointsVid   = MSEREvalPoints;
        MSERHullsVid    = MSEREvalHulls;
        MSEREllipsesVid = MSEREvalEllipses;
    }
}

void EAMViewer::saveDBToFile()
{

}

void EAMViewer::saveROItoDb()
{
    if(!ui->leROIName->text().isEmpty())
    {
            dbStructCurrentROI.RoiImg = ROI.clone();
            dbStructCurrentROI.linesHough = calcLinesHoughROI;
            dbStructCurrentROI.linesHoughP = calcLinesHoughPROI;
            dbStructCurrentROI.circlesHough = calcCirclesHoughROI;
            dbStructCurrentROI.corners = cornersROI;
            dbStructCurrentROI.MSERPoints = MSERPointsROI;
            dbStructCurrentROI.FASTKeyPoints = FASTKeyPointsROI;
            dbStructCurrentROI.BRISKKeyPoints = BRISKKeyPointsROI;
            dbStructCurrentROI.BRISKDescriptors = BRISKDescriptorsROI;
            dbStructCurrentROI.ORBKeyPoints = ORBKeyPointsROI;
            dbStructCurrentROI.ORBDescriptors = ORBDescriptorsROI;
            dbStructCurrentROI.FREAKKeyPoints = FREAKKeyPointsROI;
            dbStructCurrentROI.FREAKDescriptors = FREAKDescriptorsROI;

            dbStructCurrentROI.name = ui->leROIName->text();
            ROIDBItems.append(dbStructCurrentROI);
            FormROIDataBase *FRDB = new FormROIDataBase( this,dbStructCurrentROI);
            //(ROIDBWidgetItems.append(FormROIDataBase( this,dbStructCurrentROI));
            int nList = ROIDBWidgetItems.size();
            QRect rec = FRDB->geometry();
            FRDB->setMinimumHeight(rec.height()*1.5);
            FRDB->setMaximumHeight(rec.height()*1.5);
            FRDB->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);

            connect(FRDB,SIGNAL(doubleClicked()),QSMROIDBEvent,SLOT(map()));
            QSMROIDBEvent->setMapping(FRDB,nList);

            ui->scrollArea->widget()->layout()->addWidget(FRDB);
            ui->tabWidget->addTab(ui->tbROIDataBase,tr("roi database"));
            ROIDBWidgetItems.append(FRDB);
            newLineInText(tr("Saved ") + dbStructCurrentROI.name + tr(" to roi database;"));
    }
    else
        newLineInText(tr("Saved none! Please write a usefull text or fill in some data."));
}

void EAMViewer::selectROI()
{
    RoiEventStruct RES;
    if((index == 1)|(index == 2)|(index == 3))
    {
        matbuffg = img2.clone();
        RES.img = matbuffg.clone();
        RES.imgDraw = matbuffg.clone();
    }
    if((index == 0)|(index == 5)|(index == 6)|(index == 8)|(index == 9)|(index == 10)|(index == 11)|(index == 12)|(index == 13))
    {
        matbuffc = img5.clone();
        RES.img = matbuffc.clone();
        RES.img.convertTo(RES.img, CV_8UC3);
        RES.imgDraw = matbuffc.clone();
    }

    RES.rec = Rect();
    RES.rec.x = 0;
    RES.rec.y = 0;
    RES.rec.width = 0;
    RES.rec.height = 0;
    RES.draw = false;

    RES.drawnFlag = false;
    RES.foreGroundFlag = false;
    RES.backGroundFlag = false;
    RES.initGCwithRect = false;
    namedWindow("select ROI",WINDOW_NORMAL);
    imshow("select ROI",RES.img);
    setMouseCallback("select ROI",mouseEvent,static_cast<void*>(&RES));
    int key = 0;

    while(key != 10)
        key = waitKey(0);

    if(RES.rec.height != 0 || RES.rec.width != 0)
    {
        destroyWindow("select ROI");
        Mat imghelp = RES.img(RES.rec).clone();
        RES.imgDraw = imghelp.clone();
        RES.roi = imghelp.clone();

        namedWindow("get the foreground in ROI",WINDOW_NORMAL);

        imshow("get the foreground in ROI",RES.imgDraw);
        RES.drawnFlag = true;

        setMouseCallback("get the foreground in ROI",mouseEvent,static_cast<void*>(&RES));

        key = waitKey();
        while(key != 10)
            key = waitKey(0);

        destroyWindow("get the foreground in ROI");
                
        ROI = RES.roi.clone();
        if((index == 0)|(index == 5)|(index == 6)|(index == 8)|(index == 9)|(index == 10)|(index == 11)|(index == 12)|(index == 13))
           ROI.convertTo(ROI,mattempg.type());
        ROIBuff = ROI.clone();
        ROIHist = calculatehistogram(ROI);

        pmROI[0] = QPixmap::fromImage(matToQImage(ROI));
        pmROI[1] = QPixmap::fromImage(matToQImage(ROIHist));

        sceneROI->clear();
        sceneROIHist->clear();

        sceneROI->addPixmap(pmROI[0]);
        sceneROIHist->addPixmap(pmROI[1]);

        ui->tabWidget->addTab(ui->tbCurrentROI,tr("current roi"));
        ui->tabWidget->setCurrentWidget(ui->tbCurrentROI);
    }
}

void EAMViewer::selectROIFromDB(int i)
{
    dbStructCurrentROI  = ROIDBItems.at(i);
    calcLinesHoughROI   = dbStructCurrentROI.linesHough;
    calcLinesHoughPROI  = dbStructCurrentROI.linesHoughP;
    calcCirclesHoughROI = dbStructCurrentROI.circlesHough;
    cornersROI          = dbStructCurrentROI.corners;
    FASTKeyPointsROI    = dbStructCurrentROI.FASTKeyPoints;
    BRISKKeyPointsROI    = dbStructCurrentROI.BRISKKeyPoints;
    BRISKDescriptorsROI   = dbStructCurrentROI.BRISKDescriptors;
    ORBKeyPointsROI    = dbStructCurrentROI.ORBKeyPoints;
    ORBDescriptorsROI = dbStructCurrentROI.ORBDescriptors;
    FREAKKeyPointsROI    = dbStructCurrentROI.FREAKKeyPoints;
    FREAKDescriptorsROI = dbStructCurrentROI.FREAKDescriptors;

    ROI = dbStructCurrentROI.RoiImg.clone();
    ROIBuff = ROI.clone();
    ROI = ROIBuff.clone();
    ROIBuff = ROI.clone();
    ROIHist = calculatehistogram(ROI);

    pmROI[0] = QPixmap::fromImage(matToQImage(ROI));
    pmROI[1] = QPixmap::fromImage(matToQImage(ROIHist));

    for(h = 0; h < 6; h++)
        ROItoDBFlag[h] = 1;
    sceneROI->clear();
    sceneROIHist->clear();

    sceneROI->addPixmap(pmROI[0]);
    sceneROIHist->addPixmap(pmROI[1]);

    newLineInText(tr("Loaded ") + dbStructCurrentROI.name + tr(" from database."));
    ui->tabWidget->addTab(ui->tbCurrentROI,tr("current roi"));
    ui->tabWidget->setCurrentWidget(ui->tbCurrentROI);
}

void EAMViewer::sliderPressedStart()
{
    if(timerVideo->isActive())
        startStopGrabbingAndShowingVideo();
    sliderVidFlag = 1;
}

void EAMViewer::sliderPressedStop()
{
    if(sliderVidFlag == 1)
    {
        if(timerVideo->isActive())
            startStopGrabbingAndShowingVideo();
        sliderCurrentFramePosChanged();
        sliderVidFlag = 0;
    }
}

void EAMViewer::sliderCurrentFramePosChanged(bool changingFlag)
{
    if(changingFlag == false)
        ui->sliderCurrentFramePos->setValue(currentVideoFrame);
    else if(changingFlag == true)
    {
        currentVideoFrame = ui->sliderCurrentFramePos->value();
        vidDev.set(CV_CAP_PROP_POS_FRAMES, currentVideoFrame );
        vidFlag = 1;
        grabAndProcessFrameVideo();
        vidFlag = 0;
    }
}

void EAMViewer::startStopGrabbingAndShowingCamera()
{
    if(timer->isActive() == true)
    {
        timer->stop();        
        ui->pbRecord->setDisabled(true);
        if(timerRefreshHoughLinesTbl->isActive() == true)
            timerRefreshHoughLinesTbl->stop();
        if(timerRefreshHoughCirclesTbl->isActive() == true)
            timerRefreshHoughCirclesTbl->stop();
        if(timerRefreshCornersTbl->isActive() == true)
               timerRefreshCornersTbl->stop();
        if(timerRefreshMSERTbl->isActive() == true)
            timerRefreshMSERTbl->stop();
        if(timerRefreshFASTTbl->isActive() == true) 
            timerRefreshFASTTbl->stop();
        if(timerRefreshORBTbl->isActive() == true)
            timerRefreshORBTbl->stop();
        if(timerRefreshBRISKTbl->isActive() == true)
            timerRefreshBRISKTbl->stop();
        if(timerRefreshFREAKTbl->isActive() == true)
            timerRefreshFREAKTbl->stop();
        if(timerRefreshMSEREvalTbl->isActive() == true)
            timerRefreshMSEREvalTbl->stop();
        ui->pbPlay->setText(tr(">"));
    }
    else if(timer->isActive() == false)
    {
        ui->pbRecord->setEnabled(true);
        timer->start(int(1000/framesPS));
        for(unsigned int h = 0; h < processingToolchainIndex.size(); h++)
        {
            if(processingToolchainIndex[h] == 18)
                timerRefreshHoughLinesTblVideo->start(1000);
            if(processingToolchainIndex[h] == 19)
                timerRefreshHoughCirclesTbl->start(1000);
            if(processingToolchainIndex[h] == 20)
                timerRefreshCornersTbl->start(1000);
            if(processingToolchainIndex[h] == 23)
                timerRefreshFASTTbl->start(1000);
            if(processingToolchainIndex[h] == 24)
                timerRefreshORBTbl->start(1000);
            if(processingToolchainIndex[h] == 25)
                timerRefreshBRISKTbl->start(1000);
            if(processingToolchainIndex[h] == 26)
                timerRefreshFREAKTbl->start(1000);
            if(processingToolchainIndex[h] == 29)
                timerRefreshMSERTbl->start(1000);
        }
        ui->pbPlay->setText(tr("II"));
    }
}

void EAMViewer::startStopGrabbingAndShowingVideo()
{
    if(timerVideo->isActive() == true)
    {
        timerVideo->stop();
        if(timerRefreshHoughLinesTblVideo->isActive() == true)
            timerRefreshHoughLinesTblVideo->stop();
        if(timerRefreshHoughCirclesTblVideo->isActive() == true)
            timerRefreshHoughCirclesTblVideo->stop();
        if(timerRefreshCornersTblVideo->isActive() == true)
            timerRefreshCornersTblVideo->stop();
        if(timerRefreshMSERTblVideo->isActive() == true)
            timerRefreshMSERTblVideo->stop();
        if(timerRefreshFASTTblVideo->isActive() == true) 
            timerRefreshFASTTblVideo->stop();
        if(timerRefreshORBTblVideo->isActive() == true)
            timerRefreshORBTblVideo->stop();
        if(timerRefreshBRISKTblVideo->isActive() == true)
            timerRefreshBRISKTblVideo->stop();
        if(timerRefreshFREAKTblVideo->isActive() == true)
            timerRefreshFREAKTblVideo->stop();
        if(timerRefreshMSEREvalTblVideo->isActive())
            timerRefreshMSEREvalTblVideo->stop();
        
        ui->pbPlayVid->setText(tr(">"));
    }
    else if(timerVideo->isActive() == false)
    {
        timerVideo->start(int(1000/framesPSVid));
        for(unsigned int h = 0; h < processingVideoToolchainIndex.size(); h++)
        {
            if(processingVideoToolchainIndex[h] == 18)
                timerRefreshHoughLinesTblVideo->start(1000);
            if(processingVideoToolchainIndex[h] == 19)
                timerRefreshHoughCirclesTbl->start(1000);
            if(processingVideoToolchainIndex[h] == 20)
                timerRefreshCornersTbl->start(1000);
            if(processingVideoToolchainIndex[h] == 23)
                timerRefreshFASTTblVideo->start(1000);
            if(processingVideoToolchainIndex[h] == 24)
                timerRefreshORBTblVideo->start(1000);
            if(processingVideoToolchainIndex[h] == 25)
                timerRefreshBRISKTblVideo->start(1000);
            if(processingVideoToolchainIndex[h] == 26)
                timerRefreshFREAKTblVideo->start(1000);
            if(processingVideoToolchainIndex[h] == 29)
                timerRefreshMSERTblVideo->start(1000);
            if(processingVideoToolchainIndex[h] == 30)
                timerRefreshMSEREvalTblVideo->start(1000);
        }
        ui->pbPlayVid->setText(tr("II"));
    }
}

void EAMViewer::startStopRecordingMovieCamera()
{
    if(timer->isActive() == true)
    {

        recordFlagCam = !recordFlagCam;
        if(recordFlagCam == true)
        {
            writingVidSize = 0;
            QString hstr1, hstr2, hstr3, hstr4, hstr5, hstr6;
            QDate date = QDate::currentDate();
            QTime time = QTime::currentTime();

            videoSaveName = tr("/home/peter/DA/videos/IMG-")
                    + hstr1.setNum(date.year()) + tr("-")
                    + hstr2.setNum(date.month()) + tr("-")
                    + hstr3.setNum(date.day()) + tr("-")
                    + hstr4.setNum(time.hour()) + tr("-")
                    + hstr5.setNum(time.minute()) + tr("-")
                    + hstr6.setNum(time.second()) + tr(".avi");
            const string vsm = videoSaveName.toStdString().data();
            VW.open(vsm, CV_FOURCC('D','I','V','X'), framesPS, camImg.size(),!(camImg.channels() == 1));
            ListVideos.push_back(tr(vsm.data()));
            ui->pbRecord->setText(tr("stop record"));
        }
        if(recordFlagCam == false)
        {
            if(writingVidSize < 50)
            {
                newLineInText("to small, minimum 50 frames! ");
                return;
            }
            VW.release();
            ui->pbRecord->setText(tr("record"));
        }
    }
}

void EAMViewer::startStopRecordingMovieVideo()
{
    if(timer->isActive() == true)
    {
        recordFlagVid = !recordFlagVid;
        if(recordFlagVid == true)
        {
            if(recordFlagCam == true)
                startStopRecordingMovieCamera();

            string str = videoSaveName.toStdString();
            int p = str.find(".");
            QString hstr= tr(str.substr(0,p).data());


            videoSaveName = hstr + tr("processed.avi");
            const string vsm = videoSaveName.toStdString().data();
            VW.open(vsm, CV_FOURCC('D','I','V','X'), framesPS, camImg.size(),!(camImg.channels() == 1));

            ui->pbRecord->setText(tr("stop record"));
        }
        if(recordFlagVid == false)
        {
            VW.release();
            ui->pbRecord->setText(tr("record"));
        }
    }
}

void EAMViewer::TMROI()
{    
    functionFlag = 21;
    if(ROIDBItems.size() > 0)
    {
        vector<int>chosenDbIndex;
        for(h = 0; h < ROIDBItems.size(); h++)
            if(ROIDBWidgetItems.at(h)->checkedChooseBox == true)
                chosenDbIndex.push_back(h);
        if(index >= 12)
            if(chosenDbIndex.size() != 1)
            {
                newLineInText(tr("For the video-mode you actually are able to choose just one ROI. "));
                return;
            }
        if(chosenDbIndex.size() == 0)
        {
            newLineInText(tr("There are no rois chosen in database."));
            return;
        }
        else
        {
            QString hstr;
            if(ui->cBxMode->currentIndex() == 0)
                hstr = tr("templatematching(sq_diff);");
            if(ui->cBxMode->currentIndex() == 1)
                hstr = tr("templatematching(sq_diff_normed);");
            if(ui->cBxMode->currentIndex() == 2)
                hstr = tr("templatematching(ccorr);");
            if(ui->cBxMode->currentIndex() == 3)
                hstr = tr("templatematching(ccorr_normed);");
            if(ui->cBxMode->currentIndex() == 4)
                hstr = tr("templatematching(ccoeff);");
            if(ui->cBxMode->currentIndex() == 5)
                hstr = tr("templatematching(ccoeff_normed);");


            if(index < 12)
            {
                clearTMData();
                for( unsigned int u = 0; u < chosenDbIndex.size(); u++)
                {
                    Mat RoiImg = ROIDBItems.at(chosenDbIndex.at(u)).RoiImg;
                    Mat result;
                    if(RoiImg.channels() == 1)
                        result  = templatematching(img2,RoiImg,ui->cBxMode->currentIndex());
                    if(RoiImg.channels() == 3)
                        result  = templatematching(img5,RoiImg,ui->cBxMode->currentIndex());
                    showTMData(result,u);
                    newLineInText(hstr);
                }
            }
            if(index >= 12)
            {

                currentTMMode = ui->cBxMode->currentIndex();
                chosenRoi = chosenDbIndex.at(0);
                validateCurrentFcn(21,hstr);
            }
        }
    }
    else
        newLineInText(tr("There are no rois saved in database."));
}

