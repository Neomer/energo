#-------------------------------------------------
#
# Project created by QtCreator 2011-10-26T22:23:12
#
#-------------------------------------------------

include(../../path.build)

include(../report.build)

QT *= xml gui

TARGET = CheckDataRpt
TEMPLATE = lib

DEFINES += CHECKDATARPT_LIBRARY

SOURCES += checkdatarpt.cpp \ 

HEADERS += checkdatarpt.h\
        CheckDataRpt_global.h \

INSTALLS += plugin


LIBS +=  -L$$BUILD_PATH -lpgredrv \
         -L$$BUILD_PATH -lreportengine


RESOURCES += \
    resources.qrc



