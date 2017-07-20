#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQml>
#include <QFile>

#include "servicecontrol.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ServiceControl>("AsteroidTouch", 1, 0, "ServiceController");

    QQuickView view;
    view.engine()->rootContext()->setContextProperty("version", QStringLiteral(VERSION));
    view.engine()->rootContext()->setContextProperty("homePath", QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first());
    view.setSource(QUrl(QStringLiteral("qrc:///Main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}

