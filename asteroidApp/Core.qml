import QtQuick 2.4
import QtQuick.Layouts 1.1
import Ubuntu.Components 1.3

import AsteroidTouch 1.0

Page {
    id: root

    property var name: null
    property var address: null

    header: PageHeader {
        id: pageHeader
        title: i18n.tr("Menu ") + name
        StyleHints {
            foregroundColor: UbuntuColors.orange
            backgroundColor: UbuntuColors.porcelain
            dividerColor: UbuntuColors.slate
        }
    }
}
