#-------------------------------------------------
#
# Project created by QtCreator 2011-11-28T11:19:44
#
#-------------------------------------------------

include(../path.build)

QT       += core gui network

TARGET = updater
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TcpConnection.cpp \
    Md5Checker.cpp \
    FileReceiver.cpp

HEADERS  += MainWindow.h \
    TcpConnection.h \
    defines.h \
    Md5Checker.h \
    FileReceiver.h

FORMS    += MainWindow.ui

RC_FILE = updater.rc

OTHER_FILES += \
    updater.rc







