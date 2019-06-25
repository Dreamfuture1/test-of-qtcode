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

    initData();
    mymode = new MyModel(this);
    mymode->initData(&mainData);
    mydelegate = new MyDelegate(this);
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setModel(mymode);
    ui->tableView->setItemDelegateForColumn(0,mydelegate);
    mymode2 = new MyModelSub(this);
    mymode2->initData(&(mainData.data[0]));
    mydelegate2 = new MyDelegate(this);
    ui->tableView2->setModel(mymode2);
    ui->tableView2->setItemDelegateForColumn(0,mydelegate2);
    model = new TableModel(this);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::initData(){
    Data temp("赵","1","一");
    DataSub sub("中国","江苏","南京");
    temp.subdata.append(sub);
    DataSub sub2("中国","江苏","常州");
    temp.subdata.append(sub2);
    DataSub sub3("中国","常州","溧阳");
    temp.subdata.append(sub3);
    mainData.data.append(temp);

    Data temp2("钱","2","二");
    DataSub ssub("中国","浙江","杭州");
    temp2.subdata.append(ssub);
    DataSub ssub2("中国","浙江","千岛湖");
    temp2.subdata.append(ssub2);
    DataSub ssub3("中国","浙江","宁波");
    temp2.subdata.append(ssub3);
    mainData.data.append(temp2);

    Data temp3("孙","3","三");
    DataSub sssub("中国","浙江","杭州");
    temp3.subdata.append(sssub);
    DataSub sssub2("中国","浙江","千岛湖");
    temp3.subdata.append(sssub2);
    DataSub sssub3("中国","浙江","宁波");
    temp3.subdata.append(sssub3);
    mainData.data.append(temp3);

    Data temp4("李","4","四");
    DataSub ssssub("中国","浙江","杭州");
    temp4.subdata.append(ssssub);
    DataSub ssssub2("中国","浙江","千岛湖");
    temp4.subdata.append(ssssub2);
    DataSub ssssub3("中国","浙江","宁波");
    temp4.subdata.append(ssssub3);
    mainData.data.append(temp4);
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

        ui->tableView2->setModel(mymode2);
        ui->tableView2->setItemDelegateForColumn(0,mydelegate2);
        return;
    }
    ui->tableView2->setModel(model);

}
