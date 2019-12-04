#-------------------------------------------------
#
# Project created by QtCreator 2012-03-01T10:39:27
#
#-------------------------------------------------
include(../path.build)

QT       += core gui network xml

TARGET = xmlimport
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    EMailMessage.cpp \
    XML80020.cpp \
    FileChecker.cpp

HEADERS  += MainWindow.h \
    EMailMessage.h \
    XML80020.h \
    FileChecker.h

FORMS    += \
    XmlImportMW.ui


LIBS +=  \
		$$PRJPATH/lib/libpgredrv.a

RESOURCES += \
    resources.qrc

OTHER_FILES += \
	conf.rc

RC_FILE = conf.rc

