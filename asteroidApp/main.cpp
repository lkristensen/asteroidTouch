#include "bledevices.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQml>
#include <QQmlContext>
#include <QFile>

#include "servicecontrol.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ServiceControl>("AsteroidTouch", 1, 0, "ServiceController");
    qmlRegisterType<BLEDevices>("AsteroidTouch", 1, 0, "BLEDevices");
//    qmlRegisterType<BLEDevices>("AsteroidTouch", 1, 0, "BLEDevices");
//    BLEDevices devices;
//    devices.addDevice(new BLEDevice("Demo 1", "00:11:22:33:44:55"));
//    devices.addDevice(new BLEDevice("Demo 2", "01:11:21:31:41:51"));
//    devices.addDevice(new BLEDevice("Demo 3", "11:11:11:11:11:11"));


    QQuickView view;
    view.engine()->rootContext()->setContextProperty("version", QStringLiteral(VERSION));
    view.engine()->rootContext()->setContextProperty("homePath", QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first());
//    view.engine()->rootContext()->setContextProperty("BLEDevices", &devices);
    view.setSource(QUrl(QStringLiteral("qrc:///Main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();


    return app.exec();
}

