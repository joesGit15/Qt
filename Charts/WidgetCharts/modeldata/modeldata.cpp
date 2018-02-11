#include "modeldata.h"
#include "charttablewidget.h"

#include <QtWidgets/qboxlayout.h>

ModelData::ModelData(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Model Data");

    ChartTableWidget *table = new ChartTableWidget(this);
    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(table);
    setLayout(vlyt);
}
