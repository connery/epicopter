#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QtGui>
#include <QtCore>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QWebView>
#include <QImage>
#include <QGraphicsView>
#include "form.h"
#include "login.h"

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



private:
    Ui::MainWindow *ui;
    QString adresse;
   // QWebView *mView;

private slots:
    void on_btnLogin_clicked();
    void on_Btnvalidation_clicked();
    void on_btnMap_clicked();
};

#endif // MAINWINDOW_H
