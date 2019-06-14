#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "subthread.h"
#include "test.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void thread1Lunch();
    void thread2Lunch();
public slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void button1OK();
    void button2OK();
    void dealProgressBar(int);
private:
    Ui::MainWindow *ui;
    QThread* thread;
    SubThread* subthread;
    test myth;
};

#endif // MAINWINDOW_H
