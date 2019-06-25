#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mymodel.h"
#include "mymodelsub.h"
#include "mydelegate.h"
#include "datastore.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void initData();
private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;

    DataStore mainData;

    MyModel* mymode;
    MyDelegate* mydelegate;
    MyModelSub* mymode2;
    MyDelegate* mydelegate2;
    TableModel* model;
};

#endif // WIDGET_H
