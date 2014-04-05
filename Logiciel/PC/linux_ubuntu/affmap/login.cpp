#include "login.h"
#include "ui_login.h"

#include <QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    m2_ui(new Ui::Login)
{
    m2_ui->setupUi(this);

    this->show();

    QPalette p;
    p = palette();
    p.setBrush(QPalette::Window, QBrush(QPixmap("../affmap/2015_logo_epicopter2.png")));
    setPalette(p);
    QString blah = QString(QCryptographicHash::hash(("myPassword"),QCryptographicHash::Md5).toHex());
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
}

Login::~Login()
{
    delete m2_ui;
}

QString Login::chiffrement(QString pass)
{
   return( QString(QCryptographicHash::hash(("pass"),QCryptographicHash::Md5).toHex()));
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
    QString pass = chiffrement(m2_ui->lblPassword->text());
    qDebug() <<pass;
    qDebug() <<m2_ui->lblPassword->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("database.db");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open())
    {
        QMessageBox::critical(0, "fen�tre connexion", "Impossible de se connecter � la base de donn�e");
    }
    else
    {
        QMessageBox::information(0, "fen�tre connexion", "cool");
        QSqlQuery q("select " + m2_ui->lblLogin->text() + " from users where lower(users.name) = 'epicop'");
        QSqlRecord rec = q.record();
        qDebug() << "Number of columns: " << rec.count();
        int nameCol = rec.indexOf("name"); // index of the field "name"
        while (q.next())
        qDebug() << q.value(nameCol).toString(); // output all names
    }
    if(m2_ui->lblPassword->text() == "toto")
    {
       // Login l;
       // l.hide();
         // qDebug() << "if... " ;
        this->hide();
        MainWindow *mw = new MainWindow();
        mw->show();
    }
}
