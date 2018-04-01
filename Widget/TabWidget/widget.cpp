#include "widget.h"
#include "customtabstyle.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtabwidget.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qlabel.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label;
    QComboBox* cbox;
    QHBoxLayout* hlyt = new QHBoxLayout;

    label = new QLabel(tr("QTabWidget::TabPosition"),this);
    cbox = new QComboBox(this);
    cbox->addItem(tr("North"),QVariant(QTabWidget::North));
    cbox->addItem(tr("South"),QVariant(QTabWidget::South));
    cbox->addItem(tr("West"),QVariant(QTabWidget::West));
    cbox->addItem(tr("East"),QVariant(QTabWidget::East));
    connect(cbox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(StTabPositionChanged(int)));
    hlyt->addWidget(label);
    hlyt->addWidget(cbox);
    hlyt->addStretch(1);

    label = new QLabel(tr("QTabBar::Shape"),this);
    cbox = new QComboBox(this);
    cbox->addItem(tr("RoundedNorth"),QVariant(QTabBar::RoundedNorth));
    cbox->addItem(tr("RoundedSouth"),QVariant(QTabBar::RoundedSouth));
    cbox->addItem(tr("RoundedWest"),QVariant(QTabBar::RoundedWest));
    cbox->addItem(tr("RoundedEast"),QVariant(QTabBar::RoundedEast));
    cbox->addItem(tr("TriangularNorth"),QVariant(QTabBar::TriangularNorth));
    cbox->addItem(tr("TriangularSouth"),QVariant(QTabBar::TriangularSouth));
    cbox->addItem(tr("TriangularWest"),QVariant(QTabBar::TriangularWest));
    cbox->addItem(tr("TriangularEast"),QVariant(QTabBar::TriangularEast));
    connect(cbox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(StTabShapeChanged(int)));

    hlyt->addWidget(label);
    hlyt->addWidget(cbox);
    hlyt->addStretch(1);

    _tab =new QTabWidget(this);
    QTabWidget* tab = _tab;

    tab->addTab(new QWidget(this),tr("Tab &A"));
    tab->addTab(new QWidget(this),tr("Tab &B"));
    tab->addTab(new QWidget(this),tr("Tab &C"));

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addLayout(hlyt);
    vlyt->addWidget(tab);

    tab =new QTabWidget(this);
    tab->setTabPosition(QTabWidget::East);
    tab->addTab(new QWidget(this),tr("Tab &A"));
    tab->addTab(new QWidget(this),tr("Tab &B"));
    tab->addTab(new QWidget(this),tr("Tab &C"));
    _style = new CustomTabStyle(QTabBar::RoundedNorth);
    tab->tabBar()->setStyle(_style);
    vlyt->addWidget(tab);

    setLayout(vlyt);
}

Widget::~Widget()
{
    delete _style;
}

void Widget::StTabShapeChanged(int index)
{
    QObject* obj = sender();
    QComboBox* cbox = qobject_cast<QComboBox*>(obj);
    QTabBar::Shape shape = cbox->itemData(index).value<QTabBar::Shape>();
    _tab->tabBar()->setShape(shape);
}

void Widget::StTabPositionChanged(int index)
{
    QObject* obj = sender();
    QComboBox* cbox = qobject_cast<QComboBox*>(obj);
    QTabWidget::TabPosition position = cbox->itemData(index).value<QTabWidget::TabPosition>();
    _tab->setTabPosition(position);
}
