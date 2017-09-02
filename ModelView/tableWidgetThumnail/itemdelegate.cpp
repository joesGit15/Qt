#include "itemdelegate.h"

#include <QtGui/QPainter>
#include <QtCore/QEvent>

ThumnailItemDelegate::ThumnailItemDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

void ThumnailItemDelegate::paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    if(!index.isValid()){
        return;
    }

    QRect itemRect = option.rect;
    painter->setOpacity(0.5);
    painter->fillRect(itemRect,Qt::gray);
    painter->setOpacity(1);

    QPixmap pix = index.data(Qt::UserRole).value<QPixmap>();
    int x = (itemRect.width()  - pix.width() )/2;
    int y = (itemRect.height() - pix.height())/2;
    painter->drawPixmap(itemRect.x()+x,itemRect.y()+y,pix);
}

CheckedItemDelegate::CheckedItemDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

void CheckedItemDelegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    if(!index.isValid()){
        return;
    }

    int x,y;
    QPixmap pix;
    QString path;
    QRect itemRect = option.rect;

    bool checked = index.data(Qt::UserRole).toBool();
    if(checked){
        path = ":/png/imgs/check_yes.png";
    }else{
        path = ":/png/imgs/check_no.png";
    }

    if(pix.load(path)){
        x = (itemRect.width()  - pix.width() )/2;
        y = (itemRect.height() - pix.height())/2;
        painter->drawPixmap(itemRect.x()+x,itemRect.y()+y,pix);
    }
}

bool CheckedItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index)
{
    (void)option;

    if(QEvent::MouseButtonRelease == event->type()){
        bool checked = index.data(Qt::UserRole).toBool();
        model->setData(index,!checked,Qt::UserRole);
        return true;
    }
    return false;
}
