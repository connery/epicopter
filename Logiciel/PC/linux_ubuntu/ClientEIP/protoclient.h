#ifndef PROTOCLIENT_H
#define PROTOCLIENT_H

#include <QUdpSocket>
#include <QObject>
//#include "packet.h"
#include "User.h"

class ProtoClient : public QObject
{



public slots:
    void myReadData();
private:
     QString msg;
    QUdpSocket *socket;
      struct Header
{
  int opcode;
  char name[NAME_SIZE];

  int datalen;
  int ID;
} ;
    struct Packet
{
      Header header;  // the packet header (described above)
      char data[MAX_DATA];    // the contents of the packet
} ;

    public:
    explicit ProtoClient(QObject *parent = 0);
    void writeData(QString str);
    void writeStruct(Packet *pa);
    QString getmsg();
};

#endif // PROTOCLIENT_H
