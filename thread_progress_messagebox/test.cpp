#include "test.h"

test::test(QObject *parent) : QThread(parent)
{

}

void test::run(){
    qDebug() << currentThreadId();
}
