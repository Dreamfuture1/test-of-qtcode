#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(500,500);
    QDesktopWidget* desk = QApplication::desktop();
    QRect rec = desk->availableGeometry();
    QPoint po = rec.center();
    move(po);

    //move(500,500);
    connect(this,&MainWindow::windowMove,&te,&Test::moveslot);
    connect(this,&MainWindow::windowClose,&te,&Test::closeSlot);
    connect(this,&MainWindow::currentSize,&te,&Test::resizeSlot);
    te.show();
    showMinimized();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e){
    qDebug() << "paint";
}

void MainWindow::moveEvent(QMoveEvent *e){

    int wd = width();
    qDebug() << "width:" << width();
    qDebug() << "main" << pos() << "wd" << wd;
    emit windowMove(pos(),wd);
    QMainWindow::moveEvent(e);
    return;
}
void MainWindow::closeEvent(QCloseEvent *event){
    emit windowClose();
    event->accept();
    return;
}
void MainWindow::resizeEvent(QResizeEvent *event){
    emit currentSize(event->size());
    QMainWindow::resizeEvent(event);
    return;
}
