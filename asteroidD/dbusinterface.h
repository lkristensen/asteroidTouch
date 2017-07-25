#ifndef DBUSINTERFACE_H
#define DBUSINTERFACE_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusAbstractAdaptor>
#include <QDBusObjectPath>
#include <QDebug>

#include "astwatchfinder.h"

class DBusInterface : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.asteroidos.Manager")

public:
    explicit DBusInterface(QObject *parent = 0);

public slots:
    Q_SCRIPTABLE void StartSearch();
    Q_SCRIPTABLE QString Version();
    Q_SCRIPTABLE QStringList ListDevices();

signals:
    Q_SCRIPTABLE void AstWatchesChanged();
    Q_SCRIPTABLE void DevicesChanged();
    Q_SCRIPTABLE void ScanningChanged();

private:
    AstWatchFinder *m_watchFinder;

};

#endif // DBUSINTERFACE_H
