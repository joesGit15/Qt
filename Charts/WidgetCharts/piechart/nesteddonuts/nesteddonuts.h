#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/qpieseries.h>

class QTimer;

using namespace QtCharts;

class NestedDonuts : public QWidget
{
    Q_OBJECT

public:
    NestedDonuts(QWidget *parent = 0);

public slots:
    void updateRotation();
    void explodeSlice(bool exploded);

private:
    QTimer *updateTimer = 0;

    QList<QPieSeries *> _donuts;
};

#endif // WIDGET_H
