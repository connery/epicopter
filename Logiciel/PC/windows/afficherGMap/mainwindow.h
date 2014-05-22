#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QtGui>
#include <QtCore>
#include <QtWebKit/QtWebKit>
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
public slots:
    void goLeft() {
        moveDxDy(-10, 0);
    }

    void goRight() {
        moveDxDy(+10, 0);
    }

    void goUp() {
        moveDxDy(0, -10);
    }

    void goDown() {
        moveDxDy(0, +10);
    }

    void goHome() {
        mView->page()->mainFrame()->evaluateJavaScript( "map.panTo(myLatlng);" );
    }



private:
    Ui::MainWindow *ui;

     void moveDxDy( int dx, int dy ) {
        mView->page()->mainFrame()->evaluateJavaScript( QString("map.panBy(%1, %2);").arg(dx).arg(dy) );
    }

    QString adresse;
    QWebView *mView;

private slots:
    void on_btnLogin_clicked();
    void on_Btnvalidation_clicked();
    void on_btnMap_clicked();
};

#endif // MAINWINDOW_H
