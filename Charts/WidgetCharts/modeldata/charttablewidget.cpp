#include "charttablewidget.h"

#include "charttablemodel.h"

#include <QtWidgets/qtableview.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qheaderview.h>

#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qvxymodelmapper.h>

using namespace QtCharts;

ChartTableWidget::ChartTableWidget(QWidget *parent)
    : QWidget(parent)
{
    /** create simple model for storing data user's table data model */
    ChartTableModel *model = new ChartTableModel;

    /** create table view and add model to it */
    QTableView *tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);

    QLineSeries *series = new QLineSeries;
    series->setName("Line 1");
    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);

    /** for storing color hex from the series */
    QString seriesColorHex = "#000000";

    /** get the color of the series and use it for showing the mapped area */
    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(0, 0, 2, model->rowCount()));

    series = new QLineSeries;
    series->setName("Line 2");

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(2);
    mapper->setYColumn(3);
    mapper->setSeries(series);
    mapper->setModel(model);

    chart->addSeries(series);

    /** get the color of the series and use it for showing the mapped area */
    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(2, 0, 2, model->rowCount()));

    chart->createDefaultAxes();

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
