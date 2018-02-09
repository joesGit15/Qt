#include "tablewidget.h"

#include <QtCharts/qchart.h>
#include <QtCharts/qbarset.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qbarseries.h>

#include <QtCharts/qlineseries.h>

#include <QtCharts/qvxymodelmapper.h>
#include <QtCharts/qvbarmodelmapper.h>

#include <QtCharts/qbarcategoryaxis.h>

#include <QtWidgets/qtableview.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qheaderview.h>

using namespace QtCharts;

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Model Mapper");

    CustomTableModel *model = new CustomTableModel(this);
    _model = model;

    QTableView *tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->setMinimumWidth(300);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model->setParent(tableView);

    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);

    QBarSeries *series = new QBarSeries;

    int first = 3;
    int count = 5;
    QVBarModelMapper *mapper = new QVBarModelMapper(this);
    mapper->setFirstBarSetColumn(1);
    mapper->setLastBarSetColumn(4);
    mapper->setFirstRow(first);
    mapper->setRowCount(count);
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);

    QString seriesColorHex = "#000000";

    /** get the color of the series and use it for showing the mapped area */
    QList<QBarSet *> barsets = series->barSets();
    for (int i = 0; i < barsets.count(); i++) {
        seriesColorHex = "#" + QString::number(barsets.at(i)->brush().color().rgb(), 16).right(6).toUpper();
        model->addMapping(seriesColorHex, QRect(1 + i, first, 1, barsets.at(i)->count()));
    }

    QStringList categories;
    categories << "April" << "May" << "June" << "July" << "August";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);

    QGridLayout *glyt = new QGridLayout;
    glyt->addWidget(tableView, 1, 0);
    glyt->addWidget(chartView, 1, 1);
    glyt->setColumnStretch(1, 1);
    glyt->setColumnStretch(0, 0);
    setLayout(glyt);
}
