#include "coloritemdelegate.h"

#include <QtGui/QPainter>

ColorItemDelegate::ColorItemDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

void ColorItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    if(!index.isValid()){
        return;
    }

    QColor clo = index.data(Qt::DisplayRole).value<QColor>();
    painter->fillRect(option.rect,clo);
}
