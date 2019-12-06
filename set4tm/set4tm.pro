#-------------------------------------------------
#
# Project created by QtCreator 2011-10-03T11:12:19
#
#-------------------------------------------------

include(../path.build)

QT       -= gui
QT		 += network

TARGET = $$qtLibraryTarget(set4tmplugin)

TEMPLATE = lib

INSTALLS += plugin

DEFINES += SET4TM_LIBRARY

SOURCES += Set4tm.cpp \
	../recv/connection.cpp

HEADERS += Set4tm.h\
        set4tm_global.h \
        Set4tmInterface.h \
        global.h \
        ../includes/global.h \
	../includes/CounterInterface.h \
	../recv/connection.h

CONFIG(debug, debug|release) {
        LIBS  += -L$$BUILD_PATH -lqextserialportd1
}
CONFIG(release, debug|release) {
        LIBS  += -L$$BUILD_PATH -lqextserialport1
}




