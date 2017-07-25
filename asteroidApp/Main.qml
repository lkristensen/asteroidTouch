import QtQuick 2.4
import QtQuick.Layouts 1.1

import Ubuntu.Components 1.3

import AsteroidTouch 1.0

/*!
    \brief MainView with a Label and Button elements.
*/

MainView {
    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "mainView"

    // Note! applicationName needs to match the "name" field of the click manifest
    applicationName: "asteroidtouch.lkristensen"

    width: units.gu(100)
    height: units.gu(75)

    ServiceController {
        id: serviceController
        serviceName: "asteroidD"
        Component.onCompleted: {
            print("Tester")
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

    BLEDevices {
        id: devices
    }
    AdaptivePageLayout {
        id: pageStack
        anchors.fill: parent
        primaryPageSource: Qt.resolvedUrl("WatchFinder.qml")
    }
}
