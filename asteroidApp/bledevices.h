#ifndef BLEDEVICES_H
#define BLEDEVICES_H

#include <QDebug>
#include <QObject>
#include <QAbstractListModel>
#include <QStringList>
#include <QVariant>
#include <QDBusConnection>
#include <QDBusServiceWatcher>
#include <QDBusInterface>
#include <QDBusArgument>

#define ASTEROIDOS_SERVICE QStringLiteral("org.asteroidos")
#define ASTEROIDOS_MANAGER_PATH QStringLiteral("/org/asteroidos/Manager")
#define ASTEROIDOS_MANAGER_IFACE QStringLiteral("org.asteroidos.Manager")


class BLEDevice
{
public:
    BLEDevice(const QString &name, const QString &address);
    QString name() const;
    QString address() const;

private:
    QString m_name;
    QString m_address;
};

class BLEDevices : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum DeviceRoles {
        NameRole = Qt::UserRole + 1,
        AddressRole
    };

    BLEDevices(QObject *parent = 0);

    void addDevice(BLEDevice *device);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE BLEDevice *get(int index) const;

protected:
    QHash<int, QByteArray> roleNames() const;

signals:
    void countChanged();

private slots:
    void getData();

private:
    QList<BLEDevice *> m_devices;
    QDBusServiceWatcher *m_serviceWatcher;
};




#endif // BLEDEVICES_H
