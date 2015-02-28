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
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../qt-custom-libs/build-qt-custom-libs-Desktop_Qt_5_3_MSVC2013_OpenGL_64bit-Debug/views/json/release/ -ljson
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../qt-custom-libs/build-qt-custom-libs-Desktop_Qt_5_3_MSVC2013_OpenGL_64bit-Debug/views/json/debug/ -ljson
else:unix: LIBS += -L$$PWD/../../../qt-custom-libs/build-qt-custom-libs-Desktop_Qt_5_3_MSVC2013_OpenGL_64bit-Debug/views/json/ -ljson

INCLUDEPATH += $$PWD/../../../qt-custom-libs/qt-custom-libs/views/json
DEPENDPATH += $$PWD/../../../qt-custom-libs/qt-custom-libs/views/json
