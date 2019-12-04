#-------------------------------------------------
#
# Project created by QtCreator 2012-04-06T09:54:15
#
#-------------------------------------------------

include(../path.build)

QT       += core gui

TARGET = sceditor
TEMPLATE = app

UI_HEADERS_DIR = $$PRJPATH/$$TARGET
UI_SOURCES_DIR = $$PRJPATH/$$TARGET
UI_DIR = $$PRJPATH/$$TARGET

SOURCES += main.cpp\
        SchemeEditorMW.cpp \
    SchemeObject.cpp \
    ObjectTransformer.cpp \
    ObjectDataSource.cpp \
    SchemeObjectSetting.cpp \
    ObjectText.cpp \
    SchemeScene.cpp \
    ObjectRect.cpp \
    ObjectEllipse.cpp \
	ObjectConnectionLine.cpp \
    ObjectLine.cpp \
	#LoadScreen.cpp
    ObjectTriangle.cpp \
    ObjectMeter.cpp

HEADERS  += SchemeEditorMW.h \
    SchemeObject.h \
    ObjectTransformer.h \
    ObjectDataSource.h \
    SchemeObjectSetting.h \
    ObjectText.h \
    SchemeScene.h \
    ObjectRect.h \
    ObjectEllipse.h \
	ObjectConnectionLine.h \
    ObjectLine.h \
	#LoadScreen.h
    ObjectTriangle.h \
    ObjectMeter.h

FORMS    += SchemeEditorMW.ui \
	#LoadScreen.ui

LIBS +=  \
	$$PRJPATH/lib/libpgredrv.a
		

OTHER_FILES += \
	conf.rc

RC_FILE = conf.rc

RESOURCES += \
    resources.qrc
