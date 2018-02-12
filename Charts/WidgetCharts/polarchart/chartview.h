#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/qchartview.h>
#include <QtCharts/qpolarchart.h>

using namespace QtCharts;

class ChartView : public QChartView
{
public:
    ChartView(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void switchChartType();
};

#endif
