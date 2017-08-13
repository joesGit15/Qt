#include "listitemdelegate.h"
#include "listmodel.h"

#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>

#include <QtCore/QDebug>

#define CalShapeRect(srcRect,dstRect,nOffGrid) {\
    (dstRect) = (srcRect); \
    (dstRect).setX((srcRect).width()-(nOffGrid)*(srcRect).height()); \
    (dstRect).setWidth((dstRect).height()); \
    (dstRect) = (dstRect).marginsAdded(QMargins(-10,-10,-10,-10)); \
}

ListItemDelegate::ListItemDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{

}

/**
    ///< don't forget to set view mouse tracking
    if(option.state & QStyle::State_MouseOver)
    if(option.state & QStyle::State_HasFocus)
*/
void ListItemDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    QRect itemRect = option.rect;
    if(!index.isValid()){
        return;
    }

    Color clo = index.data(Qt::UserRole).value<Color>();
    QColor color;

    if(option.state & QStyle::State_Selected){
        color = QColor(clo.r,clo.g,clo.b,255);
    }else{
        color = QColor(clo.r,clo.g,clo.b,200);
    }
    painter->fillRect(itemRect,color);

    QRect shapeRect;
    CalShapeRect(itemRect,shapeRect,1);
    painter->drawImage(shapeRect,QImage(":/png/imgs/delete_32.png"));
    CalShapeRect(itemRect,shapeRect,2);
    painter->drawImage(shapeRect,QImage(":/png/imgs/edit_32.png"));
}

QSize ListItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    (void)option;
    (void)index;
    return QSize(10,50);
}


bool ListItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index)
{
    (void)model;
    (void)index;

    if(QEvent::MouseButtonRelease == event->type()){
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        QRect shapeRect;
        CalShapeRect(option.rect,shapeRect,1);
        if(shapeRect.contains(mouseEvent->pos())){
            model->removeRow(index.row());
            return true;
        }

        CalShapeRect(option.rect,shapeRect,2);
        if(shapeRect.contains(mouseEvent->pos())){
            qDebug("Edit...%d",index.row());
            return true;
        }
    }
    return false;
}
