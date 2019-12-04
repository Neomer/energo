#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T13:12:31
#
#-------------------------------------------------

include(../path.build)

QT       *= gui xml

TARGET = ReportEngine
TEMPLATE = lib

DEFINES += REPORTENGINE_LIBRARY

SOURCES += ReportEngine.cpp \
    ReportSheet.cpp \
    ReportRow.cpp \
    ReportElement.cpp \
    ReportText.cpp \
    ReportTable.cpp \
    ReportTableRow.cpp \
    ReportTableColumn.cpp \
    ReportTableElement.cpp \
    PrintPreviewDlg.cpp \
    ReportWidget.cpp \
    ReportSheetRegion.cpp

HEADERS += ReportEngine.h \
    ReportSheet.h \
    ReportRow.h \
    ReportElement.h \
    ReportText.h \
    ReportTable.h \
    ReportTableRow.h \
    ReportTableColumn.h \
    ReportTableElement.h \
    PrintPreviewDlg.h \
    ReportWidget.h \
    ReportSheetRegion.h

LIBS += $$PRJPATH/lib/libpgredrv.a

FORMS += \
    PrintPreviewDlg.ui





