#ifndef XYSERIESIODEVICE_H
#define XYSERIESIODEVICE_H

#include <QtCore/QIODevice>
#include <QtCharts/QChartGlobal>

namespace QtCharts {
    class QXYSeries;
}

using namespace QtCharts;

class XYSeriesIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit XYSeriesIODevice(QXYSeries * series, QObject *parent = 0);

protected:
    qint64 readData(char * data, qint64 maxSize);
    qint64 writeData(const char * data, qint64 maxSize);

private:
    QXYSeries *_series;
};

#endif // XYSERIESIODEVICE_H
