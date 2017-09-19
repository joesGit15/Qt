#include "mainwindow.h"
#include "DatabaseConnect.h"

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QHeaderView>

#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setDockNestingEnabled(true);

    _tabWidget = new QTabWidget(this);
    setCentralWidget(_tabWidget);

    QDockWidget* dock = 0;
    dock = new QDockWidget(tr("Database"),this);
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    DatabaseConnect* DBConnect = new DatabaseConnect(this);
    dock->setWidget(DBConnect);
    _ltDocks.append(dock); ///< use the DockIdx::Main to get

    dock = new QDockWidget(tr("Info"),this);
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    _ltDocks.append(dock); ///< use the DockIdx::Info to get

    _info = new QTextEdit(this);
    _info->setReadOnly(true);
    dock->setWidget(_info);

    addDockWidget(Qt::TopDockWidgetArea,_ltDocks[DockIdx::Main]);
    splitDockWidget(_ltDocks[DockIdx::Main],_ltDocks[DockIdx::Info],Qt::Horizontal);

    _tbvDesc = new QTableView(this);
    _tbvData = new QTableView(this);

    SetTableViewDefaultOpts(_tbvDesc);
    SetTableViewDefaultOpts(_tbvData);

    _tbvDesc->setModel(DBConnect->TableDescModel());
    _tbvData->setModel(DBConnect->TableDataModel());

    _tabWidget->addTab(_tbvDesc,tr("Table Desc"));
    _tabWidget->addTab(_tbvData,tr("Table Data"));

    connect(DBConnect,&DatabaseConnect::SigError,
            this,&MainWindow::StDatabaseConnectError);
    connect(DBConnect,&DatabaseConnect::SigInfo,
            this,&MainWindow::StDatabaseConnectInfo);
}

void MainWindow::showEvent(QShowEvent *event)
{
    (void)event;
    int w = width();
    QList<int> size;
    size.append(int(w*0.6));
    size.append(int(w*0.4));
    resizeDocks(_ltDocks,size,Qt::Horizontal);

    int h = height();
    size.clear();
    size.append(int(h*0.2));
    size.append(int(h*0.2));
    resizeDocks(_ltDocks,size,Qt::Vertical);
}

void MainWindow::StDatabaseConnectError(const QString &error)
{
    _info->append(error);
}

void MainWindow::StDatabaseConnectInfo(const QString &info)
{
    _info->append(info);
}

void MainWindow::SetTableViewDefaultOpts(QTableView *tbv)
{
    QHeaderView* header;
    tbv->setSelectionBehavior(QTableView::SelectRows);
    header = tbv->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);
    header->setStretchLastSection(true);
}
