#include "charttablemodel.h"

#include <QtGui/qcolor.h>
#include <QtCore/qvector.h>
#include <QtCore/qdatetime.h>

ChartTableModel::ChartTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    _columnCount = 4;
    _rowCount = 15;

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

int ChartTableModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return _data.count();
}

int ChartTableModel::columnCount(const QModelIndex &parent) const
{
    (void)parent;
    return _columnCount;
}

QVariant ChartTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section % 2 == 0)
            return "x";
        else
            return "y";
    } else {
        return QString("%1").arg(section + 1);
    }
}

QVariant ChartTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return _data[index.row()]->at(index.column());
    } else if (role == Qt::EditRole) {
        return _data[index.row()]->at(index.column());
    } else if (role == Qt::BackgroundRole) {
        foreach (QRect rect, _mapping) {
            if (rect.contains(index.column(), index.row()))
                return QColor(_mapping.key(rect));
        }
        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

bool ChartTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        _data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags ChartTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void ChartTableModel::addMapping(QString color, QRect area)
{
    _mapping.insertMulti(color, area);
}
