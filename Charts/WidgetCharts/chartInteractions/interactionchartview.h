#ifndef INTERACTIONCHARTVIEW_H
#define INTERACTIONCHARTVIEW_H

#include <QtCharts/qchartview.h>

class InteractionChart;

using namespace QtCharts;

class InteractionChartView : public QChartView
{
public:
    InteractionChartView(InteractionChart *chart, QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint _mousePos;
    InteractionChart *_chart     = 0;
};

#endif
