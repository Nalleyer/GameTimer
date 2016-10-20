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
    datamanager.cpp

HEADERS  += mainwindow.h \
    gamelist.h \
    datamanager.h

FORMS    += mainwindow.ui

CONFIG += c++11
