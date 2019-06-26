#include "widget.h"
#include "ui_widget.h"
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QMessagebox>
#include <QDebug>

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
    mydelegate2 = new MyDelegate(this);
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
    DataSub sssub("中国","上海","闵行");
    temp3.subdata.append(sssub);
    DataSub sssub2("中国","上海","外滩");
    temp3.subdata.append(sssub2);
    DataSub sssub3("中国","上海","松江");
    temp3.subdata.append(sssub3);
    mainData.data.append(temp3);

    Data temp4("李","4","四");
    DataSub ssssub("中国","四川","成都");
    temp4.subdata.append(ssssub);
    DataSub ssssub2("中国","四川","绵阳");
    temp4.subdata.append(ssssub2);
    DataSub ssssub3("中国","四川","九寨沟");
    temp4.subdata.append(ssssub3);
    mainData.data.append(temp4);
}

void Widget::on_pushButton_clicked()
{
    QItemSelectionModel* selection = ui->tableView->selectionModel();

    //返回的是每一个item，不是行，可以添加index.coloumn == 0之类来筛选
//    QModelIndexList selected = selection->selectedIndexes();
//    for(int i = 0;i < selected.size();++i){
//        mymode->insertRows(selected[i].row(),1);
//    }
    QModelIndex selected = selection->currentIndex();
    mymode->insertRows(selected.row(),1);
    mainData.eachData();
}


void Widget::on_pushButton_2_clicked()
{
    QItemSelectionModel* selection = ui->tableView->selectionModel();
    QModelIndex selected = selection->currentIndex();
    qDebug() << "3 row:" << selected.row();
    QString temp = QString("确定要删除第%1行？").arg(selected.row() + 1);
    int ret = QMessageBox::question(this,"提示",temp,\
                                    QMessageBox::Yes,QMessageBox::No);
    if(ret == QMessageBox::No){
        return;
    }

    mymode->removeRows(selected.row(),1);
    //mainData.eachData();

}

void Widget::on_tableView_clicked(const QModelIndex &index)
{
    qDebug() << "clicked";
    ui->tableView2->setModel(model);//必须用一个空的model去刷新一下view，否则只有在点击view的时候才会刷新
                                    //猜测是view设置原有的model，不会触发改变的信号，所以不会刷新
    mymode2->initData(&(mainData.data[index.row()]));
    ui->tableView2->setModel(mymode2);
}

void Widget::on_insert2l_clicked()
{
     QItemSelectionModel* selection = ui->tableView->selectionModel();
     QModelIndex selected = selection->currentIndex();
     mymode2->initData(&(mainData.data[selected.row()]));
     qDebug() << "1 row:" << selected.row();

     selection = ui->tableView2->selectionModel();
     if(selection == NULL){
         QMessageBox::warning(this,"提示","请先选择遥信表行",\
                                             QMessageBox::Ok);
         return;
     }
     selected = selection->currentIndex();
     if(selected.row() < 0){
         mymode2->insertRows(0,1);
     }else{
         mymode2->insertRows(selected.row(),1);
     }
     qDebug() << "2 row:" << selected.row();
     mainData.eachData();

}

void Widget::on_del2_clicked()
{
    QItemSelectionModel* selection = ui->tableView2->selectionModel();
    if(selection == NULL){
        QMessageBox::warning(this,"提示","删除无效！",\
                                            QMessageBox::Ok);
        return;
    }
    QModelIndex selected = selection->currentIndex();
    QString temp;
    int row = -1;
    if(selected.row() < 0){
        temp = QString("确定要删除第%1行？").arg(1);
        row = 0;
    }else{
        temp = QString("确定要删除第%1行？").arg(selected.row() + 1);
        row = selected.row();
    }

    int ret = QMessageBox::question(this,"提示",temp,\
                                    QMessageBox::Yes,QMessageBox::No);
    if(ret == QMessageBox::No){
        return;
    }

    mymode2->removeRows(row,1);
    mainData.eachData();

}
