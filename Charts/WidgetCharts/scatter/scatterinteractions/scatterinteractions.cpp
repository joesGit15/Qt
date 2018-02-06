#include "scatterinteractions.h"

#include <QtCore/qmath.h>

ScatterInterActions::ScatterInterActions(QWidget *parent)
    : QChartView(new QChart(), parent)
{
    setObjectName("Scatter Inter Actions");

    setRenderHint(QPainter::Antialiasing);

    chart()->setTitle("Click to interact with scatter points");

    _scatter = new QScatterSeries();
    _scatter->setName("scatter1");
    for (qreal x(0.5); x <= 4.0; x += 0.5) {
        for (qreal y(0.5); y <= 4.0; y += 0.5) {
            *_scatter << QPointF(x, y);
        }
    }
    _scatter2 = new QScatterSeries();
    _scatter2->setName("scatter2");

    chart()->addSeries(_scatter2);
    chart()->addSeries(_scatter);
    chart()->createDefaultAxes();
    chart()->axisX()->setRange(0, 4.5);
    chart()->axisY()->setRange(0, 4.5);

    connect(_scatter, &QScatterSeries::clicked,
            this, &ScatterInterActions::handleClickedPoint);
}

void ScatterInterActions::handleClickedPoint(const QPointF &point)
{
    QPointF clickedPoint = point;
    /** Find the closest point from series 1 */
    QPointF closest(INT_MAX, INT_MAX);
    qreal distance(INT_MAX);
    foreach (QPointF currentPoint, _scatter->points()) {
        qreal currentDistance = qSqrt((currentPoint.x() - clickedPoint.x())
                                      * (currentPoint.x() - clickedPoint.x())
                                      + (currentPoint.y() - clickedPoint.y())
                                      * (currentPoint.y() - clickedPoint.y()));
        if (currentDistance < distance) {
            distance = currentDistance;
            closest = currentPoint;
        }
    }

    /** Remove the closes point from series 1 and append it to series 2 */
    _scatter->remove(closest);
    _scatter2->append(closest);
}
