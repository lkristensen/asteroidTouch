#ifndef CORE_H
#define CORE_H

#include "dbusinterface.h"

#include <QObject>
#include <QDebug>

class DBusInterface;

class Core : public QObject
{
    Q_OBJECT

public:
    static Core *instance();
    void init();

private:
    explicit Core(QObject *parent = 0);
    static Core *s_instance;

    DBusInterface *m_dbusInterface;
};

#endif // CORE_H
