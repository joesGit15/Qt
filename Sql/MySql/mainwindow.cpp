#include "mainwindow.h"

#include <QtWidgets/QMdiArea>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setDockNestingEnabled(true);

    _mdiArea = new QMdiArea(this);
    setCentralWidget(_mdiArea);

    QDockWidget* dock = 0;
    dock = new QDockWidget(tr("Database"),this);
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    _ltDocks.append(dock); ///< use the DockIdx::Main to get

    dock = new QDockWidget(tr("Info"),this);
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    _ltDocks.append(dock); ///< use the DockIdx::Info to get

    _info = new QTextEdit(this);
    _info->setReadOnly(true);
    dock->setWidget(_info);

    addDockWidget(Qt::TopDockWidgetArea,_ltDocks[DockIdx::Main]);
    splitDockWidget(_ltDocks[DockIdx::Main],_ltDocks[DockIdx::Info],Qt::Horizontal);

#if 0
    /** put two widgets in tabs */
    addDockWidget(Qt::TopDockWidgetArea,dockWget);
    tabifyDockWidget(dockWget,dockWgetInfo);
#endif
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
