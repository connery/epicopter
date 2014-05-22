#ifndef LOGIN_H
#define LOGIN_H

#include <QtGui/QWidget>
#include <QtSql>
#include <QtWebKit/QtWebKit>
#include <QImage>
#include <QGraphicsView>
#include <QtCore>
#include <QtGui/QtGui>
#include <QDebug>
#include <QCryptographicHash>
#include "protoclient.h"
#include "tcpclientproto.h"
#include "mainwindow.h"
#include "sender.h"


namespace Ui {
    class Login;
}

class Login : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(Login)
public:
    explicit Login(QWidget *parent = 0);
    virtual ~Login();
    QString chiffrement(QString);
    QString dechiffrement(QString);
    QString getCurrentDir();
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Login *m2_ui;
     QString blah;
   // QString masterKey[10][10];
   // QString Table[10][10];


private slots:
    void on_BtnLogin_clicked();
    void on_BtnQuit_clicked();
};

#endif // LOGIN_H
