#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T19:30:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameTimer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamelist.cpp \
    inputtimedialog.cpp \
    timedisplayer.cpp \
    gamerunner.cpp \
    datasaver.cpp \
    savingdata.cpp

HEADERS  += mainwindow.h \
    gamelist.h \
    inputtimedialog.h \
    timedisplayer.h \
    gamerunner.h \
    datasaver.h \
    savingdata.h

FORMS    += mainwindow.ui \
    inputtimedialog.ui

CONFIG += c++11

RESOURCES += \
    imageresource.qrc
