#ifndef SENDER_H
#define SENDER_H

#include <QImage>
#include <QTcpSocket>
#include <QTimer>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <iostream>
#include <QObject>
#include <QApplication>
#include "User.h"

class QUdpSocket;
class QImage;

class Sender: public QObject
{
  Q_OBJECT

  public:
  Sender();
  void ecrit(QString str);
  QString getMsg();

  public slots:
    void readTcpData();

 private:
    QTcpSocket *_pSocket;
    QUdpSocket *socket;
    QImage *image;
    quint16 blockSize;
    QString currenttcp;

};

#endif // SENDER_H
