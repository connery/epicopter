#include <QtGui/QApplication>
#include "mainwindow.h"
#include "login.h"
#include "frm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //xml
    frm *xmlpos = new frm();
    xmlpos->show();
    //Login l;
    Login *log = new Login();
    //w.show();
    return a.exec();
}
