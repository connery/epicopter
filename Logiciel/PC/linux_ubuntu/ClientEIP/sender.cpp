#include "sender.h"
#include <QDebug>


Sender::Sender()
{
  QByteArray data; // <-- fill with data
    taille = 5;
  _pSocket = new QTcpSocket( this ); // <-- needs to be a member variable: QTcpSocket * _pSocket;
  connect( _pSocket, SIGNAL(readyRead()), SLOT(readTcpData()) );
  //data.append("zboub");
  _pSocket->connectToHost(IP_CLIENT, PORT_CLIENT);
/*  if( _pSocket->waitForConnected() ) {
    qDebug() << "zeeazazae";
    _pSocket->write( data,data.size() );
    QApplication::processEvents();
    _pSocket->waitForBytesWritten();
    //_pSocket->writeData(data,data.size());
  }*/
}
void Sender::setTaille(int t){
    taille = t;
}

void Sender::ecrit(QString str)
{
     QByteArray data;
     if( _pSocket->waitForConnected() ) {

     data.append(str);
     _pSocket->connectToHost(IP_CLIENT, PORT_CLIENT);

     _pSocket->write( data,(data.size()+1));
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

   // QString str;

  /*  while(str.size() < 1)
    {
        QDataStream in(_pSocket);
        in.setVersion(QDataStream::Qt_4_0);
        in >> str;
        qDebug() <<"reponse :"+str;
       QThread::sleep(1);
    }*/

    char buffer[1024];
   // QApplication::processEvents();
  //  _pSocket->waitForBytesWritten();
    _pSocket->waitForReadyRead();
   _pSocket->read(buffer,  taille);

     QString str( buffer);

 /*   _pSocket->read(buffer, _pSocket->bytesAvailable());
    QString str2( buffer);*/
  //  return (str/*+str2*/);



        return str;
}
