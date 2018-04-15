#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    _headersText << "1" << "2" << "3" << "4" << "5";
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return 5;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return _headersText.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    QVariant var;

    if(Qt::CheckStateRole == role && index.column() == 0){
        //var = index.data(Qt::CheckStateRole);
        if(index.row() % 2 == 0){
            var = Qt::Checked;
        }else{
            var = Qt::Unchecked;
        }
    }

    if(Qt::DisplayRole == role){
        var = QString("Cell");
    }

    return var;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant var;
    if(Qt::Horizontal == orientation){
        if(Qt::DisplayRole == role){
            var = _headersText.at(section);
        }
    }
    return var;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    if(index.column() == 0){
        flags |= Qt::ItemIsUserCheckable;
    }else{
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}
