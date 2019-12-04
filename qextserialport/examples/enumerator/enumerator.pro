######################################################################
# Enumerator
######################################################################


PROJECT = enumerator
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH  += ../../src
QMAKE_LIBDIR += ../../src/build

OBJECTS_DIR    = tmp
MOC_DIR        = tmp
UI_DIR         = tmp

SOURCES += main.cpp

CONFIG(debug, debug|release):LIBS  += D:/project/Qt/energo/lib/qextserialport1.dll
else:LIBS  += D:/project/Qt/energo/lib/qextserialport1.dll
win32:LIBS += -lsetupapi
