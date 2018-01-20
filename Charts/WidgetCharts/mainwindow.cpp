#include "mainwindow.h"

#include "areaseries.h"
#include "barchart.h"
#include "callOut/calloutview.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtablewidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTabWidget* tab = new QTabWidget(this);
    setCentralWidget(tab);

    AreaSeries* areaSeries = new AreaSeries(this);
    BarChart* barChart = new BarChart(this);
    CallOutView* view = new CallOutView(this);

    tab->addTab(areaSeries,areaSeries->objectName());
    tab->addTab(barChart,barChart->objectName());
    tab->addTab(view,view->objectName());
}

MainWindow::~MainWindow()
{

}
