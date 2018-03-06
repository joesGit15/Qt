#ifndef AX_STYLEITEMDELEGATE_H
#define AX_STYLEITEMDELEGATE_H

#include <QtWidgets/qstyleditemdelegate.h>

struct CellDt{
    int  val = 20;
    bool checked = false;
    bool radio   = false;  ///< false means first radio, true mean second radio
};

Q_DECLARE_METATYPE(CellDt)

class AX_StyleitemDelegate : public QStyledItemDelegate
{
public:
    AX_StyleitemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

/**  */

class AX_FirstitemDelegate : public QStyledItemDelegate
{
public:
    AX_FirstitemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // AX_STYLEITEMDELEGATE_H
