#include "interactionchartview.h"
#include "interactionchart.h"

#include <QtGui/qevent.h>

InteractionChartView::InteractionChartView(InteractionChart *chart, QWidget *parent) :
    QChartView(chart, parent)
{
    _chart = chart;
    setRenderHint(QPainter::Antialiasing);
}

void InteractionChartView::mousePressEvent(QMouseEvent *event)
{
    _mousePos = event->pos();
    QChartView::mousePressEvent(event);
}

void InteractionChartView::mouseMoveEvent(QMouseEvent *event)
{
    _chart->handlePointMove(event->pos());
    QChartView::mouseMoveEvent(event);
}

void InteractionChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->pos() != _mousePos) {
        _chart->handlePointMove(event->pos());
        _chart->setPointClicked(false);
    }
    QChartView::mouseReleaseEvent(event);
}
