#include "donutbreakdownchart.h"
#include "mainslice.h"

#include <QtCharts/qpieslice.h>
#include <QtCharts/qpielegendmarker.h>

DonutBreakdownChart::DonutBreakdownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
    /** create the series for main center pie */
    _mainSeries = new QPieSeries();
    _mainSeries->setPieSize(0.7);
    QChart::addSeries(_mainSeries);
}

void DonutBreakdownChart::addBreakdownSeries(QPieSeries *breakdownSeries, QColor color)
{
    QFont font("Arial", 8);

    /** add breakdown series as a slice to center pie*/
    MainSlice *mainSlice = new MainSlice(breakdownSeries);
    mainSlice->setName(breakdownSeries->name());
    mainSlice->setValue(breakdownSeries->sum());
    _mainSeries->append(mainSlice);

    /** customize the slice */
    mainSlice->setBrush(color);
    mainSlice->setLabelVisible();
    mainSlice->setLabelColor(Qt::white);
    mainSlice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
    mainSlice->setLabelFont(font);

    /** position and customize the breakdown series */
    breakdownSeries->setPieSize(0.8);
    breakdownSeries->setHoleSize(0.7);
    breakdownSeries->setLabelsVisible();
    foreach (QPieSlice *slice, breakdownSeries->slices()) {
        color = color.lighter(115);
        slice->setBrush(color);
        slice->setLabelFont(font);
    }

    QChart::addSeries(breakdownSeries);

    /** recalculate breakdown donut segments */
    recalculateAngles();

    /** update customize legend markers */
    updateLegendMarkers();
}

void DonutBreakdownChart::recalculateAngles()
{
    qreal angle = 0;
    for (QPieSlice *slice: _mainSeries->slices()) {
        QPieSeries *breakdownSeries = qobject_cast<MainSlice *>(slice)->breakdownSeries();
        breakdownSeries->setPieStartAngle(angle);
        angle += slice->percentage() * 360.0; ///< full pie is 360.0
        breakdownSeries->setPieEndAngle(angle);
    }
}

void DonutBreakdownChart::updateLegendMarkers()
{
    /** go through all markers */
    for (QAbstractSeries *series: QChart::series()) {
        for (QLegendMarker *marker: legend()->markers(series)) {
            QPieLegendMarker *pieMarker = qobject_cast<QPieLegendMarker *>(marker);
            if (series == _mainSeries) {
                /** hide markers from main series */
                pieMarker->setVisible(false);
            } else {
                /** modify markers from breakdown series */
                pieMarker->setLabel(QString("%1 %2%")
                                    .arg(pieMarker->slice()->label())
                                    .arg(pieMarker->slice()->percentage() * 100, 0, 'f', 2));
                pieMarker->setFont(QFont("Arial", 8));
            }
        }
    }
}
