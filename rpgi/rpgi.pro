TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += main.cpp \
    phasehandler.cpp \
    fight.cpp \
    item.cpp \
    functions.cpp \
    Player.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    phasehandler.hh \
    fight.hh \
    item.hh \
    functions.hh \
    Player.hh

DISTFILES += \
    save_01.txt

