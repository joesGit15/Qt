#ifndef CHARTCUSTOMTABLEMODEL_H
#define CHARTCUSTOMTABLEMODEL_H

#include <QtCore/QAbstractTableModel>

#include <QtCore/qhash.h>
#include <QtCore/qrect.h>

class ChartTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ChartTableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void addMapping(QString color, QRect area);
    void clearMapping() { _mapping.clear(); }

private:
    QList<QVector<qreal> * > _data;
    QHash<QString, QRect> _mapping;
    int _columnCount;
    int _rowCount;
};

#endif // CHARTCUSTOMTABLEMODEL_H
