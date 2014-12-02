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

    FileHandler();

    int writeParameters(QString *thresholds=NULL);
    int readParameters(QStringList *vals);
    void initParameters(QString *val);

    enum PARAMETER_ENUM {LISTENADDRESS,LISTENPORT, REMOTEADDRESS, REMOTEPORT, FILETRANSFERPORT};




private:



};

#endif // FILEHANDLER_H
