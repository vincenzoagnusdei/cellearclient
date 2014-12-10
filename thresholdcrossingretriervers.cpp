#include "thresholdcrossingretriervers.h"
#include <assert.h>
#include "mainwindow.h"

/* get filelist \n -> name,date,time */
/* getdata filename -> data */

static const char * EventEnumStrings[] = { "UnconnectedState","HostLookupState","ConnectingState","ConnectedState","BoundState",
"ListeningState","ClosingState" };

const QString ThresholdCrossingRetriervers::GET_FILE_LIST = "getfilelist\n";
const QString ThresholdCrossingRetriervers::GET_DATETIME = "getdatetime\n";



ThresholdCrossingRetriervers::ThresholdCrossingRetriervers(QObject *parent) :
    QObject(parent)
{


     mpFH = ((MainWindow *) parent)->getFileHanlder();
     mpTcpSocket = new QTcpSocket(this);
     mpFtpClient = new FTPClient(this);

     connect(mpTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
             SLOT(on_tcp_socket_event(QAbstractSocket::SocketState)));
     connect(mpTcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
     connect(mpTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(logError(QAbstractSocket::SocketError)));

     connect(this, SIGNAL(file_list(QStringList)), mpFtpClient, SLOT(on_synchronize_file_transfer(QStringList)),
             Qt::QueuedConnection);

     this->connectToRemoteServer();




}

ThresholdCrossingRetriervers::~ThresholdCrossingRetriervers()
{
    delete mpTcpSocket;
    delete mpFtpClient;
}

void ThresholdCrossingRetriervers::logError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found";
        break;

    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "connection refused by the peer.";
        break;

    default:
        qDebug()  << "error occurred: " << mpTcpSocket->errorString();
    }

}



void ThresholdCrossingRetriervers::on_tcp_socket_event(QAbstractSocket::SocketState ss)
{

    qDebug() << this->getTextForEnum(ss);

    if (ss == QAbstractSocket::ConnectedState)
    {

        this->writeData(GET_FILE_LIST);
    }
}

const char * ThresholdCrossingRetriervers::getTextForEnum( int enumval )
{
  return EventEnumStrings[enumval];
}



void ThresholdCrossingRetriervers::readData()
{


   QTcpSocket* socket = (QTcpSocket*)sender();
   while (socket->canReadLine())
   {
       QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));

       for (int i=0; i < tokens.size() ; i++)
       {
           qDebug() << tokens[i];
       }

       emit file_list(tokens);
       qDebug() << "Thresholdcrossinretriever tid " << QThread::currentThreadId();

   }

}



void ThresholdCrossingRetriervers::connectToRemoteServer()
{

    assert(mpFH!=NULL);

    mpTcpSocket->connectToHost(mpFH->getRemoteAddress(),
                             mpFH->getFileTransferPort().toInt());
}


bool ThresholdCrossingRetriervers::writeData(QString data)
{

    QByteArray databyte;

    databyte.append(data);

    if(mpTcpSocket->state() == QAbstractSocket::ConnectedState)
    {

        mpTcpSocket->write(databyte);
        return mpTcpSocket->waitForBytesWritten();
    }
    else
        return false;
}


FileHandler * ThresholdCrossingRetriervers::getFileHandler()
{
    return mpFH;
}

