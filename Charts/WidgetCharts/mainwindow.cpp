#include "mainwindow.h"

#include "areaSeries/areaseries.h"
#include "barChart/barchart.h"
#include "callOut/calloutview.h"
#include "chartInteractions/interactionwidget.h"
#include "chartThemes/themewidget.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtablewidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTabWidget* tab = new QTabWidget(this);
    setCentralWidget(tab);

    QWidget *widget = 0;

    widget = new AreaSeries(this);
    tab->addTab(widget,widget->objectName());

    widget = new BarChart(this);
    tab->addTab(widget,widget->objectName());

    widget = new CallOutView(this);
    tab->addTab(widget,widget->objectName());

    widget = new tInteractionsWidget(this);
    tab->addTab(widget,widget->objectName());

    widget = new ThemeWidget(this);
    tab->addTab(widget,widget->objectName());
}

MainWindow::~MainWindow()
{

}
