#include "styleditemdelegate.h"

StyledItemDelegate::StyledItemDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

StyledItemDelegate::~StyledItemDelegate(){}

void StyledItemDelegate::paint(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    /** patent class virtual function at begin of the subclass,
     * it also can not have the dot line when the mouse select item. */
    QStyledItemDelegate::paint(painter, option, index);

    /** Step1: draw pixmap border */
#if 0
    if( option.state & QStyle::State_HasFocus )
        pen.setColor( QColor(65,105,255) );
    else if( option.state & QStyle::State_Selected )
        pen.setColor( QColor(100,150,255) );
    else if( option.state & QStyle::State_MouseOver )
        pen.setColor( QColor(100,200,255) );
    else
        pen.setColor( QColor(211,211,211) );
#endif
}
