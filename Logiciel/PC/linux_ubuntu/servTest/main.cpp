#include <QtCore/QCoreApplication>
#include "serv.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    serv s;
    return a.exec();
}
