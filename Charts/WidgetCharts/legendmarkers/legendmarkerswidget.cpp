#include "legendmarkerswidget.h"

#include <QtCharts/qchart.h>
#include <QtCharts/qlegend.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qlegendmarker.h>
#include <QtCharts/qxylegendmarker.h>

#include <QtCore/qmath.h>
#include <QtWidgets/qgridlayout.h>

LegendMarkersWidget::LegendMarkersWidget(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("LegendMarkers");

    QChart *chart = new QChart;
    _chart = chart;
    chart->setTitle("Legendmarker example (click on legend)");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(_chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    QGridLayout *glyt = new QGridLayout;
    glyt->addWidget(chartView, 0, 1, 3, 1);
    setLayout(glyt);

    addSeries(chart);
    addSeries(chart);
    addSeries(chart);
    addSeries(chart);

    for(QLegendMarker* marker: chart->legend()->markers()) {
        /** Disconnect possible existing connection to avoid multiple connections */
        disconnect(marker, &QLegendMarker::clicked,
                   this, &LegendMarkersWidget::handleMarkerClicked);
        connect(marker, &QLegendMarker::clicked,
                this, &LegendMarkersWidget::handleMarkerClicked);
    }
}

void LegendMarkersWidget::addSeries(QChart *chart)
{
    Q_ASSERT(0 != chart);
    QList<QLineSeries *> &ltSeries = _series;

    QLineSeries *series = new QLineSeries;
    ltSeries.append(series);

    series->setName(QString("line " + QString::number(ltSeries.count())));

    /** Make some sine wave for data */
    QList<QPointF> data;
    int offset = chart->series().count();
    for (int i = 0; i < 360; i++) {
        qreal x = offset * 20 + i;
        data.append(QPointF(i, qSin(2.0 * 3.141592 * x / 360.0)));
    }

    series->append(data);
    chart->addSeries(series);

    if (ltSeries.count() == 1) {
        chart->createDefaultAxes();
    }
}

void LegendMarkersWidget::handleMarkerClicked()
{
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    Q_ASSERT(marker != 0);

    if(marker->type() != QLegendMarker::LegendMarkerTypeXY){
        return;
    }

    marker->series()->setVisible(!marker->series()->isVisible());

    /**
      * Turn legend marker back to visible, since hiding series also hides the marker
      * and we don't want it to happen now.
      * */
    marker->setVisible(true);

    /** Dim the marker, if series is not visible */
    qreal alpha = 1.0;

    if (!marker->series()->isVisible()) {
        alpha = 0.5;
    }

    QColor color;
    QBrush brush = marker->labelBrush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setLabelBrush(brush);

    brush = marker->brush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setBrush(brush);

    QPen pen = marker->pen();
    color = pen.color();
    color.setAlphaF(alpha);
    pen.setColor(color);
    marker->setPen(pen);
}
