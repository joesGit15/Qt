#include "dialog.h"
#include "checkboxheaderview.h"
#include "tablemodel.h"

#include <QtWidgets/qlabel.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtablewidget.h>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    /** QTableWidget init*/
    QTableWidget* tableWidget = new QTableWidget(this);
    //table->setStyleSheet("border: 0px solid black;");
    /** show grid lines */
    tableWidget->setColumnCount(5);
    tableWidget->setShowGrid(true);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* header;
    header = new CheckBoxHeaderView(1,Qt::Horizontal,tableWidget);
    //connect(header,&CheckBoxHeaderView::SigCheckStatusChanged)
    tableWidget->setHorizontalHeader(header);
    /** must set these after set header */
    header = tableWidget->horizontalHeader();
    header->setStretchLastSection(true);
    header->setFont(QFont("song",12));
    header->setDefaultSectionSize(100);

    /** TableView init */
    QTableView* tableView = new QTableView(this);
    tableView->setModel(new TableModel(this));
    header = new CheckBoxHeaderView(1,Qt::Horizontal,tableView);
    tableView->setHorizontalHeader(header);

    /** layout TableWidget */
    QVBoxLayout* vlytTableWidget = new QVBoxLayout;
    vlytTableWidget->addWidget(new QLabel("TableWidget",this));
    vlytTableWidget->addWidget(tableWidget);

    /** layout TableView */
    QVBoxLayout* vlytTableView = new QVBoxLayout;
    vlytTableView->addWidget(new QLabel("TableView",this));
    vlytTableView->addWidget(tableView);

    /** layout all */
    QHBoxLayout* hlyt = new QHBoxLayout;
    hlyt->addLayout(vlytTableWidget);
    hlyt->addLayout(vlytTableView);
    setLayout(hlyt);
}

Dialog::~Dialog()
{

}
