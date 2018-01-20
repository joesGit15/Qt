#ifndef GRAPHICSCALLOUTITEM_H
#define GRAPHICSCALLOUTITEM_H

#include <QtGui/qfont.h>
#include <QtWidgets/qgraphicsitem.h>
#include <QtCharts/qchartglobal.h>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class GraphicsCalloutItem : public QGraphicsItem
{
public:
    GraphicsCalloutItem(QChart *parent);

    void setText(const QString &text);
    void setAnchor(QPointF point);
    void updateGeometry();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QString _text;
    QRectF _textRect;
    QRectF _rect;
    QPointF _anchor;
    QFont _font;
    QChart *_chart = 0;
};

#endif // CALLOUT_H
