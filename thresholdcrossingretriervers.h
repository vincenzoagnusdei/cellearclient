#ifndef THRESHOLDCROSSINGRETRIEVERS_H
#define THRESHOLDCROSSINGRETRIEVERS_H


#include <QDebug>
#include <QAbstractSocket>
#include <QDataStream>
#include <QTcpSocket>
#include <QMutex>
#include <QByteArray>
#include <QStringList>
#include "filehandler.h"
#include "ftpclient.h"



class ThresholdCrossingRetriervers : public QObject
{
    Q_OBJECT
public:
    explicit ThresholdCrossingRetriervers(QObject *parent = 0);
    ~ThresholdCrossingRetriervers();
    static const QString GET_FILE_LIST;
    static const QString GET_DATETIME;

    FileHandler * getFileHandler();


signals:

    void file_list(QStringList filelist);

public slots:
    void logError(QAbstractSocket::SocketError socketEvent);
    void on_tcp_socket_event(QAbstractSocket::SocketState socketEvent);
    bool writeData(QString data);
    void readData();

private:
     QTcpSocket *mpTcpSocket;
     const char * getTextForEnum( int enumval );
     void connectToRemoteServer();
     FileHandler *mpFH;
     FTPClient *mpFtpClient;

};




#endif // THRESHOLDCROSSINGRETRIEVERS_H
