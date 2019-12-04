#-------------------------------------------------
#
# Project created by QtCreator 2011-11-07T16:30:10
#
#-------------------------------------------------

include(../path.build)

QT = core

TARGET = pgredrv
TEMPLATE = lib
CONFIG += lib

DEFINES += PGRESQLDRV_LIBRARY

SOURCES += PgreSqlDrv.cpp \
    PgreSqlResult.cpp

HEADERS += PgreSqlDrv.h \
    export.h \
    PgreSqlResult.h

LIBS += $$PRJPATH/lib/pgre/libpq.lib
