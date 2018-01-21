#include "themewidget.h"

#include <QtCharts/qlegend.h>
#include <QtCharts/qbarset.h>
#include <QtCharts/qpieslice.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qareaseries.h>
#include <QtCharts/qsplineseries.h>
#include <QtCharts/qscatterseries.h>
#include <QtCharts/qstackedbarseries.h>

#include <QtWidgets/qlabel.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qgridlayout.h>
#include <QtCore/qdatetime.h>

ThemeWidget::ThemeWidget(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("Chart Theme");
    _dataTable = generateRandomData(_listCount, _valueMax, _valueCount);

    QComboBox *themeComboBox = new QComboBox();
    _themeComboBox = themeComboBox;
    themeComboBox->addItem("Light", QChart::ChartThemeLight);
    themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    themeComboBox->addItem("Qt", QChart::ChartThemeQt);

    QComboBox *animationComboBox = new QComboBox();
    _animatedComboBox = animationComboBox;
    animationComboBox->addItem("No Animations", QChart::NoAnimation);
    animationComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    animationComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    animationComboBox->addItem("All Animations", QChart::AllAnimations);

    QComboBox *legendComboBox = new QComboBox();
    _legendComboBox = legendComboBox;
    legendComboBox->addItem("No Legend ", 0);
    legendComboBox->addItem("Legend Top", Qt::AlignTop);
    legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    legendComboBox->addItem("Legend Right", Qt::AlignRight);

    _antialiasCheckBox = new QCheckBox("Anti-aliasing");

    connect(themeComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateUI()));
    connect(animationComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateUI()));
    connect(legendComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateUI()));
    connect(_antialiasCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(updateUI()));

    QGridLayout *baseLayout = new QGridLayout;
    QHBoxLayout *settingsLayout = new QHBoxLayout;
    settingsLayout->addWidget(new QLabel("Theme:"));
    settingsLayout->addWidget(_themeComboBox);
    settingsLayout->addWidget(new QLabel("Animation:"));
    settingsLayout->addWidget(_animatedComboBox);
    settingsLayout->addWidget(new QLabel("Legend:"));
    settingsLayout->addWidget(_legendComboBox);
    settingsLayout->addWidget(_antialiasCheckBox);
    settingsLayout->addStretch();
    baseLayout->addLayout(settingsLayout, 0, 0, 1, 3);

    //create charts

    QChartView *chartView = 0;

    chartView = new QChartView(createAreaChart());
    baseLayout->addWidget(chartView, 1, 0);
    _charts << chartView;

    chartView = new QChartView(createBarChart());
    baseLayout->addWidget(chartView, 1, 1);
    _charts << chartView;

    chartView = new QChartView(createLineChart());
    baseLayout->addWidget(chartView, 1, 2);
    _charts << chartView;

    chartView = new QChartView(createPieChart());
    /** funny things happen if the pie slice labels no not fit the screen...*/
    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    baseLayout->addWidget(chartView, 2, 0);
    _charts << chartView;

    chartView = new QChartView(createSplineChart());
    baseLayout->addWidget(chartView, 2, 1);
    _charts << chartView;

    chartView = new QChartView(createScatterChart());
    baseLayout->addWidget(chartView, 2, 2);
    _charts << chartView;

    setLayout(baseLayout);

    /** Set defaults */
    _antialiasCheckBox->setChecked(true);
    updateUI();
}

ThemeWidget::~ThemeWidget()
{
}

DataTable ThemeWidget::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    for (int i=0; i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j=0; j < valueCount; j++) {
            yValue = yValue + (qreal)(qrand() % valueMax) / (qreal) valueCount;
            QPointF value((j + (qreal) rand() / (qreal) RAND_MAX) * ((qreal) _valueMax / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

QChart *ThemeWidget::createAreaChart() const
{
    QChart *chart = new QChart;
    chart->setTitle("Area chart");

    /** The lower series initialized to zero values */
    QLineSeries *lowerSeries = 0;
    QString name("Series ");
    int nameIndex = 0;
    for (int i(0); i < _dataTable.count(); i++) {
        QLineSeries *upperSeries = new QLineSeries(chart);
        for (int j(0); j < _dataTable[i].count(); j++) {
            Data data = _dataTable[i].at(j);
            if (lowerSeries) {
                const QVector<QPointF>& points = lowerSeries->pointsVector();
                upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
            } else {
                upperSeries->append(QPointF(j, data.first.y()));
            }
        }
        QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
        area->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(area);
        chart->createDefaultAxes();
        lowerSeries = upperSeries;
    }

    return chart;
}

QChart *ThemeWidget::createBarChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Bar chart");

    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for (int i(0); i < _dataTable.count(); i++) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        for (Data data: _dataTable[i]){
            *set << data.first.y();
        }
        series->append(set);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();

    return chart;
}

QChart *ThemeWidget::createLineChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Line chart");

    QString name("Series ");
    int nameIndex = 0;
    for (DataList list: _dataTable) {
        QLineSeries *series = new QLineSeries(chart);
        for (Data data: list){
            series->append(data.first);
        }
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    chart->createDefaultAxes();

    return chart;
}

QChart *ThemeWidget::createPieChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Pie chart");

    qreal pieSize = 1.0 / _dataTable.count();
    for (int i = 0; i < _dataTable.count(); i++) {
        QPieSeries *series = new QPieSeries(chart);
        for (Data data: _dataTable[i]) {
            QPieSlice *slice = series->append(data.second, data.first.y());
            if (data == _dataTable[i].first()) {
                slice->setLabelVisible();
                slice->setExploded();
            }
        }
        qreal hPos = (pieSize / 2) + (i / (qreal) _dataTable.count());
        series->setPieSize(pieSize);
        series->setHorizontalPosition(hPos);
        series->setVerticalPosition(0.5);
        chart->addSeries(series);
    }

    return chart;
}

QChart *ThemeWidget::createSplineChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Spline chart");
    QString name("Series ");
    int nameIndex = 0;
    for (DataList list: _dataTable) {
        QSplineSeries *series = new QSplineSeries(chart);
        for (Data data: list){
            series->append(data.first);
        }
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    chart->createDefaultAxes();
    return chart;
}

QChart *ThemeWidget::createScatterChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Scatter chart");
    QString name("Series ");
    int nameIndex = 0;
    for (DataList list: _dataTable) {
        QScatterSeries *series = new QScatterSeries(chart);
        for (Data data: list){
            series->append(data.first);
        }
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    chart->createDefaultAxes();
    return chart;
}

void ThemeWidget::updateUI()
{
    int idx = _themeComboBox->currentIndex();
    QChart::ChartTheme theme;
    theme = (QChart::ChartTheme) _themeComboBox->itemData(idx).toInt();

    if (_charts.at(0)->chart()->theme() != theme) {
        for (QChartView *chartView: _charts)
            chartView->chart()->setTheme(theme);
#if 1
        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        } else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
#endif
    }

    bool checked = _antialiasCheckBox->isChecked();
    for (QChartView *chart: _charts){
        chart->setRenderHint(QPainter::Antialiasing, checked);
    }

    idx = _animatedComboBox->currentIndex();
    QChart::AnimationOptions options(_animatedComboBox->itemData(idx).toInt());
    if (_charts.at(0)->chart()->animationOptions() != options) {
        for (QChartView *chartView: _charts){
            chartView->chart()->setAnimationOptions(options);
        }
    }

    idx = _legendComboBox->currentIndex();
    Qt::Alignment alignment(_legendComboBox->itemData(idx).toInt());

    if (!alignment) {
        for (QChartView *chartView: _charts){
            chartView->chart()->legend()->hide();
        }
    } else {
        for (QChartView *chartView: _charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }
}
