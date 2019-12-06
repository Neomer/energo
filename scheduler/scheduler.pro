#-------------------------------------------------
#
# Project created by QtCreator 2011-11-10T16:46:06
#
#-------------------------------------------------

include(../path.build)

QT       += gui core network

TARGET = scheduler

TEMPLATE = app

UI_HEADERS_DIR = $$PRJPATH/scheduler
UI_SOURCES_DIR = $$PRJPATH/scheduler
UI_DIR = $$PRJPATH/scheduler


SOURCES += main.cpp \
    Schedule.cpp \
    ScheduleList.cpp \
    InstanceController.cpp \
    Timer.cpp \
    Listener.cpp \
    MainWindow.cpp

LIBS += -L$$BUILD_PATH -lpgredrv

HEADERS += \
    Schedule.h \
    ScheduleList.h \
    InstanceController.h \
    Timer.h \
    Listener.h \
    MainWindow.h \
    global.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
	conf.rc

RC_FILE = conf.rc

