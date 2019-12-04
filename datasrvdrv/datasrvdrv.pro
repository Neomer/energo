#-------------------------------------------------
#
# Project created by QtCreator 2012-02-14T16:11:46
#
#-------------------------------------------------

include(../path.build)

QT       += network
QT       -= gui

TARGET = datasrvdrv
TEMPLATE = lib

DEFINES += DATASRVDRV_LIBRARY

SOURCES += DataSrvDrv.cpp \
	../recv/connection.cpp \
    TcpPackage.cpp

HEADERS += DataSrvDrv.h\
		../recv/connection.h \
        datasrvdrv_global.h \
    TcpPackage.h

#LIBS += $$PRJPATH/lib/libpgredrv.a

CONFIG(debug, debug|release) {
	LIBS  += $$PRJPATH/lib/qextserialportd1.dll
} 
ELSE {
	LIBS  += $$PRJPATH/lib/qextserialport1.dll
}


