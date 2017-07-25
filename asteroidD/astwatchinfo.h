#ifndef ASTWATCHINFO_H
#define ASTWATCHINFO_H

#include <QString>
#include <QObject>
#include <QBluetoothDeviceInfo>
#include <QBluetoothAddress>

class AstWatchInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName READ getName NOTIFY deviceChanged)
    Q_PROPERTY(QString deviceAddress READ getAddress NOTIFY deviceChanged)
public:
    AstWatchInfo(const QBluetoothDeviceInfo &watch);
    void setDevice(const QBluetoothDeviceInfo &watch);
    QString getName() const;
    QString getAddress() const;
    QBluetoothDeviceInfo getDevice() const;

signals:
    void deviceChanged();

private:
    QBluetoothDeviceInfo m_device;
};

#endif // ASTWATCHINFO_H
