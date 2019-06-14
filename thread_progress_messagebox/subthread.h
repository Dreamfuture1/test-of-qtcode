#ifndef SUBTHREAD_H
#define SUBTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
class SubThread : public QObject
{
    Q_OBJECT
public:
    explicit SubThread(QObject *parent = nullptr);

signals:
    void slol1EndSignal();
    void slot2EndSignal();
    void progressBarSignal(int);

public slots:
    void slot1();
    void slot2();
};

#endif // SUBTHREAD_H
