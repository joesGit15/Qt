#include "tablemode.h"

TableMode::TableMode(QObject *parent)
    :QAbstractTableModel(parent)
{

}

QVariant TableMode::data(const QModelIndex &index, int role) const
{
    return QString("%1X%2").arg(index.row()).arg(index.column());
}

bool TableMode::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent,column,column + count);
    mColumCount++;
    endInsertColumns();
    return true;
}

bool TableMode::insertRows(int row, int count, const QModelIndex &parent)
{
}

QVariant TableMode::headerData(int section, Qt::Orientation orientation, int role) const
{
    return section;
}

int TableMode::columnCount(const QModelIndex &parent) const
{
    return mColumCount;
}

int TableMode::rowCount(const QModelIndex &parent) const
{
    return 10000000;
}
