#include "interactionwidget.h"
#include "interactionchart.h"
#include "interactionchartview.h"

#include <QtWidgets>

using namespace QtCharts;

tInteractionsWidget::tInteractionsWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("ChartInteractions");

    QPushButton *btn;
    QHBoxLayout *hlyt;
    QVBoxLayout *vlyt;

    btn = new QPushButton(tr("ChartShot"),this);
    connect(btn,&QPushButton::clicked,
            this,&tInteractionsWidget::StBtnChartShot);

    hlyt = new QHBoxLayout;
    hlyt->addWidget(btn);
    hlyt->addStretch(1);

    InteractionChart *chart = new InteractionChart;
    InteractionChartView *chartView = new InteractionChartView(chart,this);
    _chartView = chartView;

    vlyt = new QVBoxLayout;
    vlyt->addLayout(hlyt);
    vlyt->addWidget(chartView);
    setLayout(vlyt);

    chartView->setVisible(false);
}

void tInteractionsWidget::StBtnChartShot()
{

    QImage img(800,800,QImage::Format_RGB32);
    QPainter painter(&img);

    QChartView* view = static_cast<QChartView*>(_chartView);
#if 1
    view->render(&painter);
#else
    QRect viewport = view.viewport()->rect();
    view.render(&painter,
                QRectF(0, printer.height() / 2,
                       printer.width(), printer.height() / 2),
                viewport.adjusted(0, 0, 0, -viewport.height() / 2));
#endif
    img.save("a.jpg");
}
