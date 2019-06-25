#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QItemDelegate>
#include <QWidget>

class MyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit MyDelegate(QObject *parent = nullptr);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, \
                            const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, \
                            const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,\
                            const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, \
                            const QModelIndex &index) const;
signals:

public slots:
};

#endif // MYDELEGATE_H
