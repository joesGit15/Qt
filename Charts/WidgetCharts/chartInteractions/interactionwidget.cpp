#include "interactionwidget.h"
#include "interactionchart.h"
#include "interactionchartview.h"

#include <QtWidgets/qboxlayout.h>

using namespace QtCharts;

tInteractionsWidget::tInteractionsWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("ChartInteractions");

    InteractionChart *chart = new InteractionChart;
    InteractionChartView *chartView = new InteractionChartView(chart,this);

    QHBoxLayout* vlyt = new QHBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);

}
