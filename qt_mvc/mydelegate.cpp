#include "mydelegate.h"
#include <QRegExp>
#include <QLineEdit>
MyDelegate::MyDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget* MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, \
                        const QModelIndex &index) const{
    QLineEdit *editor =  new  QLineEdit(parent);
    QRegExp regExp( "[0-9]{0,10}" );
    editor->setValidator( new  QRegExpValidator(regExp, parent));
    return  editor;
}
void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
    lineEdit->setText(text);
}
void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, \
                        const QModelIndex &index) const{
    QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
    QString text = lineEdit->text();
    model->setData(index, text, Qt::EditRole);

}
void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,\
                        const QModelIndex &index) const{
    editor->setGeometry(option.rect);
}
