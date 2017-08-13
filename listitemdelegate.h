#ifndef LISTITEMDELEGATE_H
#define LISTITEMDELEGATE_H

#include <QtWidgets/QAbstractItemDelegate>

class ListItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    ListItemDelegate(QObject *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // LISTITEMDELEGATE_H
