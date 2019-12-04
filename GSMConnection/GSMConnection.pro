#-------------------------------------------------
#
# Project created by QtCreator 2011-10-07T11:50:37
#
#-------------------------------------------------

include(../path.build)

QT       -= gui

TARGET = GSMConnection
TEMPLATE = lib
CONFIG += lib

SOURCES += GSMConnection.cpp \
    GSMSender.cpp

HEADERS += GSMConnection.h \
    GSMConnectionInterface.h \
    GSMSender.h


CONFIG(debug, debug|release) {
	LIBS  += $$PRJPATH/lib/qextserialportd1.dll
} 
ELSE {
	LIBS  += $$PRJPATH/lib/qextserialport1.dll
}
		
INCLUDEPATH += $$PRJPATH/includes

CONFIG(debug, debug|release) 
{
	DESTDIR = ../build/debug
	#DEFINES += QT_NO_DEBUG_OUTPUT
} ELSE {
	DESTDIR = ../build/release
	DEFINES += QT_NO_DEBUG_OUTPUT
}

