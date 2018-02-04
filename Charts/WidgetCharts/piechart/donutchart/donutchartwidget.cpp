#include "donutchartwidget.h"

#include <QtWidgets/qboxlayout.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieslice.h>

using namespace QtCharts;

DonutChartWidget::DonutChartWidget(QWidget *parent)
    :QWidget(parent)
{
    setObjectName("DonutChart");

    QChartView *view = new QChartView(this);
    view->setRenderHint(QPainter::Antialiasing);

    QChart *chart = view->chart();
    chart->setTitle(tr("this is chart title"));
    chart->legend()->setFont(QFont("Arial",7));
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    QPieSeries *series = new QPieSeries;
    series->setHoleSize(0.35);
    series->append("Protein 4.2%",4.2);
    series->append("Other 23.8%",23.8);
    series->append("Carbs 56.4%",56.4);

    QPieSlice *slice = series->append("Fat 15.6%",15.6);
    slice->setExploded();
    slice->setLabelVisible(true);

    chart->addSeries(series);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(view);
    setLayout(vlyt);
}
