#include "stackedbardrilldown.h"

#include <QtWidgets/qboxlayout.h>

#include <QtCharts/qbarset.h>
#include <QtCharts/qlegend.h>
#include <QtCharts/qchartview.h>

#include "drilldownseries.h"
#include "bardrilldownchart.h"

using namespace QtCharts;

StackedBarDrilldown::StackedBarDrilldown(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Stacked Bar Drilldown");

    BarDrilldownChart *drilldownChart =  new BarDrilldownChart;
    drilldownChart->legend()->setVisible(true);
    drilldownChart->legend()->setAlignment(Qt::AlignBottom);
    drilldownChart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList months;
    months << "May" << "Jun" << "Jul" << "Aug" << "Sep";
    QStringList weeks;
    weeks << "week 1" << "week 2" << "week 3" << "week 4";

    QStringList plants;
    plants << "Habanero" << "Lemon Drop" << "Starfish" << "Aji Amarillo";

    DrilldownBarSeries *seasonSeries = new DrilldownBarSeries(months, drilldownChart);
    seasonSeries->setName("Crop by month - Season");

    /** Each month in season series has drilldown series for weekly data */
    for (int month = 0; month < months.count(); month++) {

        /** Create drilldown series for every week */
        DrilldownBarSeries *weeklySeries = new DrilldownBarSeries(weeks, drilldownChart);
        seasonSeries->mapDrilldownSeries(month, weeklySeries);

        /** Drilling down from weekly data brings us back to season data.*/
        for (int week = 0; week < weeks.count(); week++) {
            weeklySeries->mapDrilldownSeries(week, seasonSeries);
            weeklySeries->setName(QString("Crop by week - " + months.at(month)));
        }

        connect(weeklySeries, &DrilldownBarSeries::clicked,
                drilldownChart, &BarDrilldownChart::handleClicked);
    }

    /** Enable drilldown from season series using clicked signal */
    connect(seasonSeries, &DrilldownBarSeries::clicked,
            drilldownChart, &BarDrilldownChart::handleClicked);

    /** Fill monthly and weekly series with data */
    foreach (QString plant, plants) {
        QBarSet *monthlyCrop = new QBarSet(plant);
        for (int month = 0; month < months.count(); month++) {
            QBarSet *weeklyCrop = new QBarSet(plant);
            for (int week = 0; week < weeks.count(); week++)
                *weeklyCrop << (qrand() % 20);

            /** Get the drilldown series from season series and add crop to it.*/
            seasonSeries->drilldownSeries(month)->append(weeklyCrop);
            *monthlyCrop << weeklyCrop->sum();
        }

        seasonSeries->append(monthlyCrop);
    }

    /** Show season series in initial view */
    drilldownChart->changeSeries(seasonSeries);
    drilldownChart->setTitle(seasonSeries->name());
    drilldownChart->axisX()->setGridLineVisible(false);

    QChartView* view = new QChartView(drilldownChart,this);
    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addWidget(view);
    setLayout(vlyt);
}
