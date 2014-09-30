#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* pallete :  mettre une image dans un item
    QPalette p;
    p = palette();
    p.setBrush(QPalette::Window, QBrush(QPixmap(getCurrentDir()+"/data/blueBackground.png")));
    setPalette(p);
    */



    //load la map avec l'id
    /*
     *
     * à tester avec la base op
     *
    */
    /*
    s->ecrit("LAN;map;");
    s->setTaille(20);
    QString andwser=s->getMsg();
    andwser =andwser.mid(andwser.indexOf("LAN;"),andwser.indexOf("EOF;"));
    andwser = andwser.mid(4,4);
    qDebug()<<andwser;
    idmap = andwser.toInt();
    qDebug()<<"test"+QString::number(idmap);
    ui->maWeb->load(QUrl("http://www.talatrique.fr/testEip/map.html?i_ui="+andwser));
    ui->webView->load(QUrl("http://www.talatrique.fr/MickaGraphEIP/mickaGraph"));
    */


    ui->maWeb->load(QUrl("http://www.talatrique.fr/testEip/map.html?i_ui=5"));

    connect(ui->actionValider,SIGNAL(triggered()),this,SLOT(validate()));
}



void MainWindow::validate()
{
    Form *parcour = new Form();
    parcour->setId(idmap);
    parcour->setSender(s);
}

void MainWindow::annuler()
{

}


void MainWindow::closeEvent(QCloseEvent *event)
{
   //  s->ecrit("END;");
     event->accept();
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
