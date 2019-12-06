#-------------------------------------------------
#
# Project created by QtCreator 2011-10-02T13:30:55
#
#-------------------------------------------------

include(../path.build)

QT       += core network

QT       -= gui

TARGET = recv
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    connection.cpp \ 

HEADERS += connection.h \ 
		../includes/Alerts.h

LIBS += -L$$BUILD_PATH -lpgredrv

CONFIG(debug, debug|release) {
        LIBS  += -L$$BUILD_PATH -lqextserialportd1
}
CONFIG(release, debug|release) {
        LIBS  += -L$$BUILD_PATH -lqextserialport1
}
		
DEFINES += ENERGO_NO_DEBUG






