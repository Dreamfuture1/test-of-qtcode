#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QCloseEvent>
#include <QSize>
namespace Ui {
class Test;
}

class Test : public QWidget
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = 0);
    ~Test();
public slots:
    void moveslot(QPoint data,int);
    void closeSlot();
    void resizeSlot(QSize);
private:
    Ui::Test *ui;
};

#endif // TEST_H
