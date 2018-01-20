#ifndef CALLOUTVIEW_H
#define CALLOUTVIEW_H

#include <QtWidgets/qgraphicsview.h>
#include <QtCharts/qchartglobal.h>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

class GraphicsCalloutItem;
QT_CHARTS_USE_NAMESPACE

class CallOutView: public QGraphicsView
{
    Q_OBJECT

public:
    CallOutView(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

private:
    QGraphicsSimpleTextItem *_coordX = 0;
    QGraphicsSimpleTextItem *_coordY = 0;

    QChart *_chart    = 0;
    GraphicsCalloutItem *_tooltip = 0;
    QList<GraphicsCalloutItem *> _callouts;
};
#endif
