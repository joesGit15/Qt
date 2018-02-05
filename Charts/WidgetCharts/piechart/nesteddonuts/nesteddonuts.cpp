#include "nesteddonuts.h"

#include <QtCharts/qchart.h>
#include <QtCharts/qlegend.h>
#include <QtCharts/qpieslice.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qpieseries.h>

#include <QtCore/qtimer.h>
#include <QtCore/qdatetime.h>

#include <QtWidgets/qgridlayout.h>

NestedDonuts::NestedDonuts(QWidget *parent)
    : QWidget(parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    QChartView *chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);

    QChart *chart = chartView->chart();
    chart->legend()->setVisible(false);
    chart->setTitle("Nested donuts demo");
    chart->setAnimationOptions(QChart::AllAnimations);

    qreal minSize = 0.1;
    qreal maxSize = 0.9;
    int donutCount = 5;

    for (int i = 0; i < donutCount; i++) {
        QPieSeries *donut = new QPieSeries;
        int sliceCount =  3 + qrand() % 3;
        for (int j = 0; j < sliceCount; j++) {
            qreal value = 100 + qrand() % 100;
            QPieSlice *slice = new QPieSlice(QString("%1").arg(value), value);
            slice->setLabelVisible(true);
            slice->setLabelColor(Qt::white);
            slice->setLabelPosition(QPieSlice::LabelInsideTangential);
            connect(slice, &QPieSlice::hovered,
                    this, &NestedDonuts::explodeSlice);
            donut->append(slice);
            donut->setHoleSize(minSize + i * (maxSize - minSize) / donutCount);
            donut->setPieSize(minSize + (i + 1) * (maxSize - minSize) / donutCount);
        }
        _donuts.append(donut);
        chartView->chart()->addSeries(donut);
    }

    /** create main layout */
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout,
            this, &NestedDonuts::updateRotation);
    updateTimer->start(1250);
}

void NestedDonuts::updateRotation()
{
    for (int i = 0; i < _donuts.count(); i++) {
        QPieSeries *donut = _donuts.at(i);
        qreal phaseShift =  -50 + qrand() % 100;
        donut->setPieStartAngle(donut->pieStartAngle() + phaseShift);
        donut->setPieEndAngle(donut->pieEndAngle() + phaseShift);
    }
}

void NestedDonuts::explodeSlice(bool exploded)
{
    QPieSlice *slice = qobject_cast<QPieSlice *>(sender());
    if (exploded) {
        updateTimer->stop();
        qreal sliceStartAngle = slice->startAngle();
        qreal sliceEndAngle = slice->startAngle() + slice->angleSpan();

        QPieSeries *donut = slice->series();
        qreal seriesIndex = _donuts.indexOf(donut);
        for (int i = seriesIndex + 1; i < _donuts.count(); i++) {
            _donuts.at(i)->setPieStartAngle(sliceEndAngle);
            _donuts.at(i)->setPieEndAngle(360 + sliceStartAngle);
        }
    } else {
        for (int i = 0; i < _donuts.count(); i++) {
            _donuts.at(i)->setPieStartAngle(0);
            _donuts.at(i)->setPieEndAngle(360);
        }
        updateTimer->start();
    }
    slice->setExploded(exploded);
}
