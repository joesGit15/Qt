#ifndef STYLEDITEMDELEGATE_H
#define STYLEDITEMDELEGATE_H
#include <QStyledItemDelegate>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class StyledItemDelegate : public QStyledItemDelegate
{
public:
    explicit StyledItemDelegate(QObject * parent = 0);
    ~StyledItemDelegate();

private:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // STYLEDITEMDELEGATE_H
