#include <QString>
#include <QFileInfo>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QDir>
#include "datasensorparser.h"
#include "filehandler.h"



const QString DataSensorParser::LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_A = "logmintempthXa.txt";
const QString DataSensorParser::LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_B = "logmintempthXb.txt";
const QString DataSensorParser::LOG_MIN_HUMIDITY_TH_CROSSED_FILE_A = "logminhumhXa.txt";
const QString DataSensorParser::LOG_MIN_HUMIDITY_TH_CROSSED_FILE_B = "logminhumhXb.txt";
const QString DataSensorParser::LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_A = "logminlumXa.txt";
const QString DataSensorParser::LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_B = "logminhumhXb.txt";

const QString DataSensorParser::LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_A = "logmaxtempthXa.txt";
const QString DataSensorParser::LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_B = "logmaxtempthXb.txt";
const QString DataSensorParser::LOG_MAX_HUMIDITY_TH_CROSSED_FILE_A = "logmaxhumhXa.txt";
const QString DataSensorParser::LOG_MAX_HUMIDITY_TH_CROSSED_FILE_B = "logmaxhumhXb.txt";
const QString DataSensorParser::LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_A = "logmaxlumXa.txt";
const QString DataSensorParser::LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_B = "logmaxhumhXb.txt";


const QString DataSensorParser::LOG_TEMPERATURE_CURRENT_VALUE_FILE_A = "logcurrvaltempa.txt";
const QString DataSensorParser::LOG_TEMPERATURE_CURRENT_VALUE_FILE_B = "logcurrvaltempa.txt";
const QString DataSensorParser::LOG_HUMIDITY_CURRENT_VALUE_FILE_A = "logcurrvalhuma.txt";
const QString DataSensorParser::LOG_HUMIDITY_CURRENT_VALUE_FILE_B = "logcurrvalhumb.txt";
const QString DataSensorParser::LOG_LUMINOSITY_CURRENT_VALUE_FILE_A = "logcurrvalluma.txt";
const QString DataSensorParser::LOG_LUMINOSITY_CURRENT_VALUE_FILE_B = "logcurrvallumb.txt";

DataSensorParser::DataSensorParser(QObject *parent) :
    QObject(parent)
{

    QString filename =  this->getFileNameMeasure(temperature_min_th);

    if (this->readSamples(filename))
    {
        // value retrieved
    }

   // filename.clear();
   // filename.append(this->getFileNameMeasure(temperature_max_th));

   // if (this->readSamples(filename))
   // {
        // value retrieved
   // }



}


DataSensorParser::~DataSensorParser()
{

}


QString DataSensorParser::getFileNameMeasure(measure_type_enum meastype)
{

    QFileInfo qfinfoa;
    QFileInfo qfinfob;
    QString filename = NULL;    

    switch(meastype)
    {

        case temperature_min_th:

            qfinfoa = QFileInfo(LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_A);
            qfinfob = QFileInfo(LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_B);

         break;

        case temperature_max_th:

            qfinfoa = QFileInfo(LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_A);
            qfinfob = QFileInfo(LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_B);

         break;

        case temperature_val:
            qfinfoa = QFileInfo(LOG_TEMPERATURE_CURRENT_VALUE_FILE_A);
            qfinfob = QFileInfo(LOG_TEMPERATURE_CURRENT_VALUE_FILE_B);

        break;

        case humidity_min_th:

            qfinfoa = QFileInfo(LOG_MIN_HUMIDITY_TH_CROSSED_FILE_A);
            qfinfob = QFileInfo(LOG_MIN_HUMIDITY_TH_CROSSED_FILE_B);

        break;

        case humidity_max_th:

            qfinfoa = QFileInfo(LOG_MAX_HUMIDITY_TH_CROSSED_FILE_A);
            qfinfob = QFileInfo(LOG_MAX_HUMIDITY_TH_CROSSED_FILE_B);

        break;


        case humidity_val:

            qfinfoa = QFileInfo(LOG_HUMIDITY_CURRENT_VALUE_FILE_A);
            qfinfob = QFileInfo(LOG_HUMIDITY_CURRENT_VALUE_FILE_B);

        break;

        case luminosity_min_th:

            qfinfoa = QFileInfo(LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_A);
            qfinfob = QFileInfo(LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_A);

        break;

        case luminosity_max_th:

            qfinfoa = QFileInfo(LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_A);
            qfinfob = QFileInfo(LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_A);

        break;

        case luminosity_val:

            qfinfoa = QFileInfo(LOG_LUMINOSITY_CURRENT_VALUE_FILE_A);
            qfinfob = QFileInfo(LOG_LUMINOSITY_CURRENT_VALUE_FILE_B);

        break;

        default:

            qDebug() << "measure type";



     }


    if (qfinfoa.exists())
    {

        if (qfinfob.exists())
        {

             if (qfinfoa.lastModified() > qfinfob.lastModified())
             {
                 filename=qfinfob.fileName();
             }
             else
             {
                 filename=qfinfoa.fileName();

             }

         }
        else
        {
            filename=qfinfoa.fileName();
        }
     }



    return filename;

}



int DataSensorParser::readSamples(QString filename)
{
    QString data;
    QStringList datetime;
    QStringList values;
    Measure *pmeasure;
    QString th1;


    QFile file(filename);
    if (!file.open(QFile::ReadOnly ))
    {
        qDebug() << "Error opening Parameter File";
        return -1;
    }


    // read one threhsold out of the loop
    // to reduce the time spent in the loop
    // and classify each value to know
    // if the value crossed min or max th


    QTextStream in(&file);
    data = in.readLine();
    if (data.size() > 0)
    {



        while (!in.atEnd()) {
          data = in.readLine();
          values.clear();
          values = data.split(FileHandler::SEPARATOR);
          datetime = values.at(datetime_token).split(FileHandler::SEPARATOR1);
          pmeasure = new Measure();
          pmeasure->setDate(datetime.at(datetime_token));
          pmeasure->setTime(datetime.at(time_position));
          pmeasure->setValue(values.at(value_token));
          pmeasure->setSensor(values.at(sensor_token));
          pmeasure->setThreshold(values.at(threshold_token));
          if (values.at(threshold_token).compare(th1) == 0)
          {
              pmeasure->setIsThreshold1();
          }

          mMeasures.append(pmeasure);


        }
    }

    file.close();

    return 0;

}


QList<Measure *> * DataSensorParser::getMeasureList()
{
    return &mMeasures;

}
