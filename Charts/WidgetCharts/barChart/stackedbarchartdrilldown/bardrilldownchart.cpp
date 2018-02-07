#include "bardrilldownchart.h"

#include <QtCharts/qbarcategoryaxis.h>

BarDrilldownChart::BarDrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
}

void BarDrilldownChart::changeSeries(DrilldownBarSeries *series)
{
    if (_currentSeries) {
        removeSeries(_currentSeries);
    }

    _currentSeries = series;

    /** Reset axis */
    QBarCategoryAxis *axis = new QBarCategoryAxis;
    axis->append(_currentSeries->categories());

    addSeries(series);

    createDefaultAxes();
    setAxisX(axis, series);
    axisY()->setTitleText("Crops");

    setTitle(series->name());
}

void BarDrilldownChart::handleClicked(int index, QBarSet *barset)
{
    (void)barset;

    DrilldownBarSeries *series = static_cast<DrilldownBarSeries *>(sender());
    changeSeries(series->drilldownSeries(index));
}
