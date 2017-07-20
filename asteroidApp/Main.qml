import QtQuick 2.4
import Ubuntu.Components 1.3

import AsteroidTouch 1.0

/*!
    \brief MainView with a Label and Button elements.
*/

MainView {
    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "mainView"

    // Note! applicationName needs to match the "name" field of the click manifest
    applicationName: "test.username"

    width: units.gu(100)
    height: units.gu(75)

    ServiceController {
        id: serviceController
        serviceName: "asteroidD"
        Component.onCompleted: {
            if (!serviceController.serviceFileInstalled) {
                print("Service file not installed. Installing now.")
                serviceController.installServiceFile();
            }
            if (!serviceController.serviceRunning) {
                print("Service not running. Starting now.")
                serviceController.startService();
            }
        }
    }

    Page {
        header: PageHeader {
            id: pageHeader
            title: i18n.tr("test")
            StyleHints {
                foregroundColor: UbuntuColors.orange
                backgroundColor: UbuntuColors.porcelain
                dividerColor: UbuntuColors.slate
            }
        }

        Label {
            id: label
            objectName: "label"
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: pageHeader.bottom
                topMargin: units.gu(2)
            }

            text: i18n.tr("Hello..")
        }

        Button {
            objectName: "button"
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: label.bottom
                topMargin: units.gu(2)
            }
            width: parent.width
            text: i18n.tr("Tap me!")
            onClicked: {
                label.text = i18n.tr("..world!")
            }
        }
    }
}
