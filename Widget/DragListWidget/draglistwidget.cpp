#include "draglistwidget.h"

#include <QtCore/qmimedata.h>
#include <QtGui/qevent.h>

#include <QtCore/qdebug.h>

DragListWidget::DragListWidget(QWidget *parent)
{
    _dragSources.clear();
}

void DragListWidget::appendDragSourceObjName(const QString &objName)
{
    if(!_dragSources.contains(objName)){
        _dragSources.append(objName);
    }
}

void DragListWidget::dropEvent(QDropEvent *event)
{
    /** source QListWidget */
    QString objName = event->source()->objectName();
    if(_dragSources.contains(objName)){
        QListWidget::dropEvent(event);
    }
}
