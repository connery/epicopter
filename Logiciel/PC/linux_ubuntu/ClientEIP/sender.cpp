#include "sender.h"



Sender::Sender()
{
  QByteArray data; // <-- fill with data

  _pSocket = new QTcpSocket( this ); // <-- needs to be a member variable: QTcpSocket * _pSocket;
  connect( _pSocket, SIGNAL(readyRead()), SLOT(readTcpData()) );
  data.append("zboub");
  _pSocket->connectToHost(IP_CLIENT, PORT_CLIENT);
  if( _pSocket->waitForConnected() ) {
    qDebug() << "zeeazazae";
    _pSocket->write( data,data.size() );
    QApplication::processEvents();
    _pSocket->waitForBytesWritten();
    //_pSocket->writeData(data,data.size());
  }
}

void Sender::ecrit(QString str)
{
     QByteArray data;
     if( _pSocket->waitForConnected() ) {

     data.append(str);
     _pSocket->connectToHost(IP_CLIENT, PORT_CLIENT);

     _pSocket->write( data,data.size());
     QApplication::processEvents();
     _pSocket->waitForBytesWritten();
     }
}

void Sender::readTcpData()
{
    /////////////////////////////////////////////////////////////
    /* v1 */
/*   QDataStream in(_pSocket);
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
     qDebug()<<nexttcp;*/
    /////////////////////////////////////////////////////////////
/*     if (nexttcp == currenttcp) {
         QTimer::singleShot(0, this, SLOT(requestNewtcp()));
         return;
     }

     currenttcp = nexttcp;*/

    /* v2   */


}

QString Sender::getMsg(){
    char buffer[1024] = {0};
    _pSocket->read(buffer, _pSocket->bytesAvailable());

    QString str( buffer);
    return str;
}
