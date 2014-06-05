#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->label->setPixmap(QPixmap(getCurrentDir()+"/data/2015_logo_epicopter.png"));

}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetAd(QString ad)
{
    this->adresse = ad;
}

void MainWindow::load()
{

}

QString MainWindow::getCurrentDir(){
    QString CurrentDir = QDir::currentPath();
    return CurrentDir;
}

void MainWindow::on_btnMap_clicked()
{
     ui->maWeb->load(QUrl("http://www.talatrique.fr/testEip/map.html"));
}

void MainWindow::on_Btnvalidation_clicked()
{
   Form *parcour = new Form();
}

void MainWindow::on_btnLogin_clicked()
{
  // Login *log = new Login();
}
