#include "listwidget.h"

/** customsize */
#include "styleditemdelegate.h"

#include <QtCore/QMimeData>

#include <QtGui/QDrag>
#include <QtGui/QDragEnterEvent>

#define LIST_ITEM_FLAGS  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled
#define LIST_ITEM_SIZE   QSize(120,140)

ListWidget::ListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setSpacing(0);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setSelectionRectVisible(true);

    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    setItemDelegate(new StyledItemDelegate);
}

void ListWidget::AppendItem(QListWidgetItem *item)
{
    Q_ASSERT(0 != item);
    item->setFlags(LIST_ITEM_FLAGS);
    item->setSizeHint(LIST_ITEM_SIZE);
    addItem(item);
}


void ListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/list-item")){
        event->accept();
    }else{
        event->ignore();
    }
}

void ListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("image/list-item")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }else{
        event->ignore();
    }
}

void ListWidget::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasFormat("image/list-item")){
        QListWidgetItem *pPosItem = itemAt(event->pos());
        if(0 == _pDragItem || 0 == pPosItem){
            event->ignore();
            return;
        }

        QListWidgetItem *pItem = _pDragItem->clone();
        insertItem(row(pPosItem), pItem);
        event->setDropAction(Qt::MoveAction);
        _pDragItem = 0;
    }

    event->accept();
}

void ListWidget::startDrag(Qt::DropActions supportedActions)
{
    Q_UNUSED(supportedActions);
    QListWidgetItem *pItem = currentItem();
    if(0 == pItem || 0 != _pDragItem || count() <= 1){
        return;
    }

    clearSelection();

    QByteArray itemData;
    QMimeData *pMimeData =  new QMimeData;
    pMimeData->setData("image/list-item", itemData);

    QDrag *pDrag = new QDrag(this);
    pDrag->setMimeData(pMimeData);
    //drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    //drag->setPixmap(pixmap);

    _bDraging = true;
    _pDragItem = pItem;
    if (pDrag->exec(Qt::MoveAction) == Qt::MoveAction){
        delete takeItem(row(pItem));
    }
}
