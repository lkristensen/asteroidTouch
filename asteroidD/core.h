#ifndef CORE_H
#define CORE_H


#include <QObject>
#include <QDebug>

class Core : public QObject
{
    Q_OBJECT

public:
    static Core *instance();
    void init();

private:
    explicit Core(QObject *parent = 0);
    static Core *s_instance;
};

#endif // CORE_H
