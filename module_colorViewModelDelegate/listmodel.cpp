#include "listmodel.h"

#include <QtCore/QVariant>

#include <QtGui/QColor>
#include <QtCore/QDebug>

ListModel::ListModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return _ltColor.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    if(index.row() >= _ltColor.size()){
        return QVariant();
    }

    if(Qt::UserRole == role){
        return QVariant::fromValue(_ltColor.at(index.row()));
    }else{
        return QVariant();
    }
}

Qt::ItemFlags ListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid()){
        return Qt::ItemIsEnabled;
    }

    //return Qt::ItemIsSelectable;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && Qt::UserRole == role){
        _ltColor.replace(index.row(),value.value<Color>());
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

bool ListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    (void)parent;
    beginInsertRows(QModelIndex(),row,row+count-1);

    for(int i=0; i<count; i++){
        Color clo;
        _ltColor.insert(row,clo);
    }
    endInsertRows();
    return true;
}

bool ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    (void)parent;
    beginRemoveRows(QModelIndex(),row,row+count-1);

    for(int i=0; i < count; i++){
        _ltColor.removeAt(row);
    }
    endRemoveRows();
    return true;
}
