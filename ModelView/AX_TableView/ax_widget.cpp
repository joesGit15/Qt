#include "ax_widget.h"
#include "ax_tablemodel.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qheaderview.h>

#include <QtCore/qtimer.h>

#include <QtCore/qdebug.h>

#define MAX_ROW 50

AX_Widget::AX_Widget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* hlyt = new QHBoxLayout;
    QTableView* view = new QTableView(this);
    _view = view;
    hlyt->addWidget(view);
    setLayout(hlyt);

    //view->setMouseTracking(true);
    view->setModel(new AX_TableModel(this));
    view->setItemDelegate(new AX_StyleitemDelegate(this));
#if 1
    for(int i=0; i < 10; i++){
        addRow();
    }
#else
    QTimer* t = new QTimer(this);
    t->setInterval(1000);
    connect(t,&QTimer::timeout,this,&AX_Widget::addRow);
    t->start();
#endif
}

AX_Widget::~AX_Widget()
{

}

void AX_Widget::addRow()
{
    AX_TableModel* model = 0;
    model = (AX_TableModel*)(_view->model());
    QTableView* view = _view;

    int row,i;
    row = model->rowCount();
    model->insertRows(row,1);
    view->setRowHeight(row,60);

    for(i=0; i<model->columnCount(); i++){
        view->setColumnWidth(i,150);
    }

    if(sender() == 0){
        return;
    }

    QTimer* t = qobject_cast<QTimer*>(sender());
    if(row > MAX_ROW){
        t->stop();
    }
}
