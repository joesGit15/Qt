#include "ax_tablemodel.h"

AX_TableModel::AX_TableModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

int AX_TableModel::rowCount(const QModelIndex &parent) const
{
    return _table.size();
}

int AX_TableModel::columnCount(const QModelIndex &parent) const
{
    (void)parent;

    int column = 5;
#if 0
    if(_table.size() > 0){
        column = _table.first().size();
    }
#endif
    return column;
}

QVariant AX_TableModel::data(const QModelIndex &index, int role) const
{
    QVariant var;

    if(Qt::UserRole == role){
        CellDt dt;
        dt = _table.at(index.row()).at(index.column());
        var.setValue(dt);
    }

    return var;
}

bool AX_TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);

    for(int i=0; i < count; i++){
        Row rw;
        rw.resize(5);
        _table.insert(row+i,rw);
    }

    endInsertRows();
    return true;
}

bool AX_TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(Qt::UserRole == role){
        int row = index.row();
        int column = index.column();
        CellDt dt = _table.at(row).at(column);
        dt = value.value<CellDt>();
        _table[row][column] = dt;
    }

    return true;
}
