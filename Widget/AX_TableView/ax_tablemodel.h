#ifndef AX_TABLEMODEL_H
#define AX_TABLEMODEL_H

#include <QtCore/qvector.h>
#include <QtCore/qabstractitemmodel.h>

#include "ax_styleitemdelegate.h"

typedef QVector<CellDt> Row;

class AX_TableModel : public QAbstractTableModel
{
public:
    AX_TableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QVariant data(const QModelIndex &index, int role) const;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QVector<Row> _table;
    QStringList  _header;
};

#endif // AX_TABLEMODEL_H
