#ifndef DYNAMICSPLINEWIDGET_H
#define DYNAMICSPLINEWIDGET_H

#include <QWidget>

namespace QtCharts {
    class QChart;
    class QValueAxis;
    class QSplineSeries;
}
using namespace QtCharts;

class DynamicSplineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DynamicSplineWidget(QWidget *parent = 0);

private slots:
    void StTimerOut();

private:
    qreal _x = 5;
    qreal _y = 1;
    QChart*          _chart  = 0;
    QValueAxis*      _axis   = 0;
    QSplineSeries*   _series = 0;
};

#endif // DYNAMICSPLINEWIDGET_H
