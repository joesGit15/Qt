#pragma once

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
public:
    TableModel(QObject *parent = 0);

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    QStringList  _headersText;
};
