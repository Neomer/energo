#-------------------------------------------------
#
# Project created by QtCreator 2011-11-17T17:00:39
#
#-------------------------------------------------

include(../../path.build)
include(../report.build)

OBJECTS_DIR    = ../build/tmp/$$TARGET
MOC_DIR        = ../build/tmp/$$TARGET

UI_HEADERS_DIR = $$PRJPATH/reports/$$TARGET
UI_SOURCES_DIR = $$PRJPATH/reports/$$TARGET
UI_DIR = $$PRJPATH/reports/$$TARGET


CONFIG(debug, debug|release)
{
	DESTDIR = ../../build/debug/reports
	DEFINES -= QT_NO_DEBUG_OUTPUT
}
CONFIG(release, debug|release)
{
        DESTDIR = ../../build/release/reports
	DEFINES *= QT_NO_DEBUG_OUTPUT
}

QT *= gui

TARGET = BalansRpt
TEMPLATE = lib

DEFINES += BALANSRPT_LIBRARY

SOURCES += balansrpt.cpp

HEADERS += balansrpt.h\
        BalansRpt_global.h

LIBS +=  -L$$BUILD_PATH -lpgredrv \
         -L$$BUILD_PATH -lreportengine

FORMS += \
    balansrptform.ui

RESOURCES += \
    resources.qrc






