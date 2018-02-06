#include "scatterchart.h"

#include <QtCharts/qlegendmarker.h>
#include <QtCharts/qscatterseries.h>

#include <QtGui/qimage.h>
#include <QtGui/qpainter.h>

#include <QtCore/qmath.h>

const float Pi = 3.14159f;

ScatterChart::ScatterChart(QWidget *parent) :
    QChartView(new QChart(), parent)
{
    setObjectName("Scatter Chart");

    QScatterSeries *series0 = new QScatterSeries;
    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(15.0);

    series0->append(0, 6);
    series0->append(2, 4);
    series0->append(3, 8);
    series0->append(7, 4);
    series0->append(10, 5);

    QScatterSeries *series1 = new QScatterSeries;
    series1->setName("scatter2");
    series1->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series1->setMarkerSize(20.0);
    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6)
             << QPointF(8, 3) << QPointF(10, 2);

    QScatterSeries *series2 = new QScatterSeries;
    series2->setName("scatter3");
    series2->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series2->setMarkerSize(30.0);
    *series2 << QPointF(1, 5) << QPointF(4, 6) << QPointF(6, 3) << QPointF(9, 5);

    QPainterPath starPath;
    starPath.moveTo(30, 15);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(15 + 15 * qCos(0.8 * i * Pi),
                        15 + 15 * qSin(0.8 * i * Pi));
    }
    starPath.closeSubpath();

    QImage star(30, 30, QImage::Format_ARGB32);
    star.fill(Qt::transparent);

    QPainter painter(&star);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QRgb(0xf6a625));
    painter.setBrush(painter.pen().color());
    painter.drawPath(starPath);

    series2->setBrush(star);

    setRenderHint(QPainter::Antialiasing);

    chart()->addSeries(series0);
    chart()->addSeries(series1);
    chart()->addSeries(series2);

    chart()->setTitle("Simple scatterchart example");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);

    QList<QLegendMarker *> markers = chart()->legend()->markers(series2);
    for (int i = 0; i < markers.count(); i++)
        markers.at(i)->setBrush(painter.pen().color());
}
