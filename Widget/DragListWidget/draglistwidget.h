#ifndef DRAGLISTWIDGET_H
#define DRAGLISTWIDGET_H

#include <QtWidgets/qlistwidget.h>

class DragListWidget : public QListWidget
{
public:
    DragListWidget(QWidget *parent = 0);

    void appendDragSourceObjName(const QString &objName);

protected:
    void dropEvent(QDropEvent *event) override;

private:
    QStringList     _dragSources;
};

#endif // DRAGLISTWIDGET_H
