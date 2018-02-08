#include "zoomchartview.h"

#include <QtGui/qevent.h>

ZoomChartView::ZoomChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

bool ZoomChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        /** By default touch events are converted to mouse events. So
        after this event we will get a mouse event also but we want
        to handle touch events as gestures only. So we need this safeguard
        to block mouse events that are actually generated from touch.*/
        _isTouching = true;

        /** Turn off animations when handling gestures they will only slow us down. */
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void ZoomChartView::mousePressEvent(QMouseEvent *event)
{
    if (_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void ZoomChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (_isTouching)
        return;
    QChartView::mouseMoveEvent(event);
}

void ZoomChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (_isTouching)
        _isTouching = false;

    /** Because we disabled animations when touch event was detected
    we must put them back on. */
    chart()->setAnimationOptions(QChart::SeriesAnimations);

    QChartView::mouseReleaseEvent(event);
}

void ZoomChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
