#-------------------------------------------------
#
# Project created by QtCreator 2011-10-04T14:59:54
#
#-------------------------------------------------

include(../path.build)

QT       += core

QT       -= gui

TARGET = comtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

OBJECTS_DIR    = tmp
MOC_DIR        = tmp
UI_DIR         = tmp

SOURCES += main.cpp 

message($$PWD/qextserialportd1.dll)

CONFIG(debug, debug|release) {
	LIBS  += $$PWD/qextserialportd1.dll
} 
ELSE {
	LIBS  += $$PWD/qextserialport1.dll
}

#win32 {
#	QMAKE_PRE_LINK=copy /Y $$PRJPATH/lib/qextserialportd1.dll $$DESTDIR/qextserialportd1.dll
#}

#message(copy /Y $$PRJPATH/lib/qextserialportd1.dll $$DSTPATH/qextserialportd1.dll)
