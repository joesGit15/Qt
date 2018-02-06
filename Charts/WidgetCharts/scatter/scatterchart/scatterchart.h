#ifndef SCATTERCHART
#define SCATTERCHART

#include <QtCharts/qchartview.h>

using namespace QtCharts;

class ScatterChart : public QChartView
{
    Q_OBJECT
public:
    explicit ScatterChart(QWidget *parent = 0);
};

#endif // SCATTERCHART
