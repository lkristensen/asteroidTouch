#include "astwatchfinder.h"

AstWatchFinder::AstWatchFinder(QObject *parent) :
    QObject(parent)
{
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
//    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000);

    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &AstWatchFinder::addDevice);
    connect(m_deviceDiscoveryAgent, static_cast<void (QBluetoothDeviceDiscoveryAgent::*)(QBluetoothDeviceDiscoveryAgent::Error)>(&QBluetoothDeviceDiscoveryAgent::error),
            this, &AstWatchFinder::scanError);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &AstWatchFinder::scanFinished);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled,
            this, &AstWatchFinder::scanFinished);

#ifdef SIMULATE_BLUETOOTH
    m_demoTimer.setSingleShot(true);
    m_demoTimer.setInterval(2000);
    connect(&m_demoTimer, &QTimer::timeout,
            this, &AstWatchFinder::scanFinished);
#endif
}

AstWatchFinder::~AstWatchFinder()
{
    qDeleteAll(m_devices);
    m_devices.clear();
}

void AstWatchFinder::startSearch()
{
    qDeleteAll(m_devices);
    m_devices.clear();

    emit devicesChanged();

#ifdef SIMULATE_BLUETOOTH
    m_demoTimer.start();
#else
    m_deviceDiscoveryAgent->start();
#endif

    emit scanningChanged();
}

void AstWatchFinder::addDevice(const QBluetoothDeviceInfo &watch)
{
    if(watch.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        m_devices.append(new AstWatchInfo(watch));
        emit devicesChanged();
    }
}

void AstWatchFinder::scanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
}

QList<AstWatchInfo *> AstWatchFinder::devices()
{
    return m_devices;
}

void AstWatchFinder::scanFinished()
{
#ifdef SIMULATE_BLUETOOTH
    for(int i = 0; i < 4; i++) {
        m_devices.append(new AstWatchInfo(QBluetoothDeviceInfo()));
    }
#endif
    if(m_devices.size() == 0) {} //None found
    else {} //Devices found

    emit scanningChanged();
    emit devicesChanged();
}

void AstWatchFinder::connectToService(const QString &address)
{
    m_deviceDiscoveryAgent->stop();
}
