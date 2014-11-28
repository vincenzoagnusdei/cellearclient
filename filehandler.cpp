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


FileHandler::FileHandler()
{
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
        qDebug() << "Error opening Parameter File";
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


}
