include(../path.build)

QT       += core gui

TARGET = report
TEMPLATE = app

UI_HEADERS_DIR = $$PRJPATH/$$TARGET
UI_SOURCES_DIR = $$PRJPATH/$$TARGET
UI_DIR = $$PRJPATH/$$TARGET

SOURCES += \
	main.cpp\
	mainwindow.cpp \
	loginform.cpp \ 
    MdiWindow.cpp \
    reportplugin.cpp

HEADERS  += \
	mainwindow.h \
    dbconf.h \
    loginform.h \
    struct_desc.h \ 
    MdiWindow.h \
    reportplugin.h

FORMS    += \
	mainwindow.ui \
    loginform.ui 

LIBS += -L$$BUILD_PATH -lpgredrv \
        -L$$BUILD_PATH -lreportengine
		

RESOURCES += \
    resources.qrc

OTHER_FILES += \
	conf.rc

RC_FILE = conf.rc





