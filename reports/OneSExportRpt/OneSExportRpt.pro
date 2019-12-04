#-------------------------------------------------
#
# Project created by QtCreator 2015-12-15T11:35:36
#
#-------------------------------------------------

include(../../path.build)
include(../report.build)

TARGET = OneSExportRpt
TEMPLATE = lib

DEFINES += ONESEXPORTRPT_LIBRARY

SOURCES += onesexportrpt.cpp

HEADERS += onesexportrpt.h\
        onesexportrpt_global.h

LIBS += $$PRJPATH/lib/libpgredrv.a \
		$$PRJPATH/lib/libreportengine.a

unix {
    target.path = /usr/lib
    INSTALLS += target
}
