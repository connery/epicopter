#ifndef LOGIN_H
#define LOGIN_H

#include <QtGui/QWidget>
#include <QtSql>
#include <QtWebKit/QtWebKit>
#include <QImage>
#include <QGraphicsView>
#include <QtCore>
#include <QtGui/QtGui>

namespace Ui {
    class Login;
}

class Login : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(Login)
public:
    explicit Login(QWidget *parent = 0);
    virtual ~Login();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Login *m2_ui;

private slots:
    void on_BtnLogin_clicked();
    void on_BtnQuit_clicked();
};

#endif // LOGIN_H
