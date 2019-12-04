#-------------------------------------------------
#
# Project created by QtCreator 2015-11-26T11:03:44
#
#-------------------------------------------------

include(../path.build)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = energo_db
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
LIBS += $$PRJPATH/lib/libpgredrv.a
DEFINES += ENERGO_NO_DEBUG

