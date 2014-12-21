#-------------------------------------------------
#
# Project created by QtCreator 2014-11-24T07:47:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

subdirs += qtftp

unix:!macx: LIBS += -lcantcoap -lQt5Ftp



QMAKE_CFLAGS += -std=c99

TARGET = CellarClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networkparamdialog.cpp \
    filehandler.cpp \
    realtimedatadialog.cpp \
    nethelper.c \
    connectwrapper.cpp \
    thresholdcrossingretriervers.cpp \
    ftpclient.cpp \
    infofiletodownload.cpp \
    datasensorparser.cpp \
    measure.cpp \
    graphicdatadialog.cpp \
    labelgraphicitem.cpp \
    graphicitem.cpp

HEADERS  += mainwindow.h \
    networkparamdialog.h \
    filehandler.h \
    realtimedatadialog.h \
    connectwrapper.h \
    thresholdcrossingretriervers.h \
    ftpclient.h \
    infofiletodownload.h \
    datasensorparser.h \
    measure.h \
    graphicdatadialog.h \
    labelgraphicitem.h \
    graphicitem.h

FORMS    += mainwindow.ui \
    networkparamdialog.ui \
    realtimedatadialog.ui \
    graphicdatadialog.ui
