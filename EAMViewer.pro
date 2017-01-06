#-------------------------------------------------
#
# Project created by QtCreator 2012-12-26T12:07:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EAMViewer
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

LD_LIBRARY_PATH="/usr/local/lib";

SOURCES += main.cpp\
    dialogthresholding.cpp \
    dialogadaptivethreshold.cpp \
    dialogblur.cpp \
    dialogmedianblur.cpp \
    dialoggaussian.cpp \
    dialogsobel.cpp \
    dialogdilation.cpp \
    dialogerode.cpp \
    dialogmorphologyex.cpp \
    dialogcustomfilter.cpp \
    dialoglaplacian.cpp \
    dialogscharr.cpp \
    dialogcanny.cpp \
    eventsqgraphicsview.cpp \
    eventsqlabel.cpp \
    dialoghoughlines.cpp \
    dialoghoughcircles.cpp \
    dialogcornerdetection.cpp \
    eamviewer.cpp \
    dialoglineartransformation.cpp \
    dialoggammatransformation.cpp \
    formroidatabase.cpp \
    dialogmser.cpp \
    dialogfast.cpp \
    dialogbgsubstraction.cpp \
    dialogorb.cpp \
    dialogbrisk.cpp \
    dialogfreak.cpp \
    dialogevalmser.cpp

HEADERS  += \
    dialogthresholding.h \
    dialogadaptivethreshold.h \
    dialogblur.h \
    dialogmedianblur.h \
    dialoggaussian.h \
    dialogsobel.h \
    dialogdilation.h \
    dialogerode.h \
    dialogmorphologyex.h \
    dialogcustomfilter.h \
    dialoglaplacian.h \
    dialogscharr.h \
    dialogcanny.h \
    eventsqgraphicsview.h \
    eventsqlabel.h \
    dialoghoughlines.h \
    dialoghoughcircles.h \
    dialogcornerdetection.h \
    eamviewer.h \
    dialoglineartransformation.h \
    dialoggammatransformation.h \
    formroidatabase.h \
    dialogmser.h \
    dialogfast.h \
    dialogbgsubstraction.h \
    dialogorb.h \
    dialogbrisk.h \
    dialogfreak.h \
    dialogevalmser.h \
    NaturalMergeSorter.h

FORMS    +=\
    dialogthresholding.ui \
    dialogadaptivethreshold.ui \
    dialogblur.ui \
    dialogmedianblur.ui \
    dialoggaussian.ui \
    dialogsobel.ui \
    dialogdilation.ui \
    dialogerode.ui \
    dialogmorphologyex.ui \
    dialogcustomfilter.ui \
    dialoglaplacian.ui \
    dialogscharr.ui \
    dialogcanny.ui \
    dialoghoughlines.ui \
    dialoghoughcircles.ui \
    dialogcornerdetection.ui \
    eamviewer.ui \
    dialoglineartransformation.ui \
    dialoggammatransformation.ui \
    formroidatabase.ui \
    dialogmser.ui \
    dialogfast.ui \
    dialogbgsubstraction.ui \
    dialogorb.ui \
    dialogbrisk.ui \
    dialogfreak.ui \
    dialogevalmser.ui


LIBS += `pkg-config opencv --cflags --libs`
