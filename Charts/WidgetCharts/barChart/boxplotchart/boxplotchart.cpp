#include "boxplotchart.h"

#include <QtCharts/qboxset.h>

#include <QtCharts/qlegend.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qbarcategoryaxis.h>

#include <QtCore/qfile.h>

#include <QtWidgets/qboxlayout.h>

#include "boxdatareader.h"

using namespace QtCharts;

BoxPlotChart::BoxPlotChart(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Box Plot");

    QBoxPlotSeries *acmeSeries = new QBoxPlotSeries;
    acmeSeries->setName("Acme Ltd");

    QBoxPlotSeries *boxWhiskSeries = new QBoxPlotSeries;
    boxWhiskSeries->setName("BoxWhisk Inc");

    QFile acmeData(":acme");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    BoxDataReader dataReader(&acmeData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set)
            acmeSeries->append(set);
    }

    QFile boxwhiskData(":boxwhisk");
    if (!boxwhiskData.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    dataReader.readFile(&boxwhiskData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set)
            boxWhiskSeries->append(set);
    }

    QChart *chart = new QChart;
    chart->addSeries(acmeSeries);
    chart->addSeries(boxWhiskSeries);
    chart->setTitle("Acme Ltd and BoxWhisk Inc share deviation in 2012");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->createDefaultAxes();
    chart->axisY()->setMin(15.0);
    chart->axisY()->setMax(34.0);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
