#include "drilldownslice.h"

DrilldownSlice::DrilldownSlice(qreal value, QString prefix, QAbstractSeries *drilldownSeries)
    : _drilldownSeries(drilldownSeries),_prefix(prefix)
{
    setValue(value);
    updateLabel();
    setLabelFont(QFont("Arial", 8));

    connect(this, &DrilldownSlice::percentageChanged,
            this, &DrilldownSlice::updateLabel);
    connect(this, &DrilldownSlice::hovered,
            this, &DrilldownSlice::showHighlight);
}

QAbstractSeries *DrilldownSlice::drilldownSeries() const
{
    return _drilldownSeries;
}

void DrilldownSlice::updateLabel()
{
    QString label = _prefix;
    label += " $";
    label += QString::number(value());
    label += ", ";
    label += QString::number(percentage() * 100, 'f', 1);
    label += "%";
    setLabel(label);
}

void DrilldownSlice::showHighlight(bool show)
{
    setLabelVisible(show);
    setExploded(show);
}
