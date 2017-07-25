#include "astwatchinfo.h"

AstWatchInfo::AstWatchInfo(const QBluetoothDeviceInfo &watch) :
    QObject(), m_device(watch)
{
}

QBluetoothDeviceInfo AstWatchInfo::getDevice() const
{
    return m_device;
}

QString AstWatchInfo::getName() const {
#ifdef SIMULATE_BLUETOOTH
    return "Demo watch";
#else
    return m_device.name();
#endif
}

QString AstWatchInfo::getAddress() const
{
#ifdef SIMULATE_BLUETOOTH
    return "00:11:22:33:44:55";
#else
    return m_device.address().toString();
#endif
}

void AstWatchInfo::setDevice(const QBluetoothDeviceInfo &watch)
{
    m_device = watch;
    emit deviceChanged();
}
