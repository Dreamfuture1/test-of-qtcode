#ifndef SUBTHREAD_H
#define SUBTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QVector>
#include <QMap>
struct TData{
    TData():id(-1),stationid(-1){}
    long id;
    union{
        struct{//馈线表
            long stationid;//厂站id
        };
        struct{//开关站表//配网终端信息表
            long feerderid;//馈线id
        };
        struct{//开关表
            long feer_of_switch;//开关表中的馈线id
            long combineid;//开关站id
        };

    };
};

class SubThread : public QObject
{
    Q_OBJECT
public:
    explicit SubThread(QObject *parent = nullptr);
    ~SubThread();

signals:
    void slol1EndSignal();
    void slot2EndSignal(TData);
    void progressBarSignal(int);

public slots:
    void slot1();
    void slot2();
private:
    TData savedata;
};

#endif // SUBTHREAD_H
