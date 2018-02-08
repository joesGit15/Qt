#include "zoomlinechart.h"

#include "zoomchart.h"
#include "zoomchartview.h"

#include <QtCore/qmath.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qlineseries.h>

#include <QtWidgets/qboxlayout.h>

using namespace QtCharts;

ZoomLineChart::ZoomLineChart(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Zoom Line");

    QLineSeries *series = new QLineSeries;
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += qrand() % 20;
        *series << p;
    }

    ZoomChart *chart = new ZoomChart;
    chart->addSeries(series);
    chart->setTitle("Zoom in/out example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();

    ZoomChartView *chartView = new ZoomChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
