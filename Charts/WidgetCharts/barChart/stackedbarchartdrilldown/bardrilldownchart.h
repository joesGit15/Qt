#ifndef BARDRILLDOWNCHART_H
#define BARDRILLDOWNCHART_H

#include <QtCharts/QChart>

#include "drilldownseries.h"

using namespace QtCharts;

class BarDrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit BarDrilldownChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);

    void changeSeries(DrilldownBarSeries *series);

public slots:
    void handleClicked(int index, QBarSet *barset);

private:
    DrilldownBarSeries *_currentSeries;
};

#endif // DRILLDOWNCHART_H
