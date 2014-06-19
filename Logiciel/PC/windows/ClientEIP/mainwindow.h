#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QtGui>
#include <QtCore>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QWebView>
#include <QImage>
#include <QGraphicsView>
#include <QDebug>
#include "form.h"
#include "login.h"
#include "hauteur.h"
#include "sender.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
   // void geoCode(QString local);
    void load();
    void SetAd(QString ad);
    QString getCurrentDir();
    void setSender(Sender *s1);


private:
    Ui::MainWindow *ui;
    QString adresse;
    int idmap;
    Sender *s;
   // QWebView *mView;

private slots:
    void on_btnLogin_clicked();
    void on_Btnvalidation_clicked();
    void on_btnMap_clicked();
    void on_cancel_clicked();
};

#endif // MAINWINDOW_H
