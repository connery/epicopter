#ifndef SERV_H
#define SERV_H
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QDebug>
#include <QTimer>

#define IP_CLIENT "117.198.119.215"
#define SERVER_PORT 48888
#define PACKET_SIZE 4096

class serv: public QObject
{
    Q_OBJECT

public:
    serv();
    void init();
public slots:
    void myConnect();
    void startRead();
   // void writeServ();
    //void killer();
//public slots:
   // void reception();
    //quint64 servSend();
private:
    QTcpServer *leserv;
    quint16 blockSize;
    QString currenttcp;
    QTcpSocket *client;
            
};

#endif // SERV_H
