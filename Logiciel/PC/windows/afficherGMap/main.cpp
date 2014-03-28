#include <QtGui/QApplication>
#include "mainwindow.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Login l;
    Login *log = new Login();
    //w.show();
    return a.exec();
}
