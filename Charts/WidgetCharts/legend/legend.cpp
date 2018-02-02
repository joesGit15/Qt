#include "legend.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QFormLayout>

#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qgridlayout.h>

Legend::Legend(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("Legend");

    QGridLayout *btnLayout = new QGridLayout;
    QPushButton *detachLegendButton = new QPushButton("Toggle attached");
    connect(detachLegendButton, SIGNAL(clicked()), this, SLOT(toggleAttached()));
    btnLayout->addWidget(detachLegendButton, 0, 0);

    QPushButton *addSetButton = new QPushButton("add barset");
    connect(addSetButton, SIGNAL(clicked()), this, SLOT(addBarset()));
    btnLayout->addWidget(addSetButton, 2, 0);
    QPushButton *removeBarsetButton = new QPushButton("remove barset");
    connect(removeBarsetButton, SIGNAL(clicked()), this, SLOT(removeBarset()));
    btnLayout->addWidget(removeBarsetButton, 3, 0);

    QPushButton *alignButton = new QPushButton("Align (Bottom)");
    connect(alignButton, SIGNAL(clicked()), this, SLOT(setLegendAlignment()));
    btnLayout->addWidget(alignButton, 4, 0);

    QPushButton *boldButton = new QPushButton("Toggle bold");
    connect(boldButton, SIGNAL(clicked()), this, SLOT(toggleBold()));
    btnLayout->addWidget(boldButton, 8, 0);

    QPushButton *italicButton = new QPushButton("Toggle italic");
    connect(italicButton, SIGNAL(clicked()), this, SLOT(toggleItalic()));
    btnLayout->addWidget(italicButton, 9, 0);

    _legendPosX = new QDoubleSpinBox(this);
    _legendPosY = new QDoubleSpinBox(this);
    _legendWidth = new QDoubleSpinBox(this);
    _legendHeight = new QDoubleSpinBox(this);

    connect(_legendPosX, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));
    connect(_legendPosY, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));
    connect(_legendWidth, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));
    connect(_legendHeight, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));

    QFormLayout *legendLayout = new QFormLayout();
    legendLayout->addRow("HPos", _legendPosX);
    legendLayout->addRow("VPos", _legendPosY);
    legendLayout->addRow("Width", _legendWidth);
    legendLayout->addRow("Height", _legendHeight);
    _legendSettings = new QGroupBox("Detached legend");
    _legendSettings->setLayout(legendLayout);
    btnLayout->addWidget(_legendSettings);
    _legendSettings->setVisible(false);

    // Create chart view with the chart
    _chart = new QChart();
    _chartView = new QChartView(_chart, this);

    // Create spinbox to modify font size
    _fontSize = new QDoubleSpinBox();
    _fontSize->setValue(_chart->legend()->font().pointSizeF());
    connect(_fontSize, SIGNAL(valueChanged(double)), this, SLOT(fontSizeChanged()));

    QFormLayout *fontLayout = new QFormLayout();
    fontLayout->addRow("Legend font size", _fontSize);

    // Create layout for grid and detached legend
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addLayout(btnLayout, 0, 0);
    mainLayout->addLayout(fontLayout, 1, 0);
    mainLayout->addWidget(_chartView, 0, 1, 3, 1);
    setLayout(mainLayout);

    createSeries();
}

void Legend::createSeries()
{
    _series = new QBarSeries();
    addBarset();
    addBarset();
    addBarset();
    addBarset();

    _chart->addSeries(_series);
    _chart->setTitle("Legend detach example");
    _chart->createDefaultAxes();
//![1]
    _chart->legend()->setVisible(true);
    _chart->legend()->setAlignment(Qt::AlignBottom);
//![1]

    _chartView->setRenderHint(QPainter::Antialiasing);
}

void Legend::showLegendSpinbox()
{
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
}

void Legend::hideLegendSpinbox()
{
    _legendSettings->setVisible(false);
}


void Legend::toggleAttached()
{
    QLegend *legend = _chart->legend();
    if (legend->isAttachedToChart()) {
        //![2]
        legend->detachFromChart();
        _chart->legend()->setBackgroundVisible(true);
        _chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
        _chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
        //![2]
        showLegendSpinbox();
        updateLegendLayout();
    } else {
        //![3]
        legend->attachToChart();
        legend->setBackgroundVisible(false);
        //![3]
        hideLegendSpinbox();
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
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    switch (_chart->legend()->alignment()) {
    case Qt::AlignTop:
        _chart->legend()->setAlignment(Qt::AlignLeft);
        if (button)
            button->setText("Align (Left)");
        break;
    case Qt::AlignLeft:
        _chart->legend()->setAlignment(Qt::AlignBottom);
        if (button)
            button->setText("Align (Bottom)");
        break;
    case Qt::AlignBottom:
        _chart->legend()->setAlignment(Qt::AlignRight);
        if (button)
            button->setText("Align (Right)");
        break;
    default:
        if (button)
            button->setText("Align (Top)");
        _chart->legend()->setAlignment(Qt::AlignTop);
        break;
    }
}

void Legend::toggleBold()
{
    QFont font = _chart->legend()->font();
    font.setBold(!font.bold());
    _chart->legend()->setFont(font);
}

void Legend::toggleItalic()
{
    QFont font = _chart->legend()->font();
    font.setItalic(!font.italic());
    _chart->legend()->setFont(font);
}

void Legend::fontSizeChanged()
{
    QFont font = _chart->legend()->font();
    font.setPointSizeF(_fontSize->value());
    _chart->legend()->setFont(font);
}

void Legend::updateLegendLayout()
{
//![4]
    _chart->legend()->setGeometry(QRectF(_legendPosX->value(),
                                          _legendPosY->value(),
                                          _legendWidth->value(),
                                          _legendHeight->value()));
    _chart->legend()->update();
//![4]
}
