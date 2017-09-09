#include "treeview.h"

#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

TreeView::TreeView(QWidget *parent)
    :QTreeView(parent)
{
    int row=0,columns = 1;
    _model = new QStandardItemModel(row,columns,this);
    setModel(_model);

    QStringList headerlabels;
    headerlabels << tr("TreeView");
    _model->setHorizontalHeaderLabels(headerlabels);

    connect(_model,&QStandardItemModel::itemChanged,
            this,&TreeView::StItemChanged);

    InitData();
}

TreeView::~TreeView()
{
}

bool TreeView::CheckedEmpty()
{
    Qt::CheckState state;
    QStandardItem* topItem=0;

    topItem = _model->item(0,0);
    state = topItem->checkState();
    if(Qt::Unchecked == state){
        return true;
    }else{
        return false;
    }
}

void TreeView::StItemChanged(QStandardItem *item)
{
    Q_ASSERT(0 != item);
    disconnect(_model,&QStandardItemModel::itemChanged,
            this,&TreeView::StItemChanged);

    Qt::CheckState state;
    state = item->checkState();
    if(item->isTristate()){
        if(Qt::Checked == state){
            SetChildenCheck(item,true);
        }else if(Qt::Unchecked == state){
            SetChildenCheck(item,false);
        }
    }

    SetParentState(item);

    connect(_model,&QStandardItemModel::itemChanged,
            this,&TreeView::StItemChanged);
}

void TreeView::InitData()
{
    QStandardItem* item,* subitem,* topItem,* lastitem;

    topItem = new QStandardItem(tr("Top"));
    topItem->setCheckable(true);
    topItem->setTristate(true);
    topItem->setEditable(false);
    _model->appendRow(topItem);

    for(int i=0; i < 2; i++){
        item = new QStandardItem(tr("item %1").arg(i));
        item->setCheckable(true);
        item->setTristate(true);
        item->setEditable(false);
        topItem->appendRow(item);

        for(int j=0; j < 2; j++){
            subitem = new QStandardItem(tr("subitem %1").arg(j));
            subitem->setCheckable(true);
            subitem->setTristate(true);
            subitem->setEditable(false);
            item->appendRow(subitem);

            for(int k=0; k < 3; k++){
                lastitem = new QStandardItem(tr("lastitem %1").arg(k));
                lastitem->setCheckable(true);
                lastitem->setEditable(false);
                subitem->appendRow(lastitem);
            }
        }
    }

    expandAll();
}

void TreeView::SetChildenCheck(QStandardItem *parent, bool checked)
{
    Q_ASSERT(0 != parent);
    int i,count;
    QStandardItem* item = 0;

    count = parent->rowCount();
    for(i=0; i<count; ++i){
        item = parent->child(i);
        SetChildenCheck(item,checked);
    }

    if(parent->isCheckable()){
        parent->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
    }
}

void TreeView::SetParentState(QStandardItem *child)
{
    Q_ASSERT(0 != child);

    Qt::CheckState siblingState = CheckSiblingsState(child);
    QStandardItem * parentItem = child->parent();
    if(0 == parentItem){
        return;
    }

    if(!parentItem->isCheckable()){
        return;
    }

    parentItem->setCheckState(siblingState);
    SetParentState(parentItem);
}

Qt::CheckState TreeView::CheckSiblingsState(QStandardItem *item)
{
    Qt::CheckState state;
    int brotherCount,nCheck,nUnCheck,i;
    QStandardItem * parent;
    QStandardItem * sibling;

    parent = item->parent();
    if(0 == parent){
        return item->checkState();
    }

    nCheck = nUnCheck = 0;
    brotherCount = parent->rowCount();
    for(i=0; i < brotherCount; ++i){
        sibling = parent->child(i);
        state = sibling->checkState();
        if(Qt::PartiallyChecked == state){
            return Qt::PartiallyChecked;
        }else if(Qt::Unchecked == state){
            ++nUnCheck;
        }else{
            ++nCheck;
        }

        if(nCheck > 0 && nUnCheck > 0){
            return Qt::PartiallyChecked;
        }
    }

    if(nUnCheck > 0){
        return Qt::Unchecked;
    }

    return Qt::Checked;
}
