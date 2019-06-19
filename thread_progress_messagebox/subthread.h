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
        struct{//���߱�
            long stationid;//��վid
        };
        struct{//����վ��//�����ն���Ϣ��
            long feerderid;//����id
        };
        struct{//���ر�
            long feer_of_switch;//���ر��е�����id
            long combineid;//����վid
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
