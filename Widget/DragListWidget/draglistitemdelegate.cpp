#include "draglistitemdelegate.h"

#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>

DragListItemDelegate::DragListItemDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{

}

void DragListItemDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if(!index.isValid()){
        return;
    }

    int r = index.data(Qt::UserRole+1).toInt();
    int g = index.data(Qt::UserRole+2).toInt();
    int b = index.data(Qt::UserRole+3).toInt();
    QColor color = QColor(r,g,b,200);
    painter->fillRect(option.rect,color);

    QString text = index.data(Qt::DisplayRole).toString();
    painter->drawText(option.rect,Qt::AlignCenter,text);
}

QSize DragListItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    (void)option;
    (void)index;
    return QSize(10,50);
}
