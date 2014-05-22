#include "serv.h"
//#include <QMessageBox>

serv::serv()
{
    init();
}

void serv::init()
{
    leserv = new QTcpServer(this);
    if (!leserv->listen(QHostAddress::Any, SERVER_PORT))
    {
        qDebug()<<"Le serveur n'a pas pu être démarré. Raison :" + leserv->errorString();

    }
    else
    {
        qDebug()<<"Le serveur a été démarré sur le port <strong>" + QString::number(leserv->serverPort()) + tr("</strong>.");
        connect(leserv, SIGNAL(newConnection()), SLOT(myConnect()));
    }
}


void serv::myConnect(){
   // qDebug()<<"connexion";

    client  = leserv->nextPendingConnection();
    qDebug()<<"connecté";
    connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
//    QTcpSocket * tcpSocket = leserv->nextPendingConnection();

    /*qDebug()<<"on prend la socket du client";
     QDataStream in(tcpSocket);
     in.setVersion(QDataStream::Qt_4_0);
        qDebug()<<"je la set en data";
         qDebug()<<"c'est valable?";
     while(tcpSocket->bytesAvailable() < blockSize)
        if (blockSize == 0) {
         if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
             return;
             qDebug()<<"j'ai une donnée";
         in >> blockSize;
     }

    qDebug()<<"oui";
     QString nexttcp;
     in >> nexttcp;
     qDebug()<<"read:";
      qDebug()<<nexttcp;
     if (nexttcp == currenttcp) {
         QTimer::singleShot(0, this, SLOT(requestNewtcp()));
         return;
     }

     currenttcp = nexttcp;

*/
}

void serv::startRead()
{
    char buffer[1024] = {0};
    client->read(buffer, client->bytesAvailable());
    /*QMessageBox msgBox ;
    msgBox.setText( buffer);
    msgBox.exec();*/
    qDebug()<<buffer;
}
