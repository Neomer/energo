#-------------------------------------------------
#
# Project created by QtCreator 2011-09-24T20:08:46
#
#-------------------------------------------------

include(../path.build)

QT       += core sql

#QT       -= gui

TARGET = pgtest2
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += ../includes/modbus.h

SOURCES += main.cpp

LIBS += $$PRJPATH/lib/libReportEngine.a
