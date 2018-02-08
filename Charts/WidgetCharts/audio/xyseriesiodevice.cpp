#include "xyseriesiodevice.h"

#include <QtCharts/qxyseries.h>

XYSeriesIODevice::XYSeriesIODevice(QXYSeries * series, QObject *parent) :
    QIODevice(parent),_series(series)
{
}

qint64 XYSeriesIODevice::readData(char * data, qint64 maxSize)
{
    (void)data;
    (void)maxSize;
    return -1;
}

qint64 XYSeriesIODevice::writeData(const char * data, qint64 maxSize)
{
    qint64 range = 2000;
    QVector<QPointF> oldPoints = _series->pointsVector();
    QVector<QPointF> points;
    int resolution = 4;

    if (oldPoints.count() < range) {
        points = _series->pointsVector();
    } else {
        for (int i = maxSize/resolution; i < oldPoints.count(); i++)
            points.append(QPointF(i - maxSize/resolution, oldPoints.at(i).y()));
    }

    qint64 size = points.count();
    for (int k = 0; k < maxSize/resolution; k++)
        points.append(QPointF(k + size, ((quint8)data[resolution * k] - 128)/128.0));

    _series->replace(points);
    return maxSize;
}
