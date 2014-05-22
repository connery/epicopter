#include "sender.h"



Sender::Sender()
{
  QByteArray data; // <-- fill with data

  _pSocket = new QTcpSocket( this ); // <-- needs to be a member variable: QTcpSocket * _pSocket;
  connect( _pSocket, SIGNAL(readyRead()), SLOT(readTcpData()) );
  data.append("zboub");
  _pSocket->connectToHost("127.0.0.1", 48888);
  if( _pSocket->waitForConnected() ) {
    qDebug() << "zeeazazae";
    _pSocket->write( data,data.size() );
    //_pSocket->writeData(data,data.size());
  }
}

void Sender::readTcpData()
{
   QDataStream in(_pSocket);
     in.setVersion(QDataStream::Qt_4_0);

     if (blockSize == 0) {
         if (_pSocket->bytesAvailable() < (int)sizeof(quint16))
             return;

         in >> blockSize;
     }

     if (_pSocket->bytesAvailable() < blockSize)
         return;

     QString nexttcp;
     in >> nexttcp;
     qDebug()<<"read:";
     qDebug()<<nexttcp;
/*     if (nexttcp == currenttcp) {
         QTimer::singleShot(0, this, SLOT(requestNewtcp()));
         return;
     }

     currenttcp = nexttcp;*/
}
