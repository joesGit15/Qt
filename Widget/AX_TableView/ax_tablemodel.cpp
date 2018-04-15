#include "ax_tablemodel.h"

AX_TableModel::AX_TableModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    _header << tr("First") << tr("Second") << tr("Three") << tr("Four") << tr("Five");
}

int AX_TableModel::rowCount(const QModelIndex &parent) const
{
    return _table.size();
}

int AX_TableModel::columnCount(const QModelIndex &parent) const
{
    (void)parent;

    int column = _header.size();
    return column;
}

bool AX_TableModel::setHeaderData(int section, Qt::Orientation orientation,
                                  const QVariant &value, int role)
{
    if(Qt::Horizontal == orientation){
        if(Qt::DisplayRole == role){
            (void)section; (void)value;
            /** you can set header label at here */
            return true;
        }
    }
    return false;
}

QVariant AX_TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant var;
    if(Qt::Horizontal == orientation){
        if(Qt::DisplayRole == role){
            if(section >= 0 && section < _header.size()){
                var = _header.at(section);
            }
        }
    }
    return var;
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
