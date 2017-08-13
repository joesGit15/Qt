#include "widget.h"
#include "listmodel.h"
#include "listitemdelegate.h"

#include <QtWidgets/QListView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>

#include <QtGui/QScreen>

#include <QtCore/QTime>
#include <QtCore/QDebug>

Widget::Widget(QWidget *parent)
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
    connect(btnAdd,&QPushButton::clicked,this,&Widget::StAddOneRandomItem);

    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addWidget(btnAdd);
    hlyt->addStretch(1);

    _tabWidget = new QTabWidget(this);
    _tabWidget->addTab(_ltView,tr("ListView"));

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addWidget(_tabWidget,1);
    vlyt->addLayout(hlyt);

    setLayout(vlyt);

    srand(QTime::currentTime().msec());
}

Widget::~Widget()
{

}

void Widget::showEvent(QShowEvent *)
{
    QSize s = QApplication::primaryScreen()->size();
    int w = s.width() * 0.5;
    int h = s.height() * 0.8;
    resize(w,h);
    int x = (s.width() - w)/2;
    int y = (s.height() - h)/2;
    move(x,y);
}

void Widget::StAddOneRandomItem()
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

}
