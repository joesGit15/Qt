#include "colorlistviewwidget.h"
#include "listitemdelegate.h"
#include "listmodel.h"

#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

ColorListViewWidget::ColorListViewWidget(QWidget *parent)
    : QWidget(parent)
{
    ListItemDelegate* delegate = new ListItemDelegate(this);
    _ltView = new QListView(this);
    _ltView->setItemDelegate(delegate);
    _ltView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _ltView->setSelectionRectVisible(true);
    _ltView->setMouseTracking(true);

    _model = new ListModel(this);
    _ltView->setModel(_model);

    QPushButton* btnAdd = new QPushButton(tr("Add"),this);
    btnAdd->setAutoRepeat(true);
    btnAdd->setAutoRepeatInterval(100);
    connect(btnAdd,&QPushButton::clicked,
            this,&ColorListViewWidget::StAddOneRandomItem);

    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addWidget(btnAdd);
    hlyt->addStretch(1);

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addWidget(_ltView,1);
    vlyt->addLayout(hlyt);

    setLayout(vlyt);
}

void ColorListViewWidget::StAddOneRandomItem()
{
    int row;
    QModelIndex index;

    Color clo;
    clo.r = rand()%256;
    clo.g = rand()%256;
    clo.b = rand()%256;

    row = _model->rowCount(QModelIndex());
    _model->insertRow(row);
    index = _model->index(row);
    _model->setData(index,QVariant::fromValue(clo));

    _ltView->scrollToBottom();
}
