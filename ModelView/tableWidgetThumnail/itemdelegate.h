#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QtWidgets/QStyledItemDelegate>

class ThumnailItemDelegate : public QStyledItemDelegate
{
public:
    ThumnailItemDelegate(QObject* parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

class CheckedItemDelegate : public QStyledItemDelegate
{
public:
    CheckedItemDelegate(QObject* parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override;
};
#endif // ITEMDELEGATE_H
