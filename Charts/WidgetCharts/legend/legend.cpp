#include "legend.h"

#include <QtCharts/qchart.h>
#include <QtCharts/qbarset.h>
#include <QtCharts/qlegend.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qchartview.h>

#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qgridlayout.h>

Legend::Legend(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("Legend");

    QPushButton *detachLegendButton = new QPushButton(tr("Toggle attached"),this);
    connect(detachLegendButton, &QPushButton::clicked,
            this, &Legend::toggleAttached);

    QPushButton *addSetButton = new QPushButton(tr("add barset"),this);
    connect(addSetButton, &QPushButton::clicked,
            this, &Legend::addBarset);

    QPushButton *removeBarsetButton = new QPushButton(tr("remove barset"),this);
    connect(removeBarsetButton, &QPushButton::clicked,
            this, &Legend::removeBarset);

    QPushButton *alignButton = new QPushButton(tr("Align (Bottom)"),this);
    connect(alignButton, &QPushButton::clicked,
            this, &Legend::setLegendAlignment);

    QPushButton *boldButton = new QPushButton(tr("Toggle bold"),this);
    connect(boldButton, &QPushButton::clicked,
            this, &Legend::toggleBold);

    QPushButton *italicButton = new QPushButton(tr("Toggle italic"),this);
    connect(italicButton, &QPushButton::clicked,
            this, &Legend::toggleItalic);

    _legendPosX = new QDoubleSpinBox(this);
    _legendPosY = new QDoubleSpinBox(this);
    _legendWidth = new QDoubleSpinBox(this);
    _legendHeight = new QDoubleSpinBox(this);

    connect(_legendPosX, SIGNAL(valueChanged(double)),
            this, SLOT(updateLegendLayout()));
    connect(_legendPosY, SIGNAL(valueChanged(double)),
            this, SLOT(updateLegendLayout()));
    connect(_legendWidth, SIGNAL(valueChanged(double)),
            this, SLOT(updateLegendLayout()));
    connect(_legendHeight, SIGNAL(valueChanged(double)),
            this, SLOT(updateLegendLayout()));

    QFormLayout *legendLayout = new QFormLayout;
    legendLayout->addRow("HPos", _legendPosX);
    legendLayout->addRow("VPos", _legendPosY);
    legendLayout->addRow("Width", _legendWidth);
    legendLayout->addRow("Height", _legendHeight);

    _legendSettings = new QGroupBox(tr("Detached legend"),this);
    _legendSettings->setLayout(legendLayout);
    _legendSettings->setVisible(false);

    QGridLayout *btnLayout = new QGridLayout;
    btnLayout->addWidget(detachLegendButton, 0, 0);
    btnLayout->addWidget(addSetButton, 2, 0);
    btnLayout->addWidget(removeBarsetButton, 3, 0);
    btnLayout->addWidget(alignButton, 4, 0);
    btnLayout->addWidget(boldButton, 8, 0);
    btnLayout->addWidget(italicButton, 9, 0);
    btnLayout->addWidget(_legendSettings);

    QChart *chart = new QChart;
    _chart = chart;
    _chartView = new QChartView(chart, this);

    QDoubleSpinBox *fontSize = new QDoubleSpinBox(this);
    _fontSize = fontSize;
    fontSize->setValue(chart->legend()->font().pointSizeF());
    connect(fontSize, SIGNAL(valueChanged(double)),
            this, SLOT(fontSizeChanged()));

    QFormLayout *fontLayout = new QFormLayout;
    fontLayout->addRow(tr("Legend font size"), fontSize);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addLayout(btnLayout, 0, 0);
    mainLayout->addLayout(fontLayout, 1, 0);
    mainLayout->addWidget(_chartView, 0, 1, 3, 1);
    setLayout(mainLayout);

    _series = new QBarSeries;
    addBarset();
    addBarset();

    chart->addSeries(_series);
    chart->setTitle("Legend detach example");
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    _chartView->setRenderHint(QPainter::Antialiasing);
}

void Legend::toggleAttached()
{
    QChart *chart = _chart;
    QLegend *legend = chart->legend();
    if (legend->isAttachedToChart()) {
        legend->detachFromChart();
        chart->legend()->setBackgroundVisible(true);
        chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
        chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));

        _legendSettings->setVisible(true);
        QRectF chartViewRect = _chartView->rect();

        _legendPosX->setMinimum(0);
        _legendPosX->setMaximum(chartViewRect.width());
        _legendPosX->setValue(150);

        _legendPosY->setMinimum(0);
        _legendPosY->setMaximum(chartViewRect.height());
        _legendPosY->setValue(150);

        _legendWidth->setMinimum(0);
        _legendWidth->setMaximum(chartViewRect.width());
        _legendWidth->setValue(150);

        _legendHeight->setMinimum(0);
        _legendHeight->setMaximum(chartViewRect.height());
        _legendHeight->setValue(75);
        updateLegendLayout();
    } else {
        legend->attachToChart();
        legend->setBackgroundVisible(false);
        _legendSettings->setVisible(false);
    }

    update();
}

void Legend::addBarset()
{
    QBarSet *barSet = new QBarSet(QString("set ") + QString::number(_series->count()));
    qreal delta = _series->count() * 0.1;
    *barSet << 1 + delta << 2 + delta << 3 + delta << 4 + delta;
    _series->append(barSet);
}

void Legend::removeBarset()
{
    QList<QBarSet *> sets = _series->barSets();
    if (sets.count() > 0) {
        _series->remove(sets.at(sets.count() - 1));
    }
}

void Legend::setLegendAlignment()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(btn == 0){
        return;
    }

    QChart *chart = _chart;
    switch (chart->legend()->alignment()) {
    case Qt::AlignTop:
        chart->legend()->setAlignment(Qt::AlignLeft);
        btn->setText("Align (Left)");
        break;
    case Qt::AlignLeft:
        chart->legend()->setAlignment(Qt::AlignBottom);
        btn->setText("Align (Bottom)");
        break;
    case Qt::AlignBottom:
        chart->legend()->setAlignment(Qt::AlignRight);
        btn->setText("Align (Right)");
        break;
    default:
        btn->setText("Align (Top)");
        chart->legend()->setAlignment(Qt::AlignTop);
        break;
    }
}

void Legend::toggleBold()
{
    QChart *chart = _chart;
    QFont font = chart->legend()->font();
    font.setBold(!font.bold());
    chart->legend()->setFont(font);
}

void Legend::toggleItalic()
{
    QChart *chart = _chart;
    QFont font = chart->legend()->font();
    font.setItalic(!font.italic());
    chart->legend()->setFont(font);
}

void Legend::fontSizeChanged()
{
    QChart *chart = _chart;
    QFont font = chart->legend()->font();
    font.setPointSizeF(_fontSize->value());
    chart->legend()->setFont(font);
}

void Legend::updateLegendLayout()
{
    QChart *chart = _chart;
    chart->legend()->setGeometry(QRectF(_legendPosX->value(),
                                          _legendPosY->value(),
                                          _legendWidth->value(),
                                          _legendHeight->value()));
    chart->legend()->update();
}
