#include "dbusinterface.h"

DBusInterface::DBusInterface(QObject *parent) :
    QObject(parent)
{
    QDBusConnection::sessionBus().registerService("org.asteroidos");
    QDBusConnection::sessionBus().registerObject("/org/asteroidos/Manager", this, QDBusConnection::ExportScriptableSlots);

    qDebug() << "DBus interface has been created";
}

QString DBusInterface::Version()
{
    return QStringLiteral(VERSION);
}
