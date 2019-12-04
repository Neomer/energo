#-------------------------------------------------
#
# Project created by QtCreator 2012-01-26T11:47:37
#
#-------------------------------------------------

include(../path.build)

QT       -= gui

TARGET = $$qtLibraryTarget(acdrv)
TEMPLATE = lib

DEFINES += ACDRV_LIBRARY

SOURCES += ACdrv.cpp

HEADERS += ACdrv.h\
        acdrv_global.h

LIBS  += $$PRJPATH/lib/liboradrv.a


