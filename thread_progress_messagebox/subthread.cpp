#include "subthread.h"

SubThread::SubThread(QObject *parent) : QObject(parent)
{

}
void SubThread::slot1(){
    qDebug() << QThread::currentThreadId();
    qDebug() << "slot1";
    emit slol1EndSignal();
    //QThread::sleep(100);
}

void SubThread::slot2(){
    qDebug() << QThread::currentThreadId();
    qDebug() << "slot2";
    for(int i = 0;i < 20;++i){
        QThread::sleep(1);
        emit progressBarSignal(i);
    }
    emit slot2EndSignal();

}
