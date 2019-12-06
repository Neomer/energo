#-------------------------------------------------
#
# Project created by QtCreator 2011-09-25T14:01:33
#
#-------------------------------------------------

include(../path.build)
include(../pg.build)

QT       += core gui

TARGET = conf
TEMPLATE = app

UI_HEADERS_DIR = $$PRJPATH/conf
UI_SOURCES_DIR = $$PRJPATH/conf
UI_DIR = $$PRJPATH/conf

SOURCES += \
	main.cpp\
	mainwindow.cpp \
	loginform.cpp \
	debugwindow.cpp \
	debugreader.cpp \
    CounterSets.cpp \
    FeederSets.cpp \
    ListPicker.cpp \
    ObjectSets.cpp \
    FactorySets.cpp \
    OrganizationSets.cpp \
    SearchDialog.cpp \
    ChannelsSets.cpp \
    ScheduleSets.cpp \
    ChannelSets.cpp \
    BalansSets.cpp \
    BalansAddSets.cpp \
    BalansSelectElements.cpp \
    DPGSets.cpp \
    DPGAddSets.cpp \
    PointCodes.cpp \
    DPSets.cpp \
    MPSets.cpp \
    MeasuringChannelSelect.cpp \
    MeasuringChannelSets.cpp \
    ScheduleAddSets.cpp \
    ScheduleSelectElements.cpp \
    CounterAddParamSets.cpp \
    UserSets.cpp \
    CHGAddSets.cpp \
    CHGSets.cpp \
    transformerexchange.cpp \
    channelsaddsets.cpp

HEADERS  += \
	mainwindow.h \
    loginform.h \
    struct_desc.h \
    debugwindow.h \
    debugreader.h \
    CounterSets.h \
    FeederSets.h \
    ListPicker.h \
    ObjectSets.h \
    FactorySets.h \
    OrganizationSets.h \
    SearchDialog.h \
    ChannelsSets.h \
    ScheduleSets.h \
    ChannelSets.h \
    BalansSets.h \
    BalansAddSets.h \
    BalansSelectElements.h \
    DPGSets.h \
    DPGAddSets.h \
    PointCodes.h \
    DPSets.h \
    MPSets.h \
    MeasuringChannelSelect.h \
    MeasuringChannelSets.h \
    ScheduleAddSets.h \
    ScheduleSelectElements.h \
    CounterAddParamSets.h \
    UserSets.h \
    CHGAddSets.h \
    CHGSets.h \
    transformerexchange.h \
    channelsaddsets.h

FORMS    += \
	mainwindow.ui \
    loginform.ui \
    debugwindow.ui \
    CounterSets.ui \
    FeederSets.ui \
    ListPicker.ui \
    ObjectSets.ui \
    GTPSets.ui \
    FactorySets.ui \
    OrganizationSets.ui \
    SearchDialog.ui \
    ScheduleSets.ui \
    ChannelSets.ui \
    BalansSets.ui \
    BalansAddSets.ui \
    BalansSelectElements.ui \
    DPGSets.ui \
    DPGAddSets.ui \
    PointCodes.ui \
    DPSets.ui \
    MPSets.ui \
    MeasuringChannelSelect.ui \
    MeasuringChannelSets.ui \
    ScheduleAddSets.ui \
    ScheduleSelectElements.ui \
    CounterAddParamSets.ui \
    UserSets.ui \
    CHGAddSets.ui \
    CHGSets.ui \
    transformerexchange.ui \
    channelssets.ui \
    channelsaddsets.ui

LIBS += -L$$PG_PATH/lib -lpq \
        -L$$BUILD_PATH -lpgredrv

RESOURCES += \
    resources.qrc

OTHER_FILES += \
	conf.rc

RC_FILE = conf.rc
















































