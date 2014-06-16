#ifndef TCPCLIENTPROTO_H
#define TCPCLIENTPROTO_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QMessageBox>
#include <QByteArray>
#include <QDataStream>
#include <iostream>
#include "User.h"




class TcpClientProto : public QObject
{
public:
     explicit TcpClientProto(QObject *parent = 0);
     void requestNewtcp();
     void readtcp();
     void writeData(QString str);
     private slots:
    QByteArray IntToArray(qint32 source);
private:
     QTcpSocket *tcpSocket;
     quint16 blockSize;
     QString currenttcp;

};

#endif // TCPCLIENTPROTO_H
