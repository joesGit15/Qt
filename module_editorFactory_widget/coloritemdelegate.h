#ifndef COLORITEMDELEGATE_H
#define COLORITEMDELEGATE_H
#include <QtWidgets/QStyledItemDelegate>

class ColorItemDelegate : public QStyledItemDelegate
{
public:
    ColorItemDelegate(QObject* parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // COLORITEMDELEGATE_H
