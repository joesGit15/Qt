#include "dynamicsplinewidget.h"

#include <QtCharts/qchartview.h>
#include <QtCharts/qchart.h>
#include <QtCharts/qsplineseries.h>
#include <QtCharts/qvalueaxis.h>

#include <QtCore/qtimer.h>
#include <QtCore/qdatetime.h>
#include <QtWidgets/qboxlayout.h>

DynamicSplineWidget::DynamicSplineWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(tr("Dynamic Spline"));

    QSplineSeries *series = new QSplineSeries(this);
    _series = series;
    QPen redPen(Qt::red);
    redPen.setWidth(3);
    series->setPen(redPen);

    QChart *chart = new QChart;
    _chart = chart;
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(tr("Dynamic Spline Chart"));
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->createDefaultAxes();
    QValueAxis  *axis = new QValueAxis(this);
    _axis = axis;
    axis->setTickCount(5);
    chart->setAxisX(axis,series);
    chart->axisX()->setRange(0,10);
    chart->axisY()->setRange(-5,10);

    QChartView *view = new QChartView(this);
    view->setChart(chart);
    view->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(view);
    setLayout(vlyt);

    qsrand(uint(QTime::currentTime().msec()));
    QTimer *t = new QTimer(this);
    connect(t,&QTimer::timeout,this,&DynamicSplineWidget::StTimerOut);
    t->start(1000);
}

void DynamicSplineWidget::StTimerOut()
{
    QChart* chart = _chart;
    QValueAxis* axis = _axis;

    qreal dx = chart->plotArea().width() / axis->tickCount();

    qreal y = (axis->max() - axis->min())/axis->tickCount();
    _x += y;

    _y = qrand()%5 - 2.5;
    _series->append(_x,_y);
    chart->scroll(dx,0);

    if(_x > 100){
        QTimer* t = qobject_cast<QTimer*>(sender());
        t->stop();
    }
}
