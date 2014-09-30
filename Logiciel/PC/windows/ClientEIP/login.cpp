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
    setPalette(p);

    blah = QString(QCryptographicHash::hash(("myPassword"),QCryptographicHash::Md5).toHex());
    m2_ui->lblPassword->setEchoMode(QLineEdit::Password);

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

void Login::closeEvent(QCloseEvent *event)
{
    s->ecrit("END;");
    event->accept();
}


void Login::on_BtnLogin_clicked()
{

/*
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
*/
       this->hide();
        m2_ui->lblLogin->setText("please wait");
        m2_ui->lblPassword->setText("");

        MainWindow *mw = new MainWindow();
        mw->show();
        mw->setSender(s);
        // s->ecrit("END");
        this->close();
  /*  }
    else{
        qDebug() <<"reponse :"+andwser;
    }*/
}

