#include "drilldownwidget.h"

#include "drilldownchart.h"
#include "drilldownslice.h"

#include <QtCore/qdatetime.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qpieseries.h>
#include <QtWidgets/qboxlayout.h>

using namespace QtCharts;

DrilldownWidget::DrilldownWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("DrilldownWidget");

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    DrilldownChart *chart = new DrilldownChart;

    QPieSeries *yearSeries = new QPieSeries(this);
    yearSeries->setName("Sales by year - All");

    QList<QString> months;
    months << "Jan" << "Feb" << "Mar" << "Apr" << "May"
           << "Jun" << "Jul" << "Aug" << "Sep" << "Oct"
           << "Nov" << "Dec";

    QList<QString> names;
    names << "Jane" << "John" << "Axel"
          << "Mary" << "Susan" << "Bob";

    foreach (QString name, names) {
        QPieSeries *series = new QPieSeries(this);
        series->setName("Sales by month - " + name);

        foreach (QString month, months)
            *series << new DrilldownSlice(qrand() % 1000, month, yearSeries);

        connect(series, &QPieSeries::clicked,
                chart, &DrilldownChart::handleSliceClicked);

        *yearSeries << new DrilldownSlice(series->sum(), name, series);
    }

    connect(yearSeries, &QPieSeries::clicked,
            chart, &DrilldownChart::handleSliceClicked);

    chart->changeSeries(yearSeries);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
