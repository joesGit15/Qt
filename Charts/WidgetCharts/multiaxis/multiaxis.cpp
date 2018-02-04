#include "multiaxis.h"

#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qsplineseries.h>
#include <QtCharts/qcategoryaxis.h>

#include <QtWidgets/qboxlayout.h>

using namespace QtCharts;

MultiAxis::MultiAxis(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Multiaxis");

    QChart *chart = new QChart;
    chart->legend()->hide();
    chart->setTitle("Multiaxis chart example");

    QSplineSeries *series = new QSplineSeries;
    *series << QPointF(1, 5) << QPointF(3.5, 18)
            << QPointF(4.8, 7.5) << QPointF(10, 2.5);
    chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLinePenColor(series->pen().color());
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    /**  */
    series = new QSplineSeries;
    *series << QPointF(1, 0.5) << QPointF(1.5, 4.5)
            << QPointF(2.4, 2.5) << QPointF(4.3, 12.5)
            << QPointF(5.2, 3.5) << QPointF(7.4, 16.5)
            << QPointF(8.3, 7.5) << QPointF(10, 17);
    chart->addSeries(series);

    QCategoryAxis *axisY3 = new QCategoryAxis;
    axisY3->append("Low", 5);
    axisY3->append("Medium", 12);
    axisY3->append("High", 17);
    axisY3->setLinePenColor(series->pen().color());
    axisY3->setGridLinePen((series->pen()));
    chart->addAxis(axisY3, Qt::AlignRight);

    series->attachAxis(axisX);
    series->attachAxis(axisY3);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
