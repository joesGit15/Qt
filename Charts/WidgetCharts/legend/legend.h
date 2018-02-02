#ifndef LEGEND_H
#define LEGEND_H

#include <QtWidgets/qwidget.h>

QT_BEGIN_NAMESPACE
class QGroupBox;
class QGridLayout;
class QDoubleSpinBox;
QT_END_NAMESPACE

namespace QtCharts {
    class QChartGlobal;
    class QChart;
    class QChartView;
    class QBarSeries;
}
using namespace QtCharts;

class Legend : public QWidget
{
    Q_OBJECT
public:
    explicit Legend(QWidget *parent = 0);
    void createSeries();
    void showLegendSpinbox();
    void hideLegendSpinbox();

public slots:
    void toggleAttached();
    void addBarset();
    void removeBarset();

    void setLegendAlignment();

    void toggleBold();
    void toggleItalic();
    void fontSizeChanged();

    void updateLegendLayout();

private:
    QChart *_chart;
    QBarSeries *_series;
    QChartView *_chartView;

    QDoubleSpinBox *_fontSize;

    // For detached layout
    QGroupBox *_legendSettings;
    QDoubleSpinBox *_legendPosX;
    QDoubleSpinBox *_legendPosY;
    QDoubleSpinBox *_legendWidth;
    QDoubleSpinBox *_legendHeight;
};

#endif // LEGEND_H
