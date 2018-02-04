#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtCore/qobject.h>

#include <QtCore/qtimer.h>
#include <QtCore/qpoint.h>
#include <QtCore/qvector.h>
#include <QtCore/qelapsedtimer.h>

class QLabel;

namespace QtCharts {
    class QXYSeries;
    class QAbstractSeries;
}
using namespace QtCharts;

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0);

    void startUpdates(const QList<QXYSeries *> &seriesList, QLabel *fpsLabel);

public slots:
    void generateData(int seriesCount, int rowCount, int colCount);
    void update(QAbstractSeries *series, int seriesIndex);
    void handleSceneChanged();
    void updateAllSeries();

private:
    int _index = -1;

    QList<QXYSeries *> _seriesList;

    QLabel *_fpsLabel;

    QTimer _dataUpdater;
    QElapsedTimer _fpsTimer;

    QVector<QVector<QVector<QPointF> > > _data;
};

#endif // DATASOURCE_H
