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

LIBS += $$PRJPATH/lib/libpgredrv.a

CONFIG(debug, debug|release) {
	LIBS  += $$PRJPATH/lib/qextserialportd1.dll
} 
ELSE {
	LIBS  += $$PRJPATH/lib/qextserialport1.dll
}
		
DEFINES += ENERGO_NO_DEBUG






