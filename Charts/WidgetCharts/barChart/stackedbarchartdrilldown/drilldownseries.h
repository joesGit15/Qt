#ifndef DRILLDOWNSERIES_H
#define DRILLDOWNSERIES_H

#include <QtCore/qmap.h>
#include <QtCharts/qstackedbarseries.h>

using namespace QtCharts;

class DrilldownBarSeries : public QStackedBarSeries
{
    Q_OBJECT
public:
    DrilldownBarSeries(QStringList categories, QObject *parent = 0);

    void mapDrilldownSeries(int index, DrilldownBarSeries *drilldownSeries);

    DrilldownBarSeries *drilldownSeries(int index);

    QStringList categories();

private:
    QStringList _categories;

    QMap<int, DrilldownBarSeries *> _DrilldownSeries;
};

#endif // DRILLDOWNSERIES_H
