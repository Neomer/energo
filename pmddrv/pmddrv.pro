#-------------------------------------------------
#
# Project created by QtCreator 2012-02-15T13:28:38
#
#-------------------------------------------------

include(../path.build)

QT       = core sql


TARGET = pmddrv
TEMPLATE = lib

DEFINES += PMDDRV_LIBRARY

SOURCES += PmdDrv.cpp

HEADERS += PmdDrv.h\
        pmddrv_global.h
