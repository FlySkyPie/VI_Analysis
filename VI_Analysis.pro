#-------------------------------------------------
#
# Project created by QtCreator 2018-05-18T15:23:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VI_Analysis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataanalyzer.cpp \
    linechart2d.cpp \
    linechart3d.cpp

HEADERS  += mainwindow.h \
    dataanalyzer.h \
    linechart2d.h \
    linechart3d.h

FORMS    += mainwindow.ui
