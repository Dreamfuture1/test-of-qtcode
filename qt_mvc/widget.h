#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mymodel.h"
#include "mydelegate.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    MyModel* mymode;
    MyDelegate* mydelegate;
    MyModel* mymode2;
    MyDelegate* mydelegate2;
};

#endif // WIDGET_H