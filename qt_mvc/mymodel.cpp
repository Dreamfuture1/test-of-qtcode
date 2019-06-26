#include "mymodel.h"
#include <QDebug>
#include <QColor>

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent){}

int TableModel::rowCount(const QModelIndex &) const{
    return 0;
}
int TableModel::columnCount(const QModelIndex &) const{
    return 0;
}
QVariant TableModel::data(const QModelIndex &, int ) const{return QVariant();}

Qt::ItemFlags TableModel::flags(const QModelIndex &) const{return 0;}
bool TableModel::setData(const QModelIndex &, \
                         const QVariant &, int ){return false;}

MyModel::MyModel(QObject *parent) : QAbstractTableModel(parent)
{
    headH << "姓名" << "电话" << "年龄";

}

void MyModel::initData(DataStore *data){
    dataSave = data;
}

int MyModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return dataSave->data.size();
}
int MyModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 3;
}
QVariant MyModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    if(index.row() < 0 || index.row() > dataSave->data.size() ||\
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
        return dataSave->data[index.row()].getData(index.column());
        break;
    default:
        break;
    }
    return QVariant();
}
QVariant MyModel::headerData(int section, Qt::Orientation orientation, \
                             int role) const{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return headH[section];
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const{
    if(!index.isValid()){//如果模型的索引无效
        return 0;
    }
    if(index.column() == 1){
        return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
bool MyModel::setData(const QModelIndex &index, \
                      const QVariant &value, int role){
    if(index.isValid() && role == Qt::EditRole){
        QString temp = value.toString();
        dataSave->data[index.row()].setData(index.column(),temp);
        emit dataChanged(index,index);
        return true;
    }
    return false;
}
//row是要插入的第一行的行号，count是插入的数量
bool MyModel::insertRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(),row,row + count - 1);//row是要插入的第一行的行号，count是最后一行的行号
//    for(int i = 0;i < count;++i){
//        QVector<QString> temp;
//        temp.resize(3);
//        dataSave.insert(row,temp);
//    }
    Data temp;
    dataSave->data.insert(row,count,temp);
    endInsertRows();
    return true;
}

//same
bool MyModel::removeRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(),row,row + count - 1);
    dataSave->data.remove(row,count);
    endRemoveRows();
    return true;
}

