#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QString>
#include <QStringList>

class FileHandler
{
public:

    static const QString PARAMETER_FILE;
    static const QString LOOP_IP;
    static const QString LOCAL_PORT;
    static const QString REMOTE_PORT;
    static const QString FILETRANSFER_PORT;
    static const QString FILE_DIRECTORY;
    static const QString INFO_FILE;

    FileHandler();

    int writeParameters(QString *thresholds=NULL);
    int writeFileInfo(QStringList infolist);
    int getFileInfo(QStringList *infolist);

    enum PARAMETER_ENUM {LISTENADDRESS,LISTENPORT, REMOTEADDRESS, REMOTEPORT, FILETRANSFERPORT};

    // enum FILE_INFO_ENUM {HUMIDITY_TH, HUMIDITY_VAL, TEMPERATURE_TH, TEMPERATURE_VAL, LUMINOSITY_TH, LUMINOSITY_VAL };
    enum FILE_INFO_ENUM { TEMPERATURE_X_TH, TEMPERATURE_VALUE};

    QString getListenPort();
    QString getRemotePort();
    QString getFileTransferPort();
    QString getListenAddress();
    QString getRemoteAddress();



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
