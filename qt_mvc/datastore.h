#ifndef DATASTORE_H
#define DATASTORE_H

#include <QVector>
#include <QString>

class DataSub
{
public:
    DataSub();
    DataSub(QString fi,QString se,QString th);
    QString getData(const int&num);
    void setData(const int&num,const QString& data);
public:
    QString first;
    QString second;
    QString third;
};

class Data
{
public:
    Data();
    Data(QString na,QString ph,QString ag);
    QString getData(const int&num);
    void setData(const int&num,const QString& data);
public:
    QString name;
    QString phone;
    QString age;
    QVector<DataSub> subdata;

};

class DataStore
{
public:
    DataStore();
    void eachData();

public:
    QVector<Data> data;
};

#endif // DATASTORE_H
