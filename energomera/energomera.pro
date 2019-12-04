#-------------------------------------------------
#
# Project created by QtCreator 2013-06-04T15:51:09
#
#-------------------------------------------------

include(../path.build)


QT		 += network
QT       -= gui

TARGET = energomera
TEMPLATE = lib

DEFINES += ENERGOMERA_LIBRARY

SOURCES += Energomera.cpp \
	../recv/connection.cpp

HEADERS += Energomera.h\
        energomera_global.h \
    ../includes/global.h \
	../includes/CounterInterface.h \
	../recv/connection.h

INSTALLS += plugin

CONFIG(debug, debug|release) {
	LIBS  += $$PRJPATH/lib/qextserialportd1.dll
} 
ELSE {
	LIBS  += $$PRJPATH/lib/qextserialport1.dll
}
