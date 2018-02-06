#ifndef SCATTERINTERACTIONS_H
#define SCATTERINTERACTIONS_H

#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>

using namespace QtCharts;

class ScatterInterActions : public QChartView
{
    Q_OBJECT

public:
    ScatterInterActions(QWidget *parent = 0);

private slots:
    void handleClickedPoint(const QPointF &point);

private:
    QScatterSeries *_scatter  = 0;
    QScatterSeries *_scatter2 = 0;
};

#endif // SCATTERINTERACTIONS_H
