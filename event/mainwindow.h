#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "test.h"

#include <QMainWindow>
#include <QPaintEvent>
#include <QMoveEvent>
#include <QEvent>
#include <QPoint>
#include <QSize>
#include <QCloseEvent>
#include <QDialog>
#include <QResizeEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
    void moveEvent(QMoveEvent *event);
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
    //void changeEvent(QEvent *e);
    //bool event(QEvent *event);
signals:
    void windowMove(QPoint,int);
    void currentSize(QSize);
    void windowClose();
    void windowMax();
    void windowMin();
private:
    Ui::MainWindow *ui;
    Test te;

};

#endif // MAINWINDOW_H
