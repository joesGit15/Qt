#include "mainwindow.h"

#include "areaSeries/areaseries.h"
#include "barChart/barchartwidget.h"
#include "callOut/calloutview.h"
#include "chartInteractions/interactionwidget.h"
#include "chartThemes/themewidget.h"
#include "customChart/customchartwidget.h"
#include "donutchart/donutchartwidget.h"
#include "donutbreakdown/donutbreakdownwidget.h"
#include "dynamicspline/dynamicsplinewidget.h"
#include "legend/legend.h"
#include "legendmarkers/legendmarkerswidget.h"
#include "logvalueaxis/logvalueaxis.h"
#include "multiaxis/multiaxis.h"
#include "openglseries/openglseries.h"

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

    widget = new BarChartWidget(this);
    tab->addTab(widget,widget->objectName());

    widget = new CallOutView(this);
    tab->addTab(widget,widget->objectName());

    widget = new tInteractionsWidget(this);
    tab->addTab(widget,widget->objectName());

    widget = new ThemeWidget(this);
    tab->addTab(widget,widget->objectName());

    widget = new CustomChartWidget(this);
    tab->addTab(widget,widget->objectName());

    widget = new DonutChartWidget(this);
    tab->addTab(widget,widget->objectName());

    widget = new DonutBreakDownWidget(this);
    tab->addTab(widget,widget->objectName());

    widget = new DynamicSplineWidget(this);
    tab->addTab(widget,widget->objectName());

    widget = new Legend(this);
    tab->addTab(widget,widget->objectName());

    widget = new LegendMarkersWidget(this);
    tab->addTab(widget,widget->objectName());

    widget = new LogValueAxis(this);
    tab->addTab(widget,widget->objectName());

    widget = new MultiAxis(this);
    tab->addTab(widget,widget->objectName());

    widget = new OpenglSeries(this);
    tab->addTab(widget,widget->objectName());

    tab->setCurrentIndex(tab->count()-1);
}

MainWindow::~MainWindow()
{

}
