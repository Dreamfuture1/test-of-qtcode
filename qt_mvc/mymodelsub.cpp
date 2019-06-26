#include "mymodelsub.h"
#include <QDebug>
#include <QColor>


MyModelSub::MyModelSub(QObject *parent) : QAbstractTableModel(parent)
{
    headH << "国家" << "地级市" << "县级市";

}

void MyModelSub::initData(Data *data){
    dataSave = data;
}

int MyModelSub::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return dataSave->subdata.size();
}
int MyModelSub::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 3;
}
QVariant MyModelSub::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    if(index.row() < 0 || index.row() > dataSave->subdata.size() ||\
            index.column() < 0 || index.column() > 3){
        return QVariant();
    }
    //每一个item有很多项role，在data函数调用时会自动去加载，如果设定了去设置这个role才会设置
    switch(role){
    case Qt::BackgroundRole:
        //qDebug() << "red";
        if(index.column() == 2){
            return QColor(Qt::red);
        }
        break;
    case Qt::TextColorRole:
        //qDebug() << "yellow";
        if(index.column() == 2){
            return QColor(Qt::yellow);
        }
        break;
    case Qt::DisplayRole:
    case Qt::EditRole:
        return dataSave->subdata[index.row()].getData(index.column());
        break;
    default:
        break;
    }
    return QVariant();
}
QVariant MyModelSub::headerData(int section, Qt::Orientation orientation, \
                             int role) const{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return headH[section];
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

Qt::ItemFlags MyModelSub::flags(const QModelIndex &index) const{
    if(!index.isValid()){//如果模型的索引无效
        return 0;
    }
    if(index.column() == 1){
        return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
bool MyModelSub::setData(const QModelIndex &index, \
                      const QVariant &value, int role){
    if(index.isValid() && role == Qt::EditRole){
        QString temp = value.toString();
        dataSave->subdata[index.row()].setData(index.column(),temp);
        emit dataChanged(index,index);
        return true;
    }
    return false;
}
//row是要插入的第一行的行号，count是插入的数量
bool MyModelSub::insertRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(),row,row + count - 1);//row是要插入的第一行的行号，count是最后一行的行号

    DataSub temp;
    dataSave->subdata.insert(row,count,temp);
    endInsertRows();
    return true;
}

//same
bool MyModelSub::removeRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(),row,row + count - 1);
    dataSave->subdata.remove(row,count);
    endRemoveRows();
    return true;
}

