QT += core dbus bluetooth
QT -= gui

include(../version.pri)
load(ubuntu-click)

TARGET = asteroidD
CONFIG +=c++11

TEMPLATE = app

SOURCES += main.cpp \
    core.cpp \
    dbusinterface.cpp \
    astwatchfinder.cpp \
    astwatchinfo.cpp \
    dbusastwatch.cpp

target.path = $${UBUNTU_CLICK_BINARY_PATH}
INSTALLS += target

QMAKE_POST_LINK = sed -i s/@VERSION@/$$VERSION/g $$OUT_PWD/../manifest.json || exit 0

HEADERS += \
    core.h \
    dbusinterface.h \
    astwatchfinder.h \
    astwatchinfo.h \
    dbusastwatch.h

#DEFINES += "SIMULATE_BLUETOOTH"
