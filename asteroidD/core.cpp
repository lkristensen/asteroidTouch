#include "core.h"

Core* Core::s_instance = 0;

Core *Core::instance()
{
    if(!s_instance) {
        s_instance = new Core();
    }
    return s_instance;
}

Core::Core(QObject *parent) :
    QObject(parent)
{
}

void Core::init()
{
    qDebug() << "Initializing";
    m_dbusInterface = new DBusInterface(this);
}
