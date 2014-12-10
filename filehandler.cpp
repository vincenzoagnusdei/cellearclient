#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QHostInfo>

#include <QFile>
#include <QFileInfo>
#include "filehandler.h"




const QString FileHandler::PARAMETER_FILE = "parameters.txt";
const QString FileHandler::LOOP_IP = "127.0.0.1";
const QString FileHandler::LOCAL_PORT="10000";
const QString FileHandler::REMOTE_PORT="9999";
const QString FileHandler::FILETRANSFER_PORT="9998";
const QString FileHandler::FILE_DIRECTORY="/home/cellarmonitor/client/";
const QString FileHandler::INFO_FILE="infofile.txt";


FileHandler::FileHandler()
{
    QStringList val;
    this->readParameters(&val);
    this->mlistenAddress=val.at(LISTENADDRESS);
    this->mlistenPort=val.at(LISTENPORT);
    this->mremoteAddress=val.at(REMOTEADDRESS);
    this->mremotePort=val.at(REMOTEPORT);
    this->mfileTransferPort=val.at(FILETRANSFERPORT);

}


int FileHandler::writeParameters(QString *vals)
{


    QFile file(PARAMETER_FILE);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        qDebug() << "Error writing file " << PARAMETER_FILE;
        return -1;
    }

    QTextStream datastream(&file);
    datastream << *vals;
    file.flush();
    file.close();

     return 1;

}


int FileHandler::readParameters(QStringList *vals)
{
    QString parameters;
    QFileInfo fileinfo = QFileInfo(PARAMETER_FILE);

    if (!fileinfo.exists())
    {
        this->initParameters(&parameters);
        if (this->writeParameters(&parameters) == -1)
        {
            qDebug() << "Error initializing parameter file";
            return -1;
        }

    }


    QFile file(PARAMETER_FILE);
    if (!file.open(QFile::ReadOnly ))
    {
        qDebug() << "Error opening Parameter File" << FILE_DIRECTORY << PARAMETER_FILE;
        return -1;
    }


    QTextStream in(&file);
    while (!in.atEnd()) {
      parameters = in.readAll();

    }

    *vals = parameters.split('\n');
    file.close();

    return 1;

}

void FileHandler::initParameters(QString *val)
{
    QString ip=NULL;


    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {

            ip=address.toString();
            break;
         }

    }

    if (ip == NULL)
    {
        ip = LOOP_IP;
    }

    val->append(ip);
    val->append("\n");
    val->append(LOCAL_PORT);
    val->append("\n");
    val->append(ip);
    val->append("\n");
    val->append(REMOTE_PORT);
    val->append("\n");
    val->append(FILETRANSFER_PORT);
    val->append("\n");


}

QString FileHandler::getListenPort()
{
    return mlistenPort;
}

QString FileHandler::getRemotePort()
{
    return mremotePort;
}

QString FileHandler::getFileTransferPort()
{
    return mfileTransferPort;
}

QString FileHandler::getListenAddress()
{
    return mlistenAddress;
}

QString FileHandler::getRemoteAddress()
{
    return mremoteAddress;
}



/**
<Retrieve fileinfo for ftp previous transfered files>

<Retrieve fileinfo for ftp previous transfered files.>
<They are saved as pair on line with filename and timedate in seconds since years 70>
<as uint64. Local file is INFO_FILE>

@param  Pointer to the QStringList to be filled.
@return 0 Data not present.
@return 1 Data present.
@return -1 Error.
*/

int FileHandler::getFileInfo(QStringList *infolist)
{
    QFileInfo fileinfo = QFileInfo(INFO_FILE);
    QString info;

    if (!fileinfo.exists())
    {
        return 0;

    }

    QFile file(INFO_FILE);
    if (!file.open(QFile::ReadOnly ))
    {
        qDebug() << "Error opening File" << INFO_FILE;
        return -1;
    }


    QTextStream in(&file);
    while (!in.atEnd()) {
      info = in.readAll();

    }

    *infolist = info.split('\n');
    file.close();

    return 0;
}




/**
<Write info list in INFO_FILE>

<Write info list in INFO_FILE as pair filename and timedate expressed in seconds>
<since years 70>


@param  QStringList to save.
@return 0 Data saved.
@return 1 Error.
*/

int FileHandler::writeFileInfo(QStringList infolist)
{

    QFile file(INFO_FILE);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        qDebug() << "Error writing file " << INFO_FILE;
        return -1;
    }

    QTextStream datastream(&file);
    datastream << &infolist;
    file.flush();
    file.close();

    return 0;
}



