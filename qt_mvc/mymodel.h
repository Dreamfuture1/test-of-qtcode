#ifndef MYMODEL_H
#define MYMODEL_H
#include "datastore.h"

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QStringList>
#include <QVector>

class TableModel:public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr);
    //重写函数
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &, int) const;

    Qt::ItemFlags flags(const QModelIndex &) const;
    bool setData(const QModelIndex &, const QVariant &, int);
};


class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = nullptr);
    //重写函数
    int rowCount(const QModelIndex &parent) const;//重写返回行
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
signals:

public slots:
public:
    void initData(DataStore* data);
private:
    DataStore* dataSave;
    QStringList headH;
};

#endif // MYMODEL_H
