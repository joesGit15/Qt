#ifndef TABLEMODE_H
#define TABLEMODE_H

#include <QObject>
#include <QAbstractTableModel>

class TableMode : public QAbstractTableModel
{
public:
    TableMode(QObject *parent = Q_NULLPTR);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    int mColumCount = 0;
};

#endif // TABLEMODE_H
