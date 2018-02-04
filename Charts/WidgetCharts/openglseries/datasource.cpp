#include "datasource.h"

#include <QtCore/qmath.h>

DataSource::DataSource(QObject *parent) :
    QObject(parent)
{
    generateData(0, 0, 0);
}

void DataSource::update(QAbstractSeries *series, int seriesIndex)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        const QVector<QVector<QPointF> > &seriesData = _data.at(seriesIndex);
        if (seriesIndex == 0)
            _index++;
        if (_index > seriesData.count() - 1)
            _index = 0;

        QVector<QPointF> points = seriesData.at(_index);
        /** Use replace instead of clear + append, it's optimized for performance */
        xySeries->replace(points);
    }
}

void DataSource::handleSceneChanged()
{
    _dataUpdater.start();
}

void DataSource::updateAllSeries()
{
    static int frameCount = 0;
    static QString labelText = QStringLiteral("FPS: %1");

    for (int i = 0; i < _seriesList.size(); i++)
        update(_seriesList[i], i);

    frameCount++;
    int elapsed = _fpsTimer.elapsed();
    if (elapsed >= 1000) {
        elapsed = _fpsTimer.restart();
        qreal fps = qreal(0.1 * int(10000.0 * (qreal(frameCount) / qreal(elapsed))));
        _fpsLabel->setText(labelText.arg(QString::number(fps, 'f', 1)));
        _fpsLabel->adjustSize();
        frameCount = 0;
    }
}

void DataSource::startUpdates(const QList<QXYSeries *> &seriesList, QLabel *fpsLabel)
{
    _seriesList = seriesList;
    _fpsLabel = fpsLabel;

    _dataUpdater.setInterval(0);
    _dataUpdater.setSingleShot(true);
    QObject::connect(&_dataUpdater, &QTimer::timeout,
                     this, &DataSource::updateAllSeries);

    _fpsTimer.start();
    updateAllSeries();
}

void DataSource::generateData(int seriesCount, int rowCount, int colCount)
{
    /** Remove previous data */
    foreach (QVector<QVector<QPointF> > seriesData, _data) {
        foreach (QVector<QPointF> row, seriesData)
            row.clear();
    }

    _data.clear();

    qreal xAdjustment = 20.0 / (colCount * rowCount);
    qreal yMultiplier = 3.0 / qreal(seriesCount);

    /** Append the new data depending on the type */
    for (int k(0); k < seriesCount; k++) {
        QVector<QVector<QPointF> > seriesData;
        qreal height = qreal(k) * (10.0 / qreal(seriesCount)) + 0.3;
        for (int i(0); i < rowCount; i++) {
            QVector<QPointF> points;
            points.reserve(colCount);
            for (int j(0); j < colCount; j++) {
                qreal x(0);
                qreal y(0);
                /** data with sin + random component */
                y = height + (yMultiplier * qSin(3.14159265358979 / 50 * j)
                              + (yMultiplier * (qreal) rand() / (qreal) RAND_MAX));
                /** 0.000001 added to make values logaxis compatible */
                x = 0.000001 + 20.0 * (qreal(j) / qreal(colCount)) + (xAdjustment * qreal(i));
                points.append(QPointF(x, y));
            }
            seriesData.append(points);
        }
        _data.append(seriesData);
    }
}
