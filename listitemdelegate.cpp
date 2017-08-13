#include "listitemdelegate.h"
#include "listmodel.h"

#include <QtGui/QPainter>
#include <QtCore/QDebug>

ListItemDelegate::ListItemDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{

}

void ListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid()){
        return;
    }

    QColor color;
    Color clo = index.data(Qt::UserRole).value<Color>();
    if(option.state & QStyle::State_HasFocus){
        color = QColor(clo.r,clo.g,clo.b,200);
    }else{
        color = QColor(clo.r,clo.g,clo.b,100);
    }
    painter->fillRect(option.rect,color);

    QRect ellipseRect = option.rect;
    ellipseRect.setWidth(ellipseRect.height());
    painter->drawEllipse(ellipseRect);
}

QSize ListItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    (void)option;
    (void)index;
    return QSize(10,50);
}
