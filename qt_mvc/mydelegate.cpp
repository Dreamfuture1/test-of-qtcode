#include "mydelegate.h"
#include <QRegExp>
#include <QLineEdit>
#include <QDebug>
#include <QComboBox>
#include <QPainter>
#include <QBrush>
MyDelegate::MyDelegate(QObject *parent) : QItemDelegate(parent)
{

}

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, \
                        const QModelIndex &index) const{
    QRect rect = option.rect; // 目标矩形
    rect.adjust(2, 2, -2, -2); // 缩小一圈，留出空白间隔
    //rect.adjust(0, 0, 0, 0);
    bool selected = false;
    //state的默认值为 QStyle::State_None.
    //选中时设置画笔和画刷，来绘制选中的item的形状和颜色
    if (option.state & QStyle::State_Selected){
       selected = true;
       //painter->setPen(Qt::DotLine);//定义了如何绘制线条和轮廓
       painter->setPen(QColor(120, 88,140));
       //设置画笔的填充，颜色，以及竖状填充，默认的是全部填充
       QBrush brush = QBrush(QColor(120, 88,140));
       //painter->setBrush(Qt::SolidPattern);
       //painter->setBrush(QColor(120, 88,140));
       painter->setBrush(brush);

       painter->drawRoundedRect(rect, 2, 2);//画矩形框
    }
    //返回索引引用的项的给定角色的数据
    int rowid = index.data(Qt::UserRole).toInt();
    if (rowid < 0){
       // 空条目
       qDebug() << "kong";
       painter->setBrush(Qt::NoBrush);
       painter->setPen(Qt::DotLine);
       painter->drawRect(rect);
       QRect dst = rect;
       dst.adjust(2, 2, -2, -2);
       if (selected){
           painter->setPen(QColor(0xCC, 0xCC,0xCC));
       }else{
           painter->setPen(QColor(0x99, 0x99,0x99));
       }
       painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter,"tt");
    }else{
       // 有意义的条目
       QString text = index.data(Qt::DisplayRole).toString();//返回要以文本显示的角色值
       QRect dst = rect;
       if (selected)
           painter->setPen(QColor(101, 199,147));
       else
           painter->setPen(QColor(176, 105,168));
       painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter, text);
    }
}

QWidget* MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, \
                        const QModelIndex &index) const{
//    qDebug() << "createEditor";
//    QLineEdit *editor =  new  QLineEdit(parent);
//    QRegExp regExp( "[0-9]{0,10}" );
//    editor->setValidator( new  QRegExpValidator(regExp, parent));
//    int row = index.row(),col = index.column();
//    QModelIndex temp = index.model()->index(row,--col);//根据row行col获取指定项的索引
//    QString text = temp.data().toString();
//    qDebug() << text;
    QComboBox *editor =  new  QComboBox(parent);
    editor->addItem( "Female" );
    editor->addItem( "Male" );
    return  editor;
}
void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
//    qDebug() << "setEditorData";
//    QString text = index.model()->data(index, Qt::EditRole).toString();
//    QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
//    lineEdit->setText(text);
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox =  static_cast <QComboBox*>(editor);
    int  tindex = comboBox->findText(text);
    comboBox->setCurrentIndex(tindex);

}
void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, \
                        const QModelIndex &index) const{
//    qDebug() << "setModelData";
//    QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
//    QString text = lineEdit->text();
//    model->setData(index, text, Qt::EditRole);
    QComboBox *comboBox =  static_cast <QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text, Qt::EditRole);

}
void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,\
                        const QModelIndex &index) const{
    qDebug() << "updateEditorGeometry";
    editor->setGeometry(option.rect);
}
