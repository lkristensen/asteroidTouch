#include "bledevices.h"

BLEDevices::BLEDevices(QObject *parent) :
    QAbstractListModel(parent)
{
    getData();
    m_serviceWatcher = new QDBusServiceWatcher(ASTEROIDOS_SERVICE, QDBusConnection::sessionBus(), QDBusServiceWatcher::WatchForOwnerChange, this);
    QDBusConnection::sessionBus().connect(ASTEROIDOS_SERVICE, ASTEROIDOS_MANAGER_PATH, ASTEROIDOS_MANAGER_IFACE, "AstWatchesChanged", this, SLOT(getData()));
    connect(m_serviceWatcher, &QDBusServiceWatcher::serviceRegistered, [this] {
        qDebug() << "Service Connected";
        getData();
        QDBusConnection::sessionBus().connect(ASTEROIDOS_SERVICE, ASTEROIDOS_MANAGER_PATH, ASTEROIDOS_MANAGER_IFACE, "AstWatchesChanged", this, SLOT(getData()));


        QDBusInterface iface(ASTEROIDOS_SERVICE, ASTEROIDOS_MANAGER_PATH, ASTEROIDOS_MANAGER_IFACE);
        if(!iface.isValid()) {
            qWarning() << "Could not connect to AsteroidOS D-Bus interface";
            return;
        }

        QDBusMessage reply = iface.call("StartSearch");
        qDebug() << "Called StartSearch";

    });
    connect(m_serviceWatcher, &QDBusServiceWatcher::serviceUnregistered, [this] {
        qDebug() << "Service Disconnected";
        beginResetModel();
        qDeleteAll(m_devices);
        m_devices.clear();
        endResetModel();

    });

}

void BLEDevices::addDevice(BLEDevice *device)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_devices.append(device);
    endInsertRows();
}

int BLEDevices::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_devices.count();
}

QVariant BLEDevices::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_devices.count()) {
        return QVariant();
    }

    BLEDevice *device = m_devices[index.row()];
    if(role == NameRole) {
        return device->name();
    }
    if(role == AddressRole) {
        return device->address();
    }

    return QVariant();
}

BLEDevice *BLEDevices::get(int index) const
{
    if(index >= 0 && index < m_devices.count()) {
        return m_devices.at(index);
    }

    return nullptr;
}

QHash<int, QByteArray> BLEDevices::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AddressRole] = "address";

    return roles;
}

void BLEDevices::getData()
{
    beginResetModel();
    qDeleteAll(m_devices);
    m_devices.clear();
    endResetModel();

    qDebug() << "Data changed";
    QDBusInterface iface(ASTEROIDOS_SERVICE, ASTEROIDOS_MANAGER_PATH, ASTEROIDOS_MANAGER_IFACE);
    if(!iface.isValid()) {
        qWarning() << "Could not connect to AsteroidOS D-Bus interface";
        return;
    }
    QDBusMessage reply = iface.call("ListDevices");
    if(reply.type() == QDBusMessage::ErrorMessage) {
        qWarning() << "Error getting devices: " + reply.errorMessage();
        return;
    }
    if(reply.arguments().count() == 0)
    {
        qWarning() << "No reply from D-Bus";
        return;
    }

    QStringList arg = reply.arguments().first().value<QStringList>();

    if(arg.count() % 2 != 0)
    {
        qWarning() << "Argument count does not comply with requirement";
        return;
    }

    for(QStringList::iterator it = arg.begin(); it != arg.end(); ++it) {
        QString deviceName = *it;
        ++it;
        QString deviceAddress = *it;
        addDevice(new BLEDevice(deviceName, deviceAddress));
        emit countChanged();
    }
}

BLEDevice::BLEDevice(const QString &name, const QString &address) :
    m_name(name), m_address(address)
{
}

QString BLEDevice::name() const
{
    return m_name;
}

QString BLEDevice::address() const
{
    return m_address;
}

