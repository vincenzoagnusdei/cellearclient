#include "ftpclient.h"
#include <QStringList>
#include <QString>
#include <QtNetwork>
#include <mainwindow.h>
#include <qftp/qftp.h>
#include <thresholdcrossingretriervers.h>


FTPClient::FTPClient(QObject *parent) :
    QThread(parent)
{
    mpFH = ((ThresholdCrossingRetriervers *) this->parent())->getFileHandler();
    qDebug() << mpFH->getRemoteAddress();
}



void FTPClient::run()
{
   qDebug() << "FtpClient run tid " << QThread::currentThreadId();
   exec();

}



void FTPClient::on_synchronize_file_transfer(QStringList fileinfo)
{
    // start from 1 to skip command

     qDebug() << "FtpClient tid " << QThread::currentThreadId();

    QStringList localFileInfo;

    if (mpFH->getFileInfo(&localFileInfo) == 1)
    {
        // data present
    }
    else
    {
        // data not present, retrieve all the files
        this->connectToFtp();
        this->getRemoteFile(fileinfo[1]);
    }


}


void FTPClient::connectToFtp()
{

    mpFtp= new QFtp(this);
    connect(mpFtp, SIGNAL(commandFinished(int,bool)),
            this, SLOT(ftpCommandFinished(int,bool)));
    connect(mpFtp, SIGNAL(dataTransferProgress(qint64,qint64)),
            this, SLOT(updateDataTransferProgress(qint64,qint64)));

    qDebug() << "FtpClient::connecToFtp tid " << QThread::currentThreadId();

    mpFtp->connectToHost(mpFH->getRemoteAddress());
    mpFtp->login("cellarmonitor", "cellarmonitor");

}



void FTPClient::ftpCommandFinished(int, bool error)
{

    if (mpFtp->currentCommand() == QFtp::ConnectToHost)
    {
        if (error) {
            qDebug() <<"Unable to connect to the FTP server ";

            return;
        }

        return;
    }



    if (mpFtp->currentCommand() == QFtp::Login)
    {
        return;
    }


    if (mpFtp->currentCommand() == QFtp::Get)
    {
        if (error) {
            qDebug() << "Canceled download";


        }
        else
        {
          qDebug() << "file download terminated";
          mpFileToDownload->flush();
          mpFileToDownload->close();
          delete mpFileToDownload;
        }

    } else if (mpFtp->currentCommand() == QFtp::List) {
        return;
    }

}


void FTPClient::updateDataTransferProgress(qint64 readBytes,
                                           qint64 totalBytes)
{
    qDebug() << "Transfer Progress readBytes " << readBytes << " totalBytes " << totalBytes;
    return;

}



void FTPClient::disconnectFromFTP()
{

    if (mpFtp) {
        mpFtp->abort();
        mpFtp->deleteLater();
        mpFtp = 0;
    }


}


void FTPClient::getRemoteFile(QString filename)
{

    mpFileToDownload = new QFile(filename);
    if (!mpFileToDownload->open(QIODevice::WriteOnly)) {
        qDebug() << "Unable to save the file";

        delete mpFileToDownload;
        return;
    }

    mpFtp->get(filename, mpFileToDownload);


}
