#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T12:35:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jsonviewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    jsonwidget.cpp

HEADERS  += mainwindow.h \
    jsonwidget.h

FORMS    += mainwindow.ui
