#include "measure.h"
#include <QDebug>

Measure::Measure():
mIsThreshold1(false)
{
}

Measure::~Measure()
{
    qDebug() << "destroyed measure";
}

QString Measure::getDate(){
    return mDate;
}

void Measure::setDate(QString date)
{
    mDate = date;
}

QString Measure::getTime()
{
    return mTime;
}

void Measure::setTime(QString time)
{
    mTime=time;
}

QString Measure::getThrehsold()
{
    return mThreshold;
}

void Measure::setThreshold(QString th)
{
    mThreshold=th;
}

QString Measure::getValue()
{
    return mValue;
}

void Measure::setValue(QString val)
{
    mValue=val;

}

QString Measure::getSensor()
{
    return mSensor;
}

void Measure::setSensor(QString sensor)
{
    mSensor=sensor;
}


void Measure::setIsThreshold1()
{
    mIsThreshold1=true;
}


bool Measure::isThreshold1()
{
    return mIsThreshold1;
}
