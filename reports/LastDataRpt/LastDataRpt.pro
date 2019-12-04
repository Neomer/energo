#-------------------------------------------------
#
# Project created by QtCreator 2012-04-17T10:08:44
#
#-------------------------------------------------

include(../../path.build)
include(../report.build)

TARGET = LastDataRpt
TEMPLATE = lib

DEFINES += LASTDATARPT_LIBRARY

SOURCES += LastDataRpt.cpp

HEADERS += LastDataRpt.h\
        LastDataRpt_global.h

LIBS += $$PRJPATH/lib/libpgredrv.a

FORMS += \
    LastDataForm.ui

RESOURCES += \
    resources.qrc
