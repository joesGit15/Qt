#ifndef DONUTBREAKDOWNCHART_H
#define DONUTBREAKDOWNCHART_H

#include <QtCharts/QChart>

namespace QtCharts {
    class QPieSeries;
}
using namespace QtCharts;

class DonutBreakdownChart : public QChart
{
public:
    DonutBreakdownChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    void addBreakdownSeries(QPieSeries *series, QColor color);

private:
    void recalculateAngles();
    void updateLegendMarkers();

private:
    QPieSeries *_mainSeries;
};

#endif // DONUTBREAKDOWNCHART_H
