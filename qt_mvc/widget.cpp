#include "widget.h"
#include "ui_widget.h"
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QMessagebox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mymode = new MyModel(this);
    mydelegate = new MyDelegate(this);
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setModel(mymode);
    ui->tableView->setItemDelegateForColumn(0,mydelegate);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QItemSelectionModel* selection = ui->tableView->selectionModel();

    //返回的是每一个item，不是行
//    QModelIndexList selected = selection->selectedIndexes();
//    for(int i = 0;i < selected.size();++i){
//        mymode->insertRows(selected[i].row(),1);
//    }
    QModelIndex selected = selection->currentIndex();
    mymode->insertRows(selected.row(),1);
}


void Widget::on_pushButton_2_clicked()
{
    QItemSelectionModel* selection = ui->tableView->selectionModel();
    QModelIndex selected = selection->currentIndex();
    QString temp = QString("确定要删除第%1行？").arg(selected.row() + 1);
    int ret = QMessageBox::question(this,"提示",temp,\
                                    QMessageBox::Yes,QMessageBox::No);
    if(ret == QMessageBox::No){
        return;
    }

    mymode->removeRows(selected.row(),1);


}

void Widget::on_tableView_clicked(const QModelIndex &index)
{
//    delete mymode2;
//    delete mydelegate2;
    if(index.row() == 1){
        mymode2 = new MyModel;
        mydelegate2 = new MyDelegate;
        ui->tableView2->setModel(mymode2);
        ui->tableView2->setItemDelegateForColumn(0,mydelegate2);
        return;
    }
    mymode2
}
