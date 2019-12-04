#-------------------------------------------------
#
# Project created by QtCreator 2011-12-12T15:18:44
#
#-------------------------------------------------

include(../../path.build)
include(../report.build)

TARGET = OperView
TEMPLATE = lib

DEFINES += OPERVIEW_LIBRARY

SOURCES += OperView.cpp

HEADERS += OperView.h\
        OperView_global.h

LIBS += $$PRJPATH/lib/libpgredrv.a \
		$$PRJPATH/lib/libreportengine.a


FORMS += \
    OperViewWidget.ui

RESOURCES += \
    resources.qrc

