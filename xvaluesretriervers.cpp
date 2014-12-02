#include "xvaluesretriervers.h"


static const char * EventEnumStrings[] = { "UnconnectedState","HostLookupState","ConnectingState","ConnectedState","BoundState",
"ListeningState","ClosingState" };

XValuesRetriervers::XValuesRetriervers(QObject *parent) :
    QThread(parent)
{
     mBlockSize=0;
     mStop=false;
     tcpSocket = new QTcpSocket(this);
     connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
             SLOT(on_tcp_socket_event(QAbstractSocket::SocketState)));
     connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
     connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(logError(QAbstractSocket::SocketError)));

}

XValuesRetriervers::~XValuesRetriervers()
{
    delete tcpSocket;
}

void XValuesRetriervers::logError(QAbstractSocket::SocketError socketError)
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
        qDebug()  << "error occurred: " << tcpSocket->errorString();
    }

}



void XValuesRetriervers::on_tcp_socket_event(QAbstractSocket::SocketState ss)
{

    qDebug() << this->getTextForEnum(ss);
}

const char * XValuesRetriervers::getTextForEnum( int enumval )
{
  return EventEnumStrings[enumval];
}



void XValuesRetriervers::readData()
{


    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (mBlockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> mBlockSize;
    }

    if (tcpSocket->bytesAvailable() < mBlockSize)
        return;

    QString nextFortune;
    in >> nextFortune;


}


void XValuesRetriervers::run()
{
    QMutex mutex;

    do
    {

        mutex.lock();
        if (this->mStop)
        {
            break;
        }

        mutex.unlock();

    } while(!mStop);

    this->setStop(false);


}

void XValuesRetriervers::setStop(bool t)
{
     QMutex mutex;
     mutex.lock();
     this->mStop = t;
     mutex.unlock();
     tcpSocket->abort();

}


void XValuesRetriervers::requestNewData()
{

    mBlockSize = 0;
    tcpSocket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
}
