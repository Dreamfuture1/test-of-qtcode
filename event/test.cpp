#include "test.h"
#include "ui_test.h"
#include <QDebug>
Test::Test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | \
                   Qt::WindowMinimizeButtonHint);
    setFixedSize(this->width(),this->height());
}

Test::~Test()
{
    delete ui;
}
void Test::moveslot(QPoint data,int wd){

    QPoint po;
    po.setX(data.x() - this->width());
    po.setY(data.y());
    if(po.x() <= 0){
        po.setX(data.x() + wd);
        po.setY(data.y());
    }
    qDebug() << "sub" << pos() << "wd:" << wd;
    move(po);
}

void Test::closeSlot(){
    qDebug() << "close2";
    close();
}
void Test::resizeSlot(QSize size){

    int hei = size.height();
    setFixedSize(500,hei);
}
