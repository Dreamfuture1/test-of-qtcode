#include "mymodel.h"
#include <QDebug>
#include <QColor>
MyModel::MyModel(QObject *parent) : QAbstractTableModel(parent)
{
    headH << "姓名" << "电话" << "日期";
    initData("赵","1","一");
    initData("钱","2","二");
    initData("孙","3","三");
    initData("李","4","四");
    connect(this,&MyModel::dataChanged,this,&MyModel::changed);
}

void MyModel::initData(QString name,QString phone,QString date){
    QVector<QString> temp;
    temp.push_back(name);
    temp.push_back(phone);
    temp.push_back(date);
    dataSave.push_back(temp);
}
void MyModel::changed(QModelIndex index1,QModelIndex index2){
    //showData();
}
void MyModel::showData(){
    int row = dataSave.size();

    for(int i = 0;i < row;++i){
        qDebug() << dataSave[i][0] << " " << dataSave[i][1] << " " << dataSave[i][2] << " ";
    }
}

int MyModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return dataSave.size();
}
int MyModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return dataSave[0].size();
}
QVariant MyModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    if(index.row() < 0 || index.row() > dataSave.size() ||\
            index.column() < 0 || index.column() > dataSave[0].size()){
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
        return dataSave[index.row()][index.column()];
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
//    if(index.column() == 1){
//        return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//    }
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
bool MyModel::setData(const QModelIndex &index, \
                      const QVariant &value, int role){
    if(index.isValid() && role == Qt::EditRole){
        dataSave[index.row()][index.column()] = value.toString();
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
    QVector<QString> temp;
    temp.resize(3);
    dataSave.insert(row,count,temp);
    endInsertRows();
    return true;
}

//same
bool MyModel::removeRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(),row,row + count - 1);
    dataSave.remove(row,count);
    endRemoveRows();
    return true;
}

