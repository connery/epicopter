#ifndef PROTOCLIENT_H
#define PROTOCLIENT_H

#include <QUdpSocket>
#include <QObject>

class ProtoClient : public QObject
{

public:
    explicit ProtoClient(QObject *parent = 0);
    void writeData();

public slots:
    void myReadData();
private:
    QUdpSocket *socket;

};

#endif // PROTOCLIENT_H
