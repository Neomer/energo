#-------------------------------------------------
#
# Project created by QtCreator 2011-12-02T14:56:16
#
#-------------------------------------------------
include(../path.build)


QT       -= gui
QT		 += network

TARGET = merc320
TEMPLATE = lib

DEFINES += MERC320_LIBRARY

SOURCES += Merc320.cpp \
	../recv/connection.cpp

HEADERS += Merc320.h\
        merc320_global.h \
	../recv/connection.h \
	../includes/modbus.h


CONFIG(debug, debug|release) {
	LIBS  += $$PRJPATH/lib/qextserialportd1.dll
} 
ELSE {
	LIBS  += $$PRJPATH/lib/qextserialport1.dll
}


