#include "mainwindow.h"

#include "areaSeries/areaseries.h"
#include "barChart/barchartwidget.h"
#include "callOut/calloutview.h"
#include "chartInteractions/interactionwidget.h"
#include "chartThemes/themewidget.h"
#include "customChart/customchartwidget.h"
#include "dynamicspline/dynamicsplinewidget.h"
#include "legend/legend.h"
#include "legendmarkers/legendmarkerswidget.h"
#include "logvalueaxis/logvalueaxis.h"
#include "multiaxis/multiaxis.h"
#include "openglseries/openglseries.h"
#include "piechart/piechart.h"
#include "scatter/scatter.h"
#include "zoomlinechart/zoomlinechart.h"
#include "audio/audiowidget.h"
#include "datetimeaxis/datetimeaxis.h"
#include "modeldata/modeldata.h"
#include "polarchart/polarchart.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtablewidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTabWidget* tab = new QTabWidget(this);
    setCentralWidget(tab);

    QWidget *widget = 0;

    widget = new PolarChart(this);
    tab->addTab(widget,widget->objectName());

    widget = new ModelData(this);
    tab->addTab(widget,widget->objectName());

    widget = new DatetimeAxis(this);
    tab->addTab(widget,widget->objectName());

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

    widget = new PieChart(this);
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

    widget = new Scatter(this);
    tab->addTab(widget,widget->objectName());

    widget = new ZoomLineChart(this);
    tab->addTab(widget,widget->objectName());

    widget = new AudioWidget(this);
    tab->addTab(widget,widget->objectName());
}

MainWindow::~MainWindow()
{

}
