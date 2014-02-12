#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    m2_ui(new Ui::Login)
{
    m2_ui->setupUi(this);
    this->show();
}

Login::~Login()
{
    delete m2_ui;
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
    exit(-1);
}

void Login::on_BtnLogin_clicked()
{
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

    /*sqlite*/
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("database.db");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open())
    {
        QMessageBox::critical(0, "Titre de la fenêtre", "Impossible de se connecter à la base de donnée");
    }
    else
    {
        QMessageBox::information(0, "Titre de la fenêtre", "cool");
        QSqlQuery q("select " + m2_ui->lblLogin->text() + " from users where lower(users.name) = 'epicop'");
        QSqlRecord rec = q.record();
        qDebug() << "Number of columns: " << rec.count();
        int nameCol = rec.indexOf("name"); // index of the field "name"
        while (q.next())
        qDebug() << q.value(nameCol).toString(); // output all names
    }

}
