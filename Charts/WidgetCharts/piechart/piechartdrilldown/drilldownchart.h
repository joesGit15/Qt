#ifndef DRILLDOWNCHART_H
#define DRILLDOWNCHART_H

#include <QtCharts/qchart.h>

namespace QtCharts {
    class QAbstractSeries;
    class QPieSlice;
}
using namespace QtCharts;

class DrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit DrilldownChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);

    void changeSeries(QAbstractSeries *series);

public slots:
    void handleSliceClicked(QPieSlice *slice);

private:
    QAbstractSeries *_currentSeries = 0;
};

#endif // DRILLDOWNCHART_H
