#include "protoclient.h"

ProtoClient::ProtoClient(QObject *parent) :
    QObject(parent)
{
    //je crée ma socket
    socket = new QUdpSocket(this);
    //j'ouvre la communication
    socket->bind(QHostAddress::LocalHost, 1234);
    //je lance mon slot de lecture
    qDebug() << "connect";
    connect(socket, SIGNAL(myReadData()), this, SLOT(myReadData()));
    qDebug() << "fin connect";
}

void ProtoClient::writeData()
{
    //je crée ma donnée
    QByteArray Data;
    //je la rempli
    Data.append("Hello from UDP");
    //j'ecris sur la socket
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
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

}
