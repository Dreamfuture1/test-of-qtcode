#include "subthread.h"
#include <QMetaType>
extern bool loopFlag;
SubThread::SubThread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<TData>("TData");
}
SubThread::~SubThread(){
    qDebug() << "sub delete";
}

void SubThread::slot1(){
    while(loopFlag){
        QThread::sleep(1);
        qDebug() << QThread::currentThreadId();
        loopFlag = false;
        emit slol1EndSignal();

        //QThread::sleep(10);
    }

}

void SubThread::slot2(){
    qDebug() << QThread::currentThreadId();
    qDebug() << "slot2";
//    for(int i = 0;i < 20;++i){
//        QThread::sleep(1);
//        emit progressBarSignal(i);
//    }
    savedata.id = 10000;
    emit slot2EndSignal(savedata);

}
