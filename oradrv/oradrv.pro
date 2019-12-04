#-------------------------------------------------
#
# Project created by QtCreator 2012-01-26T17:23:47
#
#-------------------------------------------------

include(../path.build)

QT = core

TARGET = oradrv
TEMPLATE = lib
CONFIG += lib


DEFINES += QT_NO_DEBUG_OUTPUT

DEFINES += ORADRV_LIBRARY

SOURCES += OraDrv.cpp \
    OraSqlResult.cpp

HEADERS += OraDrv.h\
        oradrv_global.h \
    OraSqlResult.h

LIBS += \
	$$PRJPATH/lib/ocilib/x32/ociliba.lib \
	#$$PRJPATH/lib/ocilib/ocilibw.lib \
	#$$PRJPATH/lib/ocilib/ocilibm.lib


