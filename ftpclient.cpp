#include "ftpclient.h"
#include <QStringList>
#include <QString>
#include <QtNetwork>
#include <mainwindow.h>
#include <qftp/qftp.h>
#include "thresholdcrossingretriervers.h"
#include "infofiletodownload.h"




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



void FTPClient::on_synchronize_files(QStringList fileinfo)
{
    int idx;
    QString ldatetime;
    bool mustcallconnect=false;

    QStringList localFileInfo;
    mpFH->getFileInfo(&localFileInfo);
    mFiletodownload.clear();



    for (int i=0; i < fileinfo.size(); i+=2)
    {
        if (localFileInfo.size() != 0)
        {

            // localFileInfo present
            // get index of localfilename
            idx=localFileInfo.indexOf(fileinfo.at(i));

            if (idx != -1)
            {
                ldatetime = localFileInfo.at(idx+1);

                InfoFileToDownload* info = new InfoFileToDownload();


                info->setFileName(fileinfo.at(idx));
                info->setDateTime(fileinfo.at(idx+1));

                if (ldatetime.compare(fileinfo.at(idx+1)) !=0)
                {
                    info->setDownloadStatus(InfoFileToDownload::Tobedownloaded);
                    mustcallconnect=true;

                }
                else
                {
                    info->setDownloadStatus(InfoFileToDownload::Toskip);
                }

                   mFiletodownload.append(info);
            }
        }
        else
        {
            // first time remote file are retrieved

            InfoFileToDownload* info = new InfoFileToDownload();
            info->setFileName(fileinfo.at(i));
            info->setDateTime(fileinfo.at(i+1));
            info->setDownloadStatus(InfoFileToDownload::Tobedownloaded);
            mFiletodownload.append(info);
            mustcallconnect=true;

        }


    }

    if (mustcallconnect)
    {
        mpFH->removeFileInfo();
        this->connectToFtp();
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

        this->downloadNextFile();

        return;
    }


    if (mpFtp->currentCommand() == QFtp::Get)
    {
        if (error) {
            qDebug() << "Canceled download";
        }
        else
        {
          mpInfo->setDownloadStatus(InfoFileToDownload::Downloaded);
          qDebug() << "file download terminated";
          mpFileToDownload.flush();
          mpFileToDownload.close();
          QString infofile;
          infofile.append(mpInfo->getFileName());
          infofile.append(FileHandler::SEPARATOR);
          infofile.append(mpInfo->getDateTime());
          infofile.append(FileHandler::SEPARATOR);
          mpFH->writeFileInfo(&infofile);          

          if (this->getNextFileNameToDownload() == NULL)
          {
              // no more files to download
              // disconnect ftp
              this->disconnectFromFTP();
          }
          else
          {
            this->downloadNextFile();
          }


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

    mpFileToDownload.setFileName(filename);
    if (!mpFileToDownload.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Unable to save the file";

        return;
    }

    mpFtp->get(filename, &mpFileToDownload);


}


/**
<Retrieve from remote host>

<Retrieve from remote host. The name of the file to dowload>
<is store in the mFiletodownload List>

@param
@return True if a download is started.
@return False if there is no file to download.

*/

bool FTPClient::downloadNextFile()
{
    this->mpInfo = NULL;
    bool ret=false;


    foreach (InfoFileToDownload *i, mFiletodownload )
    {
        if (i->getDownloadStatus() == InfoFileToDownload::Tobedownloaded)
        {

            this->mpInfo = i;
            qDebug() << this->mpInfo->getFileName();
            break;
        }
    }

    if (this->mpInfo!= NULL)
    {
        this->getRemoteFile((this->mpInfo)->getFileName());
        ret=true;
    }

    return ret;
}



QString FTPClient::getNextFileNameToDownload()
{
    QString filename=NULL;

    foreach (InfoFileToDownload *i, mFiletodownload )
    {
        if (i->getDownloadStatus() == InfoFileToDownload::Tobedownloaded)
        {

            filename = i->getFileName();

            break;
        }
    }

    return filename;

}
