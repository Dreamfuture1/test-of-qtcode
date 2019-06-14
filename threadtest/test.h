#ifndef TEST_H
#define TEST_H

#include <QThread>
#include <QDebug>
class test : public QThread
{
    Q_OBJECT
public:
    explicit test(QObject *parent = nullptr);

signals:

public slots:
    void run();
};

#endif // TEST_H
