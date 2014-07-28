#include "tcpclientproto.h"

TcpClientProto::TcpClientProto(QObject *parent) :
        QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    connect( tcpSocket, SIGNAL(readyRead()), SLOT(readtcp()) );
}

void TcpClientProto::requestNewtcp()
 {

     blockSize = 0;
     tcpSocket->abort();
     tcpSocket->connectToHost(IP_CLIENT, PORT_CLIENT);
 }

void TcpClientProto::writeData(QString str)
{
    QByteArray data;
    data.append(str);
    tcpSocket->connectToHost("127.0.0.1", 48888);
    if(tcpSocket->waitForConnected())
    {
        //tcpSocket->write(IntToArray(data.size())); //write size of data
        tcpSocket->write(data); //write the data itself
    }


}

QByteArray TcpClientProto::IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}




void TcpClientProto::readtcp()
 {
     QDataStream in(tcpSocket);
     in.setVersion(QDataStream::Qt_4_0);

     if (blockSize == 0) {
         if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
             return;

         in >> blockSize;
     }

     if (tcpSocket->bytesAvailable() < blockSize)
         return;

     QString nexttcp;
     in >> nexttcp;
     qDebug()<<"read:";
     qDebug()<<nexttcp;
     if (nexttcp == currenttcp) {
         QTimer::singleShot(0, this, SLOT(requestNewtcp()));
         return;
     }

     currenttcp = nexttcp;

 }

