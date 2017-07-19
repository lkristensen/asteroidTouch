TEMPLATE=subdirs

load(ubuntu-click)

SUBDIRS += asteroidD asteroidApp

UBUNTU_MANIFEST_FILE=manifest.json.in

UBUNTU_TRANSLATION_DOMAIN="asteroidtouch.lkristensen"

UBUNTU_TRANSLATION_SOURCES += \
    $$files(*.qml, true) \
    $$files(*.js, true) \
    $$files(*.desktop, true)

UBUNTU_PO_FILES+=$$files(po/*.po)

