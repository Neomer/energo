#-------------------------------------------------
#
# Project created by QtCreator 2012-02-14T14:52:58
#
#-------------------------------------------------

include(../path.build)

QT       += core network

QT       -= gui

TARGET = datasrv
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    TcpListener.cpp \
    TcpConnectionProc.cpp \
    TcpPackage.cpp

LIBS += $$PRJPATH/lib/libpgredrv.a

HEADERS += \
    default_settings.h \
    TcpListener.h \
    TcpConnectionProc.h \
    TcpPackage.h







