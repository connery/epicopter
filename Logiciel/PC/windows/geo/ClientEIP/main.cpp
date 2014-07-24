#include "mainwindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login *l =new Login();
/*
    MainWindow w;
    w.show();
*/
    return a.exec();
}
