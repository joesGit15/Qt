#include "barchartwidget.h"

#include "barchart.h"
#include "lineandbar.h"
#include "horizontalbarchart.h"
#include "horizontalpercentbarchart.h"
#include "horizontalstackedbarchart.h"

#include "stackedbarchartdrilldown/stackedbardrilldown.h"
#include "temperaturerecords/temperaturerecords.h"

#include "barmodelmapper/tablewidget.h"
#include "boxplotchart/boxplotchart.h"

#include <QtWidgets/qtoolbox.h>
#include <QtWidgets/qboxlayout.h>

BarChartWidget::BarChartWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(tr("Bar Chart"));

    QToolBox *tbox = new QToolBox(this);
    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(tbox);
    setLayout(vlyt);

    QWidget *widget = 0;

    widget = new BoxPlotChart(this);
    tbox->addItem(widget,widget->objectName());

    widget = new TableWidget(this);
    tbox->addItem(widget,widget->objectName());

    widget = new TemperatureRecords(this);
    tbox->addItem(widget,widget->objectName());

    widget = new StackedBarDrilldown(this);
    tbox->addItem(widget,widget->objectName());

    widget = new BarChart(this);
    tbox->addItem(widget,widget->objectName());

    widget = new HorizontalBarChart(this);
    tbox->addItem(widget,widget->objectName());

    widget = new HorizontalPercentBarChart(this);
    tbox->addItem(widget,widget->objectName());

    widget = new HorizontalStackedBarChart(this);
    tbox->addItem(widget,widget->objectName());

    widget = new LineAndBar(this);
    tbox->addItem(widget,widget->objectName());
}
