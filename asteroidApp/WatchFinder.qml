import QtQuick 2.4
import QtQuick.Layouts 1.1
import Ubuntu.Components 1.3

import AsteroidTouch 1.0

Page {
    id: root

    header: PageHeader {
        id: pageHeader
        title: i18n.tr("Select Watch")
        StyleHints {
            foregroundColor: UbuntuColors.orange
            backgroundColor: UbuntuColors.porcelain
            dividerColor: UbuntuColors.slate
        }
    }
    ListView {
        anchors.fill: parent
        anchors.topMargin: root.header.height
        model: devices
        delegate: ListItem {
            Row {
                    Text { text: name + " - " + address }
                }
            onClicked: {
                print("Device name: ", name, ", Address: ", address);
                pageStack.addPageToCurrentColumn(root, Qt.resolvedUrl("Core.qml"), {name: name, address: address})
            }
        }
    }
}
