#-------------------------------------------------
#
# Project created by QtCreator 2011-10-03T13:02:45
#
#-------------------------------------------------

include(../path.build)

QT       += core

QT       -= gui

TARGET = comport_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
		$$PRJPATH/recv/GSMConnection.cpp

HEADERS += $$PRJPATH/recv/GSMConnection.h


CONFIG(debug, debug|release) {
	LIBS  += $$PRJPATH/lib/qextserialportd1.dll
} 
ELSE {
	LIBS  += $$PRJPATH/lib/qextserialport1.dll
}
		
INCLUDEPATH += $$PRJPATH/includes

