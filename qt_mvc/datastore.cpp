#include "datastore.h"

DataSub::DataSub(){}
DataSub::DataSub(QString fi,QString se,QString th){
    first = fi;
    second = se;
    third = th;
}
QString DataSub::getData(const int&num){
    switch(num){
    case 0:
        return first;
        break;
    case 1:
        return second;
        break;
    case 2:
        return third;
        break;
    default:
        break;
    }
    return QString();
}
void DataSub::setData(const int&num,const QString& data){
    switch(num){
    case 0:
        first = data;
        break;
    case 1:
        second = data;
        break;
    case 2:
        third = data;
        break;
    default:
        break;
    }
}

Data::Data(){}
Data::Data(QString na,QString ph,QString ag){
    name = na;
    phone = ph;
    age = ag;
}

QString Data::getData(const int&num){
    switch(num){
    case 0:
        return name;
        break;
    case 1:
        return phone;
        break;
    case 2:
        return age;
        break;
    default:
        break;
    }
    return QString();
}
void Data::setData(const int&num,const QString& data){
    switch(num){
    case 0:
        name = data;
        break;
    case 1:
        phone = data;
        break;
    case 2:
        age = data;
        break;
    default:
        break;
    }
}
DataStore::DataStore(){}
