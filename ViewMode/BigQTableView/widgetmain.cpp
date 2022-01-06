#include "widgetmain.h"
#include "tablemode.h"
#include <QtWidgets>

static TableMode* tableMode = nullptr;

WidgetMain::WidgetMain(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* vlyt = new QVBoxLayout();
    QPushButton* btnAddColum = new QPushButton(tr("add"));
    QTableView* tableView = new QTableView();

    vlyt->addWidget(btnAddColum);
    vlyt->addWidget(tableView,1);
    setLayout(vlyt);

    tableMode = new TableMode(this);
    tableView->setModel(tableMode);

    connect(btnAddColum,&QPushButton::clicked,this,&WidgetMain::stAddBtnClicked);
}

WidgetMain::~WidgetMain()
{

}

void WidgetMain::stAddBtnClicked()
{
    tableMode->insertColumn(0);
}
