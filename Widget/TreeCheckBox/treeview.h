#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE
class QStandardItem;
class QStandardItemModel;
QT_END_NAMESPACE

class TreeView : public QTreeView
{
    Q_OBJECT

public:
    TreeView(QWidget* parent = 0);
    ~TreeView();

    bool CheckedEmpty();

private slots:
    void StItemChanged(QStandardItem* item);

private:
    void InitData();

    void SetChildenCheck(QStandardItem* parent,bool checked);
    void SetParentState(QStandardItem* child);
    Qt::CheckState CheckSiblingsState(QStandardItem* item);

private:
    QStandardItemModel*                 _model = 0;
};

#endif // TREEVIEW_H
