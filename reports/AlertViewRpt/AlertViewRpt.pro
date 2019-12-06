#-------------------------------------------------
#
# Project created by QtCreator 2012-04-18T13:51:34
#
#-------------------------------------------------

include(../../path.build)
include(../report.build)

OBJECTS_DIR    = ../build/tmp/$$TARGET
MOC_DIR        = ../build/tmp/$$TARGET

UI_HEADERS_DIR = $$PRJPATH/reports/$$TARGET
UI_SOURCES_DIR = $$PRJPATH/reports/$$TARGET
UI_DIR = $$PRJPATH/reports/$$TARGET

TARGET = AlertViewRpt
TEMPLATE = lib

DEFINES += ALERTVIEWRPT_LIBRARY

SOURCES += AlertViewRpt.cpp

HEADERS += AlertViewRpt.h\
        AlertViewRpt_global.h\
		../../includes/Alerts.h

FORMS += \
    AlertViewForm.ui

RESOURCES += \
    resources.qrc

LIBS +=  -L$$BUILD_PATH -lpgredrv \
         -L$$BUILD_PATH -lreportengine
