#-------------------------------------------------
#
# Project created by QtCreator 2011-10-27T15:37:40
#
#-------------------------------------------------

include(../../path.build)

include(../report.build)

QT *= xml gui

TARGET = DataViewRpt
TEMPLATE = lib

DEFINES += DATAVIEWRPT_LIBRARY

SOURCES += DataViewRpt.cpp \
    #../ReportQuery.cpp

HEADERS += DataViewRpt.h\
        DataViewRpt_global.h \

LIBS +=  -L$$BUILD_PATH -lpgredrv \
         -L$$BUILD_PATH -lreportengine


FORMS += \
    DataViewForm.ui

RESOURCES += \
    resources.qrc













