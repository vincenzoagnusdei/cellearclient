#ifndef MEASURE_H
#define MEASURE_H
#include <QString>

class Measure
{
public:
    Measure();
    ~Measure();
    QString getDate();
    void setDate(QString date);
    QString getTime();
    void setTime(QString time);
    QString getThrehsold();
    void setThreshold(QString th);
    QString getValue();
    void setValue(QString val);
    QString getSensor();
    void setSensor(QString sensor);
    void setIsThreshold1();
    bool isThreshold1();



private:
    QString mDate;
    QString mTime;
    QString mThreshold;
    QString mValue;
    QString mSensor;
    bool mIsThreshold1;

};

#endif // MEASURE_H
