TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += main.cpp \
    phasehandler.cpp \
    item.cpp \
    functions.cpp \
    debug.cpp \
    player.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    phasehandler.hh \
    item.hh \
    functions.hh \
    debug.hh \
    player.hh

DISTFILES += \
    example_savefile.txt \
    save_1.txt

