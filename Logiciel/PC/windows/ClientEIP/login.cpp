#include "login.h"
//#include "packet.h"
#include "ui_login.h"
#include <QThread>
#include <unistd.h>
#include <windows.h>
#include <QTime>

#include <QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    m2_ui(new Ui::Login)
{
    m2_ui->setupUi(this);

    this->show();

    QPalette p;
    p = palette();
    p.setBrush(QPalette::Window, QBrush(QPixmap(getCurrentDir()+"/data/2015_logo_epicopter2.png")));
    setPalette(p);
    blah = QString(QCryptographicHash::hash(("myPassword"),QCryptographicHash::Md5).toHex());
    m2_ui->lblPassword->setEchoMode(QLineEdit::Password);
/*    int i = 46, y = -1, z=0;

    while (i < 127)
    {
    y++;
    if (y != 0 && (y % 9 == 0))
    {
        qDebug() <<"++;";
        y =0;
        z++;
    }
    Table[y][z]=i;
    qDebug() <<Table[y][z];
    qDebug() <<y<<" et "<<z;
    i++;
    }
*/



      s = new Sender();
}

Login::~Login()
{
    delete m2_ui;
}

QString Login::chiffrement(QString pass)
{
   return( QString(QCryptographicHash::hash(("pass"),QCryptographicHash::Md5).toHex()));
}

QString Login::getCurrentDir(){
    QString CurrentDir = QDir::currentPath();
    return CurrentDir;
}

void Login::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m2_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Login::on_BtnQuit_clicked()
{
    s->ecrit("END;");
    exit(-1);
}

void Login::on_BtnLogin_clicked()
{

    /////////////////////////////////////////////////////////////////////////////////////////////
  /*  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("http://talatrique.fr/");
    db.setDatabaseName("talatriqbdd");
    db.setUserName("talatriqbdd");
    db.setPassword("epicopter88");
    if (!db.open())
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),
                            db.lastError().text());
    }*/
     //QDesktopServices::openUrl(QUrl("C:/Users/washco/Documents/afficherGMap/updateUser.php?table=UserEpi;u_data=0:login=toto:id=1", QUrl::TolerantMode));

    /*mysql*/
    //QDesktopServices::openUrl(QUrl("C:/Users/washco/Documents/afficherGMap/login.html"));

    /////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    /*sqlite*/

    //base de donnée sqlite
    /*    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("database.db");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open())
    {
        QMessageBox::critical(0, "fenêtre connexion", "Impossible de se connecter à la base de donnée");
    }
    else
    {
        QMessageBox::information(0, "fenêtre connexion", "cool");
        QSqlQuery q("select " + m2_ui->lblLogin->text() + " from users where lower(users.name) = 'epicop'");
        QSqlRecord rec = q.record();
        qDebug() << "Number of columns: " << rec.count();
        int nameCol = rec.indexOf("name"); // index of the field "name"
        while (q.next())
        qDebug() << q.value(nameCol).toString(); // output all names
    }

    */
    /////////////////////////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////////////////////////////////////
    /*
      test de socket
      */

    //const char message[25] = "mar";
    //Packet *pa;
   // pa->data = message ;
   // pa->header = 1;
    //udp


    /*ProtoClient l1;
    int i = 0;
    while(i < 6)
    {
        blah = QString(QCryptographicHash::hash(((const char*)m2_ui->lblPassword->text().data_ptr()),QCryptographicHash::Md5).toHex());
        l1.writeData("CON "+m2_ui->lblLogin->text()+" "+blah);
        l1.myReadData();
        //QThread::msleep(1000);
        Sleep(5000);
       if( l1.getmsg() == "ok")
           break;
       i++;
    }*/
///tcp test
/*
    TcpClientProto l1;
//l1.requestNewtcp();
    while(1)
    {
            qDebug()<<"write";
            l1.writeData("oui totor est vieux");
            l1.readtcp();
            Sleep(5000);
    }
    */

    /////////////////////////////////////////////////////////////////////////////////////////////


  //chiffrement
    QString pass = chiffrement(m2_ui->lblPassword->text());
  // envoie du message

    s->ecrit("con;" + m2_ui->lblLogin->text()+";"+pass+";");
//    s.ecrit("con " + m2_ui->lblLogin->text()+" "+m2_ui->lblPassword->text());

    //reception
    QString andwser;
    s->setTaille(55);
    andwser = s->getMsg();

     andwser =andwser.mid(andwser.indexOf("CON;"),andwser.indexOf("EOF;"));
    if(andwser == "CON;y;")
    {

        this->hide();
        MainWindow *mw = new MainWindow();
        mw->show();
        mw->setSender(s);
        // s->ecrit("END");
        this->close();
    }
    else{
        qDebug() <<"reponse :"+andwser;
    }
}
