#include "customtablemodel.h"

#include <QtCore/qvector.h>
#include <QtCore/qdatetime.h>

#include <QtGui/qcolor.h>

CustomTableModel::CustomTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    _columnCount = 6;
    _rowCount = 12;

    for (int i = 0; i < _rowCount; i++) {
        QVector<qreal>* dataVec = new QVector<qreal>(_columnCount);
        for (int k = 0; k < dataVec->size(); k++) {
            if (k % 2 == 0)
                dataVec->replace(k, i * 50 + qrand() % 20);
            else
                dataVec->replace(k, qrand() % 100);
        }
        _data.append(dataVec);
    }
}

CustomTableModel::~CustomTableModel()
{
    qDeleteAll(_data);
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return _data.count();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    (void)parent;
    return _columnCount;
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("201%1").arg(section);
    else
        return QString("%1").arg(section + 1);
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return _data[index.row()]->at(index.column());
    } else if (role == Qt::EditRole) {
        return _data[index.row()]->at(index.column());
    } else if (role == Qt::BackgroundRole) {
        QRect rect;
        foreach (rect, _mapping)
        if (rect.contains(index.column(), index.row()))
            return QColor(_mapping.key(rect));

        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        _data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void CustomTableModel::addMapping(QString color, QRect area)
{
    _mapping.insertMulti(color, area);
}
