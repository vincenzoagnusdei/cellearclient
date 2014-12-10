#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include <filehandler.h>
#include <QThread>
#include <qftp/qftp.h>
#include <QFile>

class FTPClient : public QThread
{
    Q_OBJECT
public:
    explicit FTPClient(QObject *parent = 0);

signals:

public slots:
    void ftpCommandFinished(int, bool error);
    void updateDataTransferProgress(qint64 readBytes, qint64 totalBytes);
    void on_synchronize_file_transfer(QStringList fileinfo);

protected:
    void run();

private:
    FileHandler *mpFH;
    QFtp *mpFtp;
    void getRemoteFile(QString filename);
    QFile *mpFileToDownload;


    void connectToFtp();
    void disconnectFromFTP();

};

#endif // FTPCLIENT_H
