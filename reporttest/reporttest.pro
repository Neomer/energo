QT       += core gui declarative

TARGET = reporttest
TEMPLATE = app

SOURCES += \
	main.cpp\
	mainwindow.cpp 

HEADERS  += \
	mainwindow.h 

FORMS    += \
	mainwindow.ui 

OTHER_FILES += \
    report.qml \
    reports/checkdatafull.rpt \
    main.js





