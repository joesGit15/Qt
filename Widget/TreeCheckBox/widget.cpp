#include "widget.h"
#include "treeview.h"
#include "treewidget.h"

#include <QtWidgets/QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    TreeView*   treeView   = new TreeView(this);
    TreeWidget* treeWidget = new TreeWidget(this);

    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addWidget(treeView);
    hlyt->addWidget(treeWidget);
    setLayout(hlyt);
}

Widget::~Widget()
{

}
