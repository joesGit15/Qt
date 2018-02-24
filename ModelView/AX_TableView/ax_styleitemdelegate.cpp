#include "ax_styleitemdelegate.h"

#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>

#include <QtCore/qdebug.h>

AX_StyleitemDelegate::AX_StyleitemDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

void AX_StyleitemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //QStyledItemDelegate::paint(painter,option,index);

    QVariant var = index.data(Qt::UserRole);
    CellDt dt = var.value<CellDt>();
    int val = dt.val;

    QRect processbarRect = option.rect;
    processbarRect.adjust(5,20,-5,-20);
    painter->setPen(Qt::blue);
    painter->drawRect(processbarRect);

    int process = processbarRect.width()* val/100.0;
    processbarRect.adjust(0,0,-(processbarRect.width() - process),0);
    painter->fillRect(processbarRect,Qt::blue);
}

bool AX_StyleitemDelegate::editorEvent(QEvent *event,
                                       QAbstractItemModel *model,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index)
{
    QMouseEvent* mouseEvent = 0;

    if(QEvent::MouseButtonPress == event->type()){
        return true;
    }

    if(QEvent::MouseButtonRelease == event->type()){
        return true;
    }

    if(QEvent::MouseMove == event->type()){
        mouseEvent = static_cast<QMouseEvent*>(event);
        int x = mouseEvent->x();

        QRect processbarRect = option.rect;
        processbarRect.adjust(5,20,-5,-20);
        QVariant var = index.data(Qt::UserRole);
        CellDt dt = var.value<CellDt>();
        dt.val = x - processbarRect.x();

        var.setValue(dt);
        model->setData(index,var,Qt::UserRole);
        return true;
    }

    return false;
}
