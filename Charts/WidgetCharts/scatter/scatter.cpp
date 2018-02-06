#include "scatter.h"

#include <QtWidgets/qtoolbox.h>
#include <QtWidgets/qboxlayout.h>

#include "scatterchart/scatterchart.h"
#include "scatterinteractions/scatterinteractions.h"

Scatter::Scatter(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Scatter");

    QToolBox *tbox = new QToolBox(this);
    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(tbox);
    setLayout(vlyt);

    QWidget *widget = 0;

    widget = new ScatterChart(this);
    tbox->addItem(widget,widget->objectName());

    widget = new ScatterInterActions(this);
    tbox->addItem(widget,widget->objectName());
}
