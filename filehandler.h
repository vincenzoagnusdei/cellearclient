#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QString>
#include <QStringList>

class FileHandler
{
public:

    FileHandler();

    int writeParameters(QString *thresholds=NULL);
    int writeFileInfo(QString *infolist);
    int getFileInfo(QStringList *infolist);
    int removeFileInfo();
    QString getListenPort();
    QString getRemotePort();
    QString getFileTransferPort();
    QString getListenAddress();
    QString getRemoteAddress();

    static const QString PARAMETER_FILE;
    static const QString LOOP_IP;
    static const QString LOCAL_PORT;
    static const QString REMOTE_PORT;
    static const QString FILETRANSFER_PORT;
    static const QString FILE_DIRECTORY;
    static const QString INFO_FILE;
    static const QString SEPARATOR;
    static const QString TERMINATOR;
    static const QString SEPARATOR1;
    static const QString SEPARATOR2;


    enum parameter_enum {listenaddress,listenport, remoteaddress, remoteport, filetransferport};


private:
    QString mlistenAddress;
    QString mlistenPort;
    QString mremoteAddress;
    QString mremotePort;
    QString mfileTransferPort;

    void initParameters(QString *val);
    int readParameters(QStringList *vals);   



};

#endif // FILEHANDLER_H
