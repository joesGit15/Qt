#ifndef LISTITEMDELEGATE_H
#define LISTITEMDELEGATE_H

#include <QtWidgets/QAbstractItemDelegate>

class ListItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    ListItemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // LISTITEMDELEGATE_H
