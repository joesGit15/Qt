#ifndef INTERACTIONCHART_H
#define INTERACTIONCHART_H

#include <QtCharts/qchart.h>

namespace QtCharts {
    class QLineSeries;
}
using namespace QtCharts;

class InteractionChart : public QChart
{
    Q_OBJECT
public:
    explicit InteractionChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~InteractionChart();

public:
    void handlePointMove(const QPoint &point);
    void setPointClicked(bool clicked);

private slots:
    void clickPoint(const QPointF &point);

private:
    qreal distance(const QPointF &p1, const QPointF &p2);

private:
    QPointF _movingPoint;
    QLineSeries *_series = 0;

    //Boolean value to determine if an actual point in the
    //series is clicked.
    bool _clicked = false;
};

#endif // CHART_H
