#include "dbusinterface.h"

DBusInterface::DBusInterface(QObject *parent) :
    QObject(parent)
{
    QDBusConnection::sessionBus().registerService("org.asteroidos");
    QDBusConnection::sessionBus().registerObject("/org/asteroidos/Manager", this, QDBusConnection::ExportScriptableSlots|QDBusConnection::ExportScriptableSignals);

    m_watchFinder = new AstWatchFinder(this);

    connect(m_watchFinder, &AstWatchFinder::devicesChanged,
            this, &DBusInterface::AstWatchesChanged);
    connect(m_watchFinder, &AstWatchFinder::scanningChanged,
            this, &DBusInterface::ScanningChanged);

    qDebug() << "DBus interface has been created";
}

void DBusInterface::StartSearch()
{
    m_watchFinder->startSearch();
}

QString DBusInterface::Version()
{
    return QStringLiteral(VERSION);
}

QStringList DBusInterface::ListDevices()
{
    QStringList ret;

    foreach(AstWatchInfo *device, m_watchFinder->devices()) {
        ret.append(device->getName());
        ret.append(device->getAddress());
    }

/*    ret.append(QString("Demo Watch 1"));
    ret.append(QString("00:11:22:33:44:55"));
    ret.append(QString("Demo Watch 2"));
    ret.append(QString("01:11:21:31:41:51"));
    ret.append(QString("Demo Watch 3"));
    ret.append(QString("10:20:30:40:50:60"));*/

    return ret;
}
