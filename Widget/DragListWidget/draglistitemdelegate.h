#ifndef LISTITEMDELEGATE_H
#define LISTITEMDELEGATE_H

#include <QtWidgets/qabstractitemdelegate.h>

class DragListItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    DragListItemDelegate(QObject *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // LISTITEMDELEGATE_H
