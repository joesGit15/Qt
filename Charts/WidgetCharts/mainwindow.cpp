#include "mainwindow.h"

#include "areaseries.h"
#include "barchart.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtablewidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTabWidget* tab = new QTabWidget(this);
    setCentralWidget(tab);

    AreaSeries* areaSeries = new AreaSeries(this);
    BarChart* barChart = new BarChart(this);

    tab->addTab(areaSeries,areaSeries->objectName());
    tab->addTab(barChart,barChart->objectName());
}

MainWindow::~MainWindow()
{

}
