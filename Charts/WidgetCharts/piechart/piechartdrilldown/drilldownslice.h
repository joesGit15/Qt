#ifndef DRILLDOWNSLICE_H
#define DRILLDOWNSLICE_H

#include <QtCharts/qpieseries.h>

namespace QtCharts{
    class QAbstractSeries;
}
using namespace QtCharts;

class DrilldownSlice : public QPieSlice
{
    Q_OBJECT

public:
    DrilldownSlice(qreal value, QString prefix, QAbstractSeries *drilldownSeries);

    QAbstractSeries *drilldownSeries() const;

public Q_SLOTS:
    void updateLabel();
    void showHighlight(bool show);

private:
    QString _prefix;
    QAbstractSeries *_drilldownSeries = 0;
};

#endif // DRILLDOWNSLICE_H
