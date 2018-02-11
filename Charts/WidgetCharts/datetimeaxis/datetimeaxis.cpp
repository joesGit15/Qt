#include "datetimeaxis.h"

#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qdatetimeaxis.h>

#include <QtCore/qfile.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qtextstream.h>

#include <QtWidgets/qboxlayout.h>

using namespace QtCharts;

DatetimeAxis::DatetimeAxis(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Datetime Axis");

    QLineSeries *series = new QLineSeries;

    // data from http://www.swpc.noaa.gov/ftpdir/weekly/RecentIndices.txt
    // http://www.swpc.noaa.gov/ftpdir/weekly/README
    // http://www.weather.gov/disclaimer
    QFile sunSpots(":sun");
    if (!sunSpots.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream stream(&sunSpots);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.startsWith("#") || line.startsWith(":"))
            continue;
        QStringList values = line.split(" ", QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 15));
        series->append(momentInTime.toMSecsSinceEpoch(), values[2].toDouble());
    }
    sunSpots.close();

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Sunspots count (by Space Weather Prediction Center)");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Sunspots count");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->addWidget(chartView);
    setLayout(vlyt);
}
