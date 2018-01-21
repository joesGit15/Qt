#include "areaseries.h"

#include <QtWidgets/qboxlayout.h>

#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qareaseries.h>

using namespace QtCharts;

AreaSeries::AreaSeries(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("AreaSeries");

    QLineSeries* upperline = new QLineSeries(this);
    QLineSeries* lowerline = new QLineSeries(this);

    *upperline << QPointF(1, 13) << QPointF(2, 13)   << QPointF(3, 13.5) << QPointF(4, 13) << QPointF(5, 13) << QPointF(6, 10) << QPointF(7, 10);
    *lowerline << QPointF(1, 12) << QPointF(2, 12.5) << QPointF(3, 13)   << QPointF(4, 12) << QPointF(5, 12) << QPointF(6, 8)  << QPointF(7, 9);

    QAreaSeries* series = new QAreaSeries(upperline,lowerline);
    series->setName(tr("Game"));

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::yellow);
    series->setPen(pen);

    QLinearGradient griadient(QPointF(0,0),QPointF(0,1));
    griadient.setColorAt(0.0,Qt::blue);
    griadient.setColorAt(1.0,Qt::green);
    griadient.setCoordinateMode(QGradient::ObjectBoundingMode);
    series->setBrush(griadient);

    QChart* chart = new QChart;
    chart->setTitle(tr("AreaChart-Game time"));
    chart->addSeries(series);

    chart->createDefaultAxes();
    chart->axisX()->setRange(1,7);
    chart->axisY()->setRange(0,24);

    QChartView* view = new QChartView(this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setChart(chart);

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addWidget(view);
    setLayout(vlyt);
}
