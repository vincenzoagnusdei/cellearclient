#ifndef DATASENSORPARSER_H
#define DATASENSORPARSER_H

#include <QObject>
#include <QStringList>
#include "measure.h"

class DataSensorParser : public QObject
{
    Q_OBJECT
public:
    explicit DataSensorParser(QObject *parent = 0);
    ~DataSensorParser();
    QList<Measure *> * getMeasureList();

private:

    enum measure_type_enum {humidity_min_th, humidity_max_th,  humidity_val, temperature_min_th, temperature_max_th,
                            temperature_val, luminosity_min_th, luminosity_max_th, luminosity_val };

    enum field_enum {datetime_token,  value_token, threshold_token, sensor_token  };
    static const int time_position =1;

    static const QString LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_A;
    static const QString LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_B;
    static const QString LOG_MIN_HUMIDITY_TH_CROSSED_FILE_A;
    static const QString LOG_MIN_HUMIDITY_TH_CROSSED_FILE_B;
    static const QString LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_A;
    static const QString LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_B;

    static const QString LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_A;
    static const QString LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_B;
    static const QString LOG_MAX_HUMIDITY_TH_CROSSED_FILE_A;
    static const QString LOG_MAX_HUMIDITY_TH_CROSSED_FILE_B;
    static const QString LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_A;
    static const QString LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_B;


    static const QString LOG_TEMPERATURE_CURRENT_VALUE_FILE_A;
    static const QString LOG_TEMPERATURE_CURRENT_VALUE_FILE_B;
    static const QString LOG_HUMIDITY_CURRENT_VALUE_FILE_A;
    static const QString LOG_HUMIDITY_CURRENT_VALUE_FILE_B;
    static const QString LOG_LUMINOSITY_CURRENT_VALUE_FILE_A;
    static const QString LOG_LUMINOSITY_CURRENT_VALUE_FILE_B;

    QList<Measure *> mMeasures;
    QStringList mInitialDate;
    QStringList mFinalDate;

    QString getFileNameMeasure(measure_type_enum meastype);
    int readSamples(QString filename);



signals:

public slots:

};

#endif // DATASENSORPARSER_H
