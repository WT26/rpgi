TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += main.cpp \
    phasehandler.cpp \
    item.cpp \
    functions.cpp \
    Player.cpp \
    Debug.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    phasehandler.hh \
    item.hh \
    functions.hh \
    Player.hh \
    Debug.hh

DISTFILES += \
    save_01.txt

