#-------------------------------------------------
#
# Project created by QtCreator 2011-11-28T10:06:10
#
#-------------------------------------------------

include(../path.build)


QT       += core network

QT       -= gui

TARGET = updater_srv
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    TcpListener.cpp \
    Md5Checker.cpp \
    TcpConnection.cpp

HEADERS += \
    TcpListener.h \
    Md5Checker.h \
    TcpConnection.h






