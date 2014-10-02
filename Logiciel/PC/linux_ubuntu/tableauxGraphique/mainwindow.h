#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>



/*

class myEventFilter: public QObject
{

  public:
  myEventFilter():QObject()
  {};
  ~myEventFilter(){};

  bool eventFilter(QObject* object,QEvent* event)
  {
      if(event->type() == QEvent::MouseButtonPress)
      {

        return true;
      }
      else
      {
    return QObject::eventFilter(object,event);
      }
  };
};

*/


namespace Ui {
class MainWindow;
}

class MainWindow : public  QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void load();
    QString getposx();
    QString getposy();


/*public slots:
    void mousePressEvent(QMouseEvent * e);
*/

//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

protected:
    void changeEvent(QEvent *e);



private slots:
    void on_pushButton_clicked();
     void setpos();
public slots:
    void mouseMoveEvent (QMouseEvent *e);
      //QMainWindow::connect (this   , SIGNAL(),this, SLOT();
private:
    Ui::MainWindow *ui;
    // QGraphicsLineItem *ligne;
};

#endif // MAINWINDOW_H
