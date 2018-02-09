#include "temperaturerecords.h"

#include <QtCharts/qbarset.h>
#include <QtCharts/qlegend.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qstackedbarseries.h>

#include <QtWidgets/qboxlayout.h>

using namespace QtCharts;

TemperatureRecords::TemperatureRecords(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("TemperatureRecords");

    QBarSet *low = new QBarSet("Min");
    QBarSet *high = new QBarSet("Max");

    *low << -52 << -50 << -45.3 << -37.0 << -25.6 << -8.0
         << -6.0 << -11.8 << -19.7 << -32.8 << -43.0 << -48.0;
    *high << 11.9 << 12.8 << 18.5 << 26.5 << 32.0 << 34.8
          << 38.2 << 34.8 << 29.8 << 20.4 << 15.1 << 11.8;

    QStackedBarSeries *series = new QStackedBarSeries;
    series->append(low);
    series->append(high);

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Temperature records in celcius");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun"
               << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

    QBarCategoryAxis *axis = new QBarCategoryAxis;
    axis->append(categories);
    axis->setTitleText("Month");
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->axisY(series)->setRange(-52, 52);
    chart->axisY(series)->setTitleText("Temperature [&deg;C]");

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
