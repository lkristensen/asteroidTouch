#include <QCoreApplication>

#include "core.h"

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

   Core::instance()->init();

   return a.exec();
}
