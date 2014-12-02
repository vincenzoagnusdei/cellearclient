#ifndef XVALUESRETRIERVERS_H
#define XVALUESRETRIERVERS_H

#include <QThread>
#include <QDebug>
#include <QAbstractSocket>
#include <QDataStream>
#include <QTcpSocket>
#include <QMutex>


class XValuesRetriervers : public QThread
{
    Q_OBJECT
public:
    explicit XValuesRetriervers(QObject *parent = 0);
    ~XValuesRetriervers();
    void setStop(bool t);

protected:
    void run();


signals:

public slots:
    void logError(QAbstractSocket::SocketError socketEvent);
    void on_tcp_socket_event(QAbstractSocket::SocketState socketEvent);

private:
     QTcpSocket *tcpSocket;
     quint16 mBlockSize;
     const char * getTextForEnum( int enumval );
     void requestNewData();
     void readData();
     bool mStop;
};




#endif // XVALUESRETRIERVERS_H
