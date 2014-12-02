#-------------------------------------------------
#
# Project created by QtCreator 2014-11-24T07:47:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


unix:!macx: LIBS += -lcantcoap



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
    temperaturegraphicdialog.cpp \
    xvaluesretriervers.cpp

HEADERS  += mainwindow.h \
    networkparamdialog.h \
    filehandler.h \
    realtimedatadialog.h \
    connectwrapper.h \
    temperaturegraphicdialog.h \
    xvaluesretriervers.h

FORMS    += mainwindow.ui \
    networkparamdialog.ui \
    realtimedatadialog.ui \
    temperaturegraphicdialog.ui
