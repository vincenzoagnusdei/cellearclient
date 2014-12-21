#include "infofiletodownload.h"
#include <QDebug>



InfoFileToDownload::InfoFileToDownload():
    mDownloadStatus(Toskip)
{
}

InfoFileToDownload::~InfoFileToDownload()
{
    qDebug() << "destructor of obj InfoFileToDownload";
}


void InfoFileToDownload::setFileName(QString filename)
{
    mFileName=filename;
}

QString InfoFileToDownload::getFileName()
{
    return mFileName;
}

void InfoFileToDownload::setDateTime(QString datetime)
{
    mDateTime = datetime;
}

QString InfoFileToDownload::getDateTime()
{
    return mDateTime;
}


void InfoFileToDownload::setDownloadStatus(DownloadStatus d)
{
   mDownloadStatus = d;
}

InfoFileToDownload::DownloadStatus InfoFileToDownload::getDownloadStatus()
{
     return mDownloadStatus;
}
