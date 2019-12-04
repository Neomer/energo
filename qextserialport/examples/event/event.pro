######################################################################
# Enumerator
######################################################################


PROJECT = event
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += ../../src
QMAKE_LIBDIR += ../../src/build

OBJECTS_DIR    = tmp
MOC_DIR        = tmp
UI_DIR         = tmp

SOURCES += main.cpp PortListener.cpp
HEADERS += PortListener.h

CONFIG(debug, debug|release):LIBS  += D:/project/Qt/energo/lib/qextserialportd1.dll
else:LIBS  += D:/project/Qt/energo/lib/qextserialport1.dll

