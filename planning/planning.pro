#-------------------------------------------------
#
# Project created by QtCreator 2012-04-03T12:03:19
#
#-------------------------------------------------

include(../path.build)

QT       += core gui

TARGET = planning
TEMPLATE = app

UI_HEADERS_DIR = $$PRJPATH/planning
UI_SOURCES_DIR = $$PRJPATH/planning
UI_DIR = $$PRJPATH/planning

SOURCES += main.cpp\
        PlanningMW.cpp \
    PlanningLoginForm.cpp \
    DatePicker.cpp

HEADERS  += PlanningMW.h \
    PlanningLoginForm.h \
    DatePicker.h

FORMS    += PlanningMW.ui \
    PlanningLoginForm.ui

LIBS +=  \
		$$PRJPATH/lib/libpgredrv.a


OTHER_FILES += \
	conf.rc

RC_FILE = conf.rc

RESOURCES += \
    resources.qrc

