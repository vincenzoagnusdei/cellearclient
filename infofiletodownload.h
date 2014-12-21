#ifndef INFOFILETODOWNLOAD_H
#define INFOFILETODOWNLOAD_H
#include <QString>


class InfoFileToDownload
{

public:
    InfoFileToDownload();
    ~InfoFileToDownload();

    // this flag will be update after the download
    // to have info about success or failure

    enum DownloadStatus {Tobedownloaded, Toskip, Downloaded, Failed};
    void setFileName(QString);
    QString getFileName();
    void setDateTime(QString);
    QString getDateTime();
    void setDownloadStatus(DownloadStatus);
    DownloadStatus getDownloadStatus();


private:
    QString mFileName;
    QString mDateTime;
    DownloadStatus mDownloadStatus;



};

#endif // INFOFILETODOWNLOAD_H

