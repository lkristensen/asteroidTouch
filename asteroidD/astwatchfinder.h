#ifndef ASTWATCHFINDER_H
#define ASTWATCHFINDER_H

#include <QTimer>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QVariant>
#include <QObject>

#include "astwatchinfo.h"

class AstWatchFinder : public QObject
{
    Q_OBJECT

//    Q_PROPERTY(bool scanning READ scanning WRITE setScanning NOTIFY scanningChanged)
//    Q_PROPERTY(QVariant devices READ devices WRITE setDevices NOTIFY devicesChanged)
public:
    AstWatchFinder(QObject *parent = 0);
    ~AstWatchFinder();

    bool scanning() const;
    QList<AstWatchInfo *> devices();

    void startSearch();

public slots:
    void connectToService(const QString &address);

private slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void scanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void scanFinished();

signals:
    void scanningChanged();
    void devicesChanged();

private:
    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QList<AstWatchInfo *> m_devices;

#ifdef SIMULATE_BLUETOOTH
    QTimer m_demoTimer;
#endif
};

#endif // ASTWATCHFINDER_H
