#include "interactionchart.h"

#include <QtCore/qmath.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qabstractaxis.h>

InteractionChart::InteractionChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
    legend()->hide();
    setTitle("Drag'n drop to move data points");

    QLineSeries *series = new QLineSeries;
    _series = series;
    QPen p = series->pen();
    p.setWidth(5);
    p.setColor(QColor(39,135,200));
    series->setPen(p);

    int const max = 20;
    for(int i=0; i < max; i++){
        series->append(i,rand()%max);
    }

    addSeries(series);
    createDefaultAxes();

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, max);
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, max);

    setAxisX(axisX, series);
    setAxisY(axisY, series);
    connect(series, &QLineSeries::pressed, this, &InteractionChart::clickPoint);
}

InteractionChart::~InteractionChart()
{
}

void InteractionChart::clickPoint(const QPointF &point)
{
    /** Find the closes data point */
    _movingPoint = QPoint();
    _clicked = false;
    for (QPointF p:_series->points()) {
        if (distance(p, point) < distance(_movingPoint, point)) {
            _movingPoint = p;
            _clicked = true;
        }
    }
}

qreal InteractionChart::distance(const QPointF &p1, const QPointF &p2)
{
    return qSqrt((p1.x() - p2.x()) * (p1.x() - p2.x())
                + (p1.y() - p2.y()) * (p1.y() - p2.y()));
}

void InteractionChart::setPointClicked(bool clicked)
{
    _clicked = clicked;
}

void InteractionChart::handlePointMove(const QPoint &point)
{
    if (_clicked) {
        /** Map the point clicked from the ChartView
        to the area occupied by the chart.*/
        QPoint mappedPoint = point;
        mappedPoint.setX(point.x() - plotArea().x());
        mappedPoint.setY(point.y() - plotArea().y());

        /** Get the x- and y axis to be able to convert the mapped
        coordinate point to the charts scale.*/
        QAbstractAxis *axisx = axisX();
        QValueAxis *haxis = 0;
        if (axisx->type() == QAbstractAxis::AxisTypeValue){
            haxis = qobject_cast<QValueAxis *>(axisx);
        }

        QAbstractAxis *axisy = axisY();
        QValueAxis *vaxis = 0;
        if (axisy->type() == QAbstractAxis::AxisTypeValue){
            vaxis = qobject_cast<QValueAxis *>(axisy);
        }

        if (haxis && vaxis) {
            /** Calculate the "unit" between points on the x
            y axis. */
            double xUnit = plotArea().width() / haxis->max();
            double yUnit = plotArea().height() / vaxis->max();

            /** Convert the mappedPoint to the actual chart scale.*/
            double x = mappedPoint.x() / xUnit;
            double y = vaxis->max() - mappedPoint.y() / yUnit;

            /** Replace the old point with the new one.*/
            _series->replace(_movingPoint, QPointF(x, y));

            /** Update the m_movingPoint so we are able to
            do the replace also during mousemoveEvent.*/
            _movingPoint.setX(x);
            _movingPoint.setY(y);
        }
    }
}

