#-------------------------------------------------
#
# Project created by QtCreator 2013-07-23T14:06:37
#
#-------------------------------------------------

include(../../path.build)
include(../report.build)

OBJECTS_DIR    = ../build/tmp/$$TARGET
MOC_DIR        = ../build/tmp/$$TARGET

UI_HEADERS_DIR = $$PRJPATH/reports/$$TARGET
UI_SOURCES_DIR = $$PRJPATH/reports/$$TARGET
UI_DIR = $$PRJPATH/reports/$$TARGET


TARGET = RegisterRpt
TEMPLATE = lib

DEFINES += REGISTERRPT_LIBRARY

SOURCES += RegisterRpt.cpp

HEADERS += RegisterRpt.h\
        registerrpt_global.h

LIBS += $$PRJPATH/lib/libpgredrv.a \
		$$PRJPATH/lib/libreportengine.a

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    RegisterViewForm.ui

RESOURCES += \
    resources.qrc
