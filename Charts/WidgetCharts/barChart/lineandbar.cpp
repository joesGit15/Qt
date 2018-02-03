#include "lineandbar.h"

#include <QtCharts/qlegend.h>
#include <QtCharts/qbarset.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qbarcategoryaxis.h>

#include <QtWidgets/qboxlayout.h>

using namespace QtCharts;

LineAndBar::LineAndBar(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("LineAndBar");

    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Sam");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    QBarSeries *barseries = new QBarSeries;
    barseries->append(set0);
    barseries->append(set1);
    barseries->append(set2);
    barseries->append(set3);
    barseries->append(set4);

    QLineSeries *lineseries = new QLineSeries;
    lineseries->setName("trend");
    lineseries->append(QPoint(0, 4));
    lineseries->append(QPoint(1, 15));
    lineseries->append(QPoint(2, 20));
    lineseries->append(QPoint(3, 4));
    lineseries->append(QPoint(4, 12));
    lineseries->append(QPoint(5, 17));

    QChart *chart = new QChart;
    chart->addSeries(barseries);
    chart->addSeries(lineseries);
    chart->setTitle("Line and barchart example");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append(categories);
    chart->setAxisX(axisX, lineseries);
    chart->setAxisX(axisX, barseries);
    axisX->setRange(QString("Jan"), QString("Jun"));

    QValueAxis *axisY = new QValueAxis;
    chart->setAxisY(axisY, lineseries);
    chart->setAxisY(axisY, barseries);
    axisY->setRange(0, 20);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
