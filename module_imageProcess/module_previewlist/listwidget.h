#ifndef LISTWIDGET_H
#define LISTWIDGET_H
#include <QListWidget>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class ListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ListWidget(QWidget *parent = 0);

    void AppendItem(QListWidgetItem* item);

signals:
    void SigFinishedDrag(QList<QListWidgetItem *> ltDragItems );

protected:
    /** OverRide */
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;

private:
    /**
     * Drag Drop 过程中, 此变量的引用, 是为了解决, 拖拽过程中,
     * 会触发itemSelectionChanged信号, 造成@see ClearSelection()的发生,
     * 此变量在 @see ClearSelection() 中. 起到了一定的控制作用.
     */
    bool _bDraging     = false;

    /**
     * 在Drag and drop event. 如果使用dataStream存储item数据, 如果数据发生变化,
     * 则需要调整这一块儿,所以, 不采用dataStream, 而是通过一个成员变量, 纪录一下
     * drag 的item 指针. 在drop以后,使用item的clone函数. 要方便一些.
    */
    QListWidgetItem *_pDragItem = 0;
};

#endif // LISTWIDGET_H
