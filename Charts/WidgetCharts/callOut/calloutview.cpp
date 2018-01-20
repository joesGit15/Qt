#include "calloutview.h"
#include "calloutitem.h"

#include <QtGui/qevent.h>
#include <QtWidgets/qgraphicsscene.h>
#include <QtWidgets/qgraphicsitem.h>

#include <QtCharts/qchart.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qsplineseries.h>

CallOutView::CallOutView(QWidget *parent)
    : QGraphicsView(new QGraphicsScene, parent)
{
    setObjectName("CallOut");
    setMouseTracking(true);
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _chart = new QChart;
    _chart->legend()->hide();
    _chart->setMinimumSize(640, 480);
    _chart->setTitle("Hover the line to show callout. Click the line to make it stay");

    QLineSeries *series = new QLineSeries;
    connect(series, &QLineSeries::clicked,
            this, &CallOutView::keepCallout);
    connect(series, &QLineSeries::hovered,
            this, &CallOutView::tooltip);
    series->append(1, 3);
    series->append(4, 5);
    series->append(5, 4.5);
    series->append(7, 1);
    series->append(11, 2);
    _chart->addSeries(series);

    QSplineSeries *series2 = new QSplineSeries;
    connect(series2, &QSplineSeries::clicked,
            this, &CallOutView::keepCallout);
    connect(series2, &QSplineSeries::hovered,
            this, &CallOutView::tooltip);
    series2->append(1.6, 1.4);
    series2->append(2.4, 3.5);
    series2->append(3.7, 2.5);
    series2->append(7, 4);
    series2->append(10, 2);
    _chart->addSeries(series2);

    _chart->createDefaultAxes();
    _chart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);
    scene()->addItem(_chart);

    _coordX = new QGraphicsSimpleTextItem(_chart);
    _coordX->setPos(_chart->size().width()/2 - 50, _chart->size().height());
    _coordX->setText("X: ");
    _coordY = new QGraphicsSimpleTextItem(_chart);
    _coordY->setPos(_chart->size().width()/2 + 50, _chart->size().height());
    _coordY->setText("Y: ");

}

void CallOutView::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
         _chart->resize(event->size());
         _coordX->setPos(_chart->size().width()/2 - 50, _chart->size().height() - 20);
         _coordY->setPos(_chart->size().width()/2 + 50, _chart->size().height() - 20);
         for (GraphicsCalloutItem *callout: _callouts){
             callout->updateGeometry();
         }
    }
    QGraphicsView::resizeEvent(event);
}

void CallOutView::mouseMoveEvent(QMouseEvent *event)
{
    _coordX->setText(QString("X: %1").arg(_chart->mapToValue(event->pos()).x()));
    _coordY->setText(QString("Y: %1").arg(_chart->mapToValue(event->pos()).y()));
    QGraphicsView::mouseMoveEvent(event);
}

void CallOutView::keepCallout()
{
    _callouts.append(_tooltip);
    _tooltip = new GraphicsCalloutItem(_chart);
}

void CallOutView::tooltip(QPointF point, bool state)
{
    if (_tooltip == 0){
        _tooltip = new GraphicsCalloutItem(_chart);
    }

    if (state) {
        _tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        _tooltip->setAnchor(point);
        _tooltip->setZValue(11);
        _tooltip->updateGeometry();
        _tooltip->show();
    } else {
        _tooltip->hide();
    }
}
