#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtWidgets/qwidget.h>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
QT_END_NAMESPACE

namespace QtCharts {
    class QChartView;
    class QChart;
}
using namespace QtCharts;

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

class ThemeWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = 0);
    ~ThemeWidget();

private slots:
    void updateUI();

private:
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    QChart *createAreaChart() const;
    QChart *createBarChart() const;
    QChart *createPieChart() const;
    QChart *createLineChart() const;
    QChart *createSplineChart() const;
    QChart *createScatterChart() const;

private:
    int _listCount = 3;
    int _valueMax  = 10;
    int _valueCount= 7;

    DataTable           _dataTable;
    QList<QChartView *> _charts;

    QComboBox *_themeComboBox    = 0;
    QComboBox *_animatedComboBox = 0;
    QComboBox *_legendComboBox   = 0;
    QCheckBox *_antialiasCheckBox= 0;
};

#endif /* THEMEWIDGET_H */
