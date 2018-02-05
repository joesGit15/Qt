#include "piechart.h"

#include <Qtwidgets/qtoolbox.h>
#include <QtWidgets/qboxlayout.h>

#include "donutchart/donutchartwidget.h"
#include "donutbreakdown/donutbreakdownwidget.h"
#include "piechartdrilldown/drilldownwidget.h"
#include "piechartcustomization/piechartcustomization.h"
#include "nesteddonuts/nesteddonuts.h"

PieChart::PieChart(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("PieChart");

    QToolBox *tbox = new QToolBox(this);
    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(tbox);
    setLayout(vlyt);

    QWidget *widget = 0;

    widget = new NestedDonuts(this);
    tbox->addItem(widget,widget->objectName());

    widget = new PieChartCustomization(this);
    tbox->addItem(widget,widget->objectName());

    widget = new DrilldownWidget(this);
    tbox->addItem(widget,widget->objectName());

    widget = new DonutChartWidget(this);
    tbox->addItem(widget,widget->objectName());

    widget = new DonutBreakDownWidget(this);
    tbox->addItem(widget,widget->objectName());
}
