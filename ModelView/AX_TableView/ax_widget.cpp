#include "ax_widget.h"
#include "ax_tablemodel.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qheaderview.h>

#include <QtCore/qtimer.h>

#define MAX_ROW 50

AX_Widget::AX_Widget(QWidget *parent)
    : QWidget(parent)
{
    int i;

    QHBoxLayout* hlyt = new QHBoxLayout;
    QTableView* view = new QTableView(this);
    hlyt->addWidget(view);
    setLayout(hlyt);

    _view = view;

    AX_TableModel* model = new AX_TableModel(this);
    view->setModel(model);

    /**  */
    view->setItemDelegateForColumn(0,new AX_FirstitemDelegate(this));
    AX_StyleitemDelegate* delegate = new AX_StyleitemDelegate(this);
    for(i = 1; i < model->columnCount(); i++){
        view->setItemDelegateForColumn(i,delegate);
    }

    QTimer* t = new QTimer(this);
    t->setInterval(1000);
    connect(t,&QTimer::timeout,this,&AX_Widget::addRow);
    t->start();
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
        view->setColumnWidth(i,200);
    }

    if(sender() == 0){
        return;
    }

    QTimer* t = qobject_cast<QTimer*>(sender());
    if(row > MAX_ROW){
        t->stop();
    }
}
