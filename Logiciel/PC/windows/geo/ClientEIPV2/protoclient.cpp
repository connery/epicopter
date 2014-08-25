#include "protoclient.h"

ProtoClient::ProtoClient(QObject *parent) :
    QObject(parent)
{
    //je crée ma socket
    socket = new QUdpSocket(this);
    //j'ouvre la communication
     QHostAddress ipclient;
     ipclient.setAddress(IP_CLIENT);
    socket->bind(ipclient, PORT_CLIENT);
    //je lance mon slot de lecture
    qDebug() << "connect";
    //this->myReadData();
    QObject::connect(socket, SIGNAL(ReadData()), this, SLOT(ReadData()));
    qDebug() << "fin connect";
    msg = "";
}

void ProtoClient::writeData(QString str)
{
    //je crée ma donnée
    QByteArray Data;
    //je la rempli
    Data.append(str);
    //j'ecris sur la socket
    QHostAddress ipclient;
    // ipclient.setAddress("117.198.115.194");
          ipclient.setAddress(IP_CLIENT);

    //socket->writeDatagram(Data,  QHostAddress::LocalHost, 4242);
     socket->writeDatagram(Data,  ipclient, PORT_CLIENT);
}

void ProtoClient::writeStruct( Packet *pa)
{
     QByteArray Data;
     QHostAddress ipclient;
     ipclient.setAddress(IP_CLIENT);
    //je la rempli
    Data.append((char*)pa);
    //j'ecris sur la socket
    socket->writeDatagram(Data, ipclient, PORT_CLIENT);
}

void ProtoClient::myReadData()
{
    //je creer mon buffer

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());


    QHostAddress sender;
    quint16 senderPort;

    //je lis la socket
    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);
    //aff de test
    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
    msg = buffer.data();

}

QString ProtoClient::getmsg()
{
    return msg;
}
