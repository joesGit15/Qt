#include "mainslice.h"

#include <QtCharts/qpieseries.h>

MainSlice::MainSlice(QPieSeries *breakdownSeries, QObject *parent)
    : QPieSlice(parent),_breakdownSeries(breakdownSeries)
{
    connect(this, SIGNAL(percentageChanged()), this, SLOT(updateLabel()));
}

QPieSeries *MainSlice::breakdownSeries() const
{
    return _breakdownSeries;
}

void MainSlice::setName(QString name)
{
    _name = name;
}

QString MainSlice::name() const
{
    return _name;
}

void MainSlice::updateLabel()
{
    setLabel(QString("%1 %2%").arg(_name).arg(percentage() * 100, 0, 'f', 2));
}
