#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>

#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

class MyGraphicsView: public QGraphicsView
{
private:
    int posx;
    int posy;
    int mysingleton;
    int plandevol[50][2];

  public:
    void Myloadcheck();
    MyGraphicsView(QWidget *parent = 0);
    //~MyGraphicsView(){};
    void setCheckpoint();
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent(QMouseEvent *event);

};

#endif // MYGRAPHICSVIEW_H
