#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->label->setPixmap(QPixmap(getCurrentDir()+"/data/2015_logo_epicopter.png"));
    ui->webView->setMaximumHeight(250);
    ui->webView->setMinimumHeight(250);
    QPalette p;
    p = palette();
    p.setBrush(QPalette::Window, QBrush(QPixmap(getCurrentDir()+"/data/blueBackground.png")));
    setPalette(p);
}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetAd(QString ad)
{
    this->adresse = ad;
}

void MainWindow::setSender(Sender *s1)
{
    s = s1;
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
     ui->webView->load(QUrl("http://www.talatrique.fr/MickaGraphEIP/mickaGraph"));


     s->ecrit("LAN;map;");
     s->setTaille(20);
     QString andwser=s->getMsg();
     andwser =andwser.mid(andwser.indexOf("LAN;"),andwser.indexOf("EOF;"));
     andwser = andwser.mid(4,4);
     qDebug()<<andwser;
     idmap = andwser.toInt();
     qDebug()<<"test"+QString::number(idmap);
}

void MainWindow::on_Btnvalidation_clicked()
{
   Form *parcour = new Form();
   parcour->setId(idmap);
   parcour->setSender(s);
}

void MainWindow::on_btnLogin_clicked()
{
  // Login *log = new Login();

}

void MainWindow::on_cancel_clicked()
{
    s->ecrit("END;");
    exit(-1);
}
