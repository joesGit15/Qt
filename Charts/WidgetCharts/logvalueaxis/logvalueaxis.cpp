#include "logvalueaxis.h"

#include <QtWidgets/qboxlayout.h>

#include <QtCharts/qchartview.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qlogvalueaxis.h>

using namespace QtCharts;

LogValueAxis::LogValueAxis(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("LogValueAxis");

    QLineSeries *series = new QLineSeries;
    *series << QPointF(1, 1) << QPointF(2, 73) << QPointF(3, 268)
            << QPointF(4, 17) << QPointF(5, 4325) << QPointF(6, 723);

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Logarithmic axis example");

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Data point");
    axisX->setTickCount(6);
    axisX->setLabelFormat("%i");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QLogValueAxis *axisY = new QLogValueAxis;
    axisY->setTitleText("Values");
    axisY->setLabelFormat("%g");
    axisY->setBase(8);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
