#-------------------------------------------------
#
# Project created by QtCreator 2012-02-02T11:47:33
#
#-------------------------------------------------

include(../../path.build)
include(../report.build)

TARGET = FeederDataRpt
TEMPLATE = lib

DEFINES += FEEDERDATARPT_LIBRARY

SOURCES += FeederDataRpt.cpp

HEADERS += FeederDataRpt.h\
        FeederDataRpt_global.h

LIBS += $$PRJPATH/lib/libpgredrv.a \
		$$PRJPATH/lib/libreportengine.a

FORMS += \
    FeederDataForm.ui

RESOURCES += \
    resources.qrc


