#ifndef CHARTINTERACTIONS_H
#define CHARTINTERACTIONS_H

#include <QWidget>

class tInteractionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit tInteractionsWidget(QWidget *parent = 0);

private slots:
    void StBtnChartShot();

private:
    void*   _chartView;
};

#endif // CHARTINTERACTIONS_H
