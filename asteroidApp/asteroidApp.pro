TEMPLATE = app
TARGET = asteroidApp

include(../version.pri)
load(ubuntu-click)

QT += qml quick dbus

CONFIG += c++11

SOURCES += main.cpp \
    servicecontrol.cpp \
    bledevices.cpp

RESOURCES += asteroidApp.qrc

QML_FILES += $$files(*.qml, true) \
             $$files(*.js, true)

CONF_FILES += asteroidTouch.apparmor \
              asteroidTouch.desktop \
              icon.png

OTHER_FILES += $${CONF_FILES} \
               $${QML_FILES}

config_files.path = /asteroidApp
config_files.files += $${CONF_FILES}
INSTALLS += config_files

desktop_file.path = /asteroidApp
desktop_file.files = $$OUT_PWD/asteroidTouch.desktop
desktop_file.CONFIG += no_check_exist
INSTALLS += desktop_file

target.path = $${UBUNTU_CLICK_BINARY_PATH}
INSTALLS += target

HEADERS += \
    servicecontrol.h \
    bledevices.h
