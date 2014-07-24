#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
{
    mysingleton = 0;
    posx = 0;
    posy = 300;
    this->setAlignment((Qt::AlignLeft | Qt::AlignTop)); //set le 0.0 en haut à gauche
    this->setMouseTracking(true);
}

void MyGraphicsView::Myloadcheck()
{
   QGraphicsLineItem *ligne = new QGraphicsLineItem(0, 300, 2000, 300);
    ligne->setFlag( QGraphicsItem::ItemIsMovable);
    //ligne->setPen(QPen(QColor(90,150,190),1));
    ligne->setPen(QPen(QColor(90,150,190) ,1));
    this->scene()->addItem(ligne);

    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPos(50,310);
    io->setPlainText("le sol");
    io->setDefaultTextColor(QColor(90,150,190));
    this->scene()->addItem(io);

    /* emulation de plan de vol */
    int i = 0;
    while(i < 20)
    {
        plandevol[i][0] = 6;
        plandevol[i][1] = 6;
        i++;
    }


}

void MyGraphicsView::mouseMoveEvent ( QMouseEvent * event )
{
    if(mysingleton == 0)
    {
         Myloadcheck();
         setCheckpoint();
         mysingleton++;
    }

  //  qDebug() << "X:"+QString::number(event->x())+"-- Y:"+QString::number(event->y());
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(event->y() <300)
        {
        if(posx < event->x())
        {
            QGraphicsLineItem *ligne = new QGraphicsLineItem(posx, posy, event->x(), event->y());
            ligne->setFlag( QGraphicsItem::ItemIsMovable);
            ligne->setPen(QPen(QColor(213,90,83),1));
            this->scene()->addItem(ligne);
            posx = event->x();
            posy = event->y();
        }
        else{
            QGraphicsLineItem *ligne = new QGraphicsLineItem(posx, posy, posx, event->y());
            ligne->setFlag( QGraphicsItem::ItemIsMovable);
            ligne->setPen(QPen(QColor(213,90,83),1));
            this->scene()->addItem(ligne);
            posy = event->y();
        }
        }

    }
    else if (event->button() == Qt::RightButton)
    {
        this->scene()->clear();
        Myloadcheck();
        setCheckpoint();
        posx = 0;
        posy = 200;
    }
}

void MyGraphicsView::setCheckpoint()
{
    int taille = 0, x = 0, pos = 700;
    while (plandevol[taille][0]!= 0)
        taille++;
    qDebug()<<taille;
    while(x <= taille)
    {
        x++;
        QGraphicsLineItem *ligne = new QGraphicsLineItem( (pos/taille)*x, 0, (pos/taille)*x, 300);
        ligne->setPen(QPen(QColor(213,200,200),1));
        this->scene()->addItem(ligne);

    }
}
