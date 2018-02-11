#include "barcandlestickchart.h"
#include "candlestickdatareader.h"

#include <QtCore/qdatetime.h>

#include <QtCharts/qchartview.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qcandlestickseries.h>

#include <QtWidgets/qboxlayout.h>

using namespace QtCharts;

BarCandlestickChart::BarCandlestickChart(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Candlestick Chart");

    QCandlestickSeries *acmeSeries = new QCandlestickSeries;
    acmeSeries->setName("Acme Ltd");
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));

    QFile acmeData(":acme");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList categories;

    CandlestickDataReader dataReader(&acmeData);
    while (!dataReader.atEnd()) {
        QCandlestickSet *set = dataReader.readCandlestickSet();
        if (set) {
            acmeSeries->append(set);
            categories << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");
        }
    }

    QChart *chart = new QChart;
    chart->addSeries(acmeSeries);
    chart->setTitle("Acme Ltd Historical Data (July 2015)");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->createDefaultAxes();

    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
