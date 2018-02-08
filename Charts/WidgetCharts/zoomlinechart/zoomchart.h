#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>

class QGestureEvent;

using namespace QtCharts;

class ZoomChart : public QChart
{
public:
    explicit ZoomChart(QGraphicsItem *parent = 0,
                   Qt::WindowFlags wFlags = 0);

protected:
    bool sceneEvent(QEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);
};

#endif // CHART_H
