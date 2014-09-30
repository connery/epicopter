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

#include "sender.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
      void closeEvent(QCloseEvent *event);


public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void load();
    void SetAd(QString ad);
    QString getCurrentDir();
    void setSender(Sender *s1);


private:
    Ui::MainWindow *ui;
    QString adresse;
    int idmap;
    Sender *s;


private slots:
    void validate();
    void annuler();
};

#endif // MAINWINDOW_H
