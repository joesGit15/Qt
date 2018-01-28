#include "horizontalpercentbarchart.h"

#include <QtCharts/qbarset.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qhorizontalpercentbarseries.h>

#include <QtWidgets/qboxlayout.h>

using namespace QtCharts;


HorizontalPercentBarChart::HorizontalPercentBarChart(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(tr("Horizontal Percent BarChart"));

    QBarSet *set0 = new QBarSet("Mon.");
    QBarSet *set1 = new QBarSet("Tue.");
    QBarSet *set2 = new QBarSet("Wed.");
    QBarSet *set3 = new QBarSet("Thu.");
    QBarSet *set4 = new QBarSet("Fri.");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    QHorizontalPercentBarSeries *series = new QHorizontalPercentBarSeries;
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTitle("Simple horizontal percent barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->setAxisY(axisY, series);

    QValueAxis *axisX = new QValueAxis();
    chart->setAxisX(axisX, series);
    axisX->applyNiceNumbers();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
