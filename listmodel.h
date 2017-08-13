#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>

struct Color{
    int r = 0;
    int g = 0;
    int b = 0;
};

Q_DECLARE_METATYPE(Color)

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::UserRole);

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

private:
    QList<Color>  _ltColor;
};

#endif // STRINGLISTMODEL_H
