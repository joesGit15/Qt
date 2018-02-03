#ifndef LEGENDMARKERSWIDGET_H
#define LEGENDMARKERSWIDGET_H

#include <QtWidgets/QWidget>

namespace QtCharts {
    class QChart;
    class QChartView;
    class QLineSeries;
}
using namespace QtCharts;

class LegendMarkersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LegendMarkersWidget(QWidget *parent = 0);

public slots:
    void addSeries(QChart *chart);
    void handleMarkerClicked();

private:
    QChart *_chart;
    QChartView *_chartView;
    QList<QLineSeries *> _series;
};

#endif // LEGENDMARKERSWIDGET_H
