#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
extern bool loopFlag;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
    thread = new QThread(this);

}

MainWindow::~MainWindow()
{
//    thread->quit();
//    thread->wait();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(thread->isRunning()){
        QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("当前程序正在测试中，请测试完再尝试!"),\
                             QMessageBox::Ok);
        return;
    }
    loopFlag = true;
    subthread = new SubThread;
    subthread->moveToThread(thread);
    connect(subthread,&SubThread::slol1EndSignal,thread,&QThread::quit);
    connect(subthread,&SubThread::slol1EndSignal,this,&MainWindow::button1OK);
    connect(thread,&QThread::finished,subthread,&SubThread::deleteLater);
    connect(this,&MainWindow::thread1Lunch,subthread,&SubThread::slot1);
    thread->start();
    emit thread1Lunch();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->progressBar->reset();
    if(thread->isRunning()){
        QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("当前程序正在测试中，请测试完再尝试!"),\
                             QMessageBox::Ok);
        return;
    }
    subthread = new SubThread;
    subthread->moveToThread(thread);
    connect(thread,&QThread::finished,subthread,&SubThread::deleteLater);
    connect(subthread,&SubThread::slot2EndSignal,thread,&QThread::quit);
    connect(subthread,&SubThread::slot2EndSignal,this,&MainWindow::button2OK);
    connect(subthread,&SubThread::progressBarSignal,this,&MainWindow::dealProgressBar);
    connect(this,&MainWindow::thread2Lunch,subthread,&SubThread::slot2);
    thread->start();
    emit thread2Lunch();
}

void MainWindow::button1OK(){
    //ui->pushButton_2->setEnabled(true);
    qDebug() << "finished";
}

void MainWindow::button2OK(TData data){
    savedata = data;
    qDebug() << savedata.id;
    qDebug() << "finished";
}
void MainWindow::dealProgressBar(int num){
    ui->progressBar->setValue(num);
    if(ui->progressBar->value() == 19){
        QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("测试结束"),\
                             QMessageBox::Ok);
    }
}
