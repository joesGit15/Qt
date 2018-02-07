#include "drilldownseries.h"

DrilldownBarSeries::DrilldownBarSeries(QStringList categories, QObject *parent)
    : QStackedBarSeries(parent)
{
    _categories = categories;
}

void DrilldownBarSeries::mapDrilldownSeries(int index, DrilldownBarSeries *drilldownSeries)
{
    _DrilldownSeries[index] = drilldownSeries;
}

DrilldownBarSeries *DrilldownBarSeries::drilldownSeries(int index)
{
    return _DrilldownSeries[index];
}

QStringList DrilldownBarSeries::categories()
{
    return _categories;
}
