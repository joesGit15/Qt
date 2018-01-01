#include "barchart.h"

#include <QtWidgets/qboxlayout.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qbarset.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qbarcategoryaxis.h>

using namespace QtCharts;

BarChart::BarChart(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("BarChart");

    QBarSet* mon = new QBarSet("Mon.");
    QBarSet* tue = new QBarSet("Tue.");
    QBarSet* wed = new QBarSet("Wed.");
    QBarSet* thu = new QBarSet("Thu.");
    QBarSet* fri = new QBarSet("Fri.");
    QBarSet* sat = new QBarSet("Sat.");
    QBarSet* sun = new QBarSet("Sun.");

    QStringList categries;
    categries << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";

    *mon << 1 << 2 << 3 << 4 << 5 << 6;
    *tue << 6 << 5 << 4 << 3 << 2 << 1;
    *wed << 3 << 2 << 5 << 1 << 4 << 3;
    *thu << 4 << 7 << 2 << 4 << 9 << 2;
    *fri << 5 << 3 << 8 << 5 << 3 << 9;
    *sat << 1 << 4 << 7 << 9 << 0 << 2;
    *sun << 5 << 2 << 7 << 9 << 3 << 5;

    QBarSeries* series = new QBarSeries(this);
    series->append(mon);
    series->append(tue);
    series->append(wed);
    series->append(thu);
    series->append(fri);
    series->append(sat);
    series->append(sun);

    QChart* chart = new QChart;
    chart->addSeries(series);
    chart->setTitle(tr("Bar Charts"));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QBarCategoryAxis* axis = new QBarCategoryAxis(this);
    axis->append(categries);

    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

    QChartView* view = new QChartView(this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setChart(chart);

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addWidget(view);
    setLayout(vlyt);
}
