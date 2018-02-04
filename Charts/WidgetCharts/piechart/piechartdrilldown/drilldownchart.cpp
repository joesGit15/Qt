#include "drilldownchart.h"
#include "drilldownslice.h"

DrilldownChart::DrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignRight);
    setTheme(QChart::ChartThemeLight);
    setAnimationOptions(QChart::AllAnimations);
}

void DrilldownChart::changeSeries(QAbstractSeries *series)
{
    if (_currentSeries)
        removeSeries(_currentSeries);

    _currentSeries = series;
    addSeries(series);
    setTitle(series->name());
}

void DrilldownChart::handleSliceClicked(QPieSlice *slice)
{
    DrilldownSlice *drilldownSlice = static_cast<DrilldownSlice *>(slice);
    changeSeries(drilldownSlice->drilldownSeries());
}
