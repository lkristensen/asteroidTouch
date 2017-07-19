QT += core
QT -= gui

include(../version.pri)
load(ubuntu-click)

TARGET = asteroidD
CONFIG +=c++11

TEMPLATE = app

SOURCES += main.cpp

target.path = $${UBUNTU_CLICK_BINARY_PATH}
INSTALLS += target

QMAKE_POST_LINK = sed -i s/@VERSION@/$$VERSION/g $$OUT_PWD/../manifest.json || exit 0
