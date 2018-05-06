#-------------------------------------------------
#
# Project created by QtCreator 2016-07-27T22:45:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fivego
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cmyview.cpp \
    cfivegoai.cpp

HEADERS  += mainwindow.h \
    cmyview.h \
    cfivegoai.h

FORMS    += mainwindow.ui

CONFIG += c++11
