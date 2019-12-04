#-------------------------------------------------
#
# Project created by QtCreator 2013-07-23T14:46:34
#
#-------------------------------------------------

include(../../path.build)
include(../report.build)

TARGET = ManualInputRpt
TEMPLATE = lib

OBJECTS_DIR    = ../build/tmp/$$TARGET
MOC_DIR        = ../build/tmp/$$TARGET

UI_HEADERS_DIR = $$PRJPATH/reports/$$TARGET
UI_SOURCES_DIR = $$PRJPATH/reports/$$TARGET
UI_DIR = $$PRJPATH/reports/$$TARGET


DEFINES += MANUALINPUTRPT_LIBRARY

SOURCES += ManualInputRpt.cpp

HEADERS += ManualInputRpt.h\
        manualinputrpt_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
LIBS += $$PRJPATH/lib/libpgredrv.a \
		$$PRJPATH/lib/libreportengine.a

FORMS += \
    ManualInputForm.ui

RESOURCES += \
    resources.qrc
