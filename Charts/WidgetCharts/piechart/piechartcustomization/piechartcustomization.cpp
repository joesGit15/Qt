#include "piechartcustomization.h"
#include "customslice.h"
#include "pentool.h"
#include "brushtool.h"

#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qfontdialog.h>

#include <QtCharts/qchartview.h>
#include <QtCharts/qpieseries.h>

PieChartCustomization::PieChartCustomization(QWidget *parent)
    : QWidget(parent)
{
    _themeComboBox = new QComboBox(this);
    _themeComboBox->addItem("Light", QChart::ChartThemeLight);
    _themeComboBox->addItem("BlueCerulean", QChart::ChartThemeBlueCerulean);
    _themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    _themeComboBox->addItem("BrownSand", QChart::ChartThemeBrownSand);
    _themeComboBox->addItem("BlueNcs", QChart::ChartThemeBlueNcs);
    _themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    _themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    _themeComboBox->addItem("Qt", QChart::ChartThemeQt);
    connect(_themeComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updateChartSettings()));

    _aaCheckBox = new QCheckBox(this);
    connect(_aaCheckBox, &QCheckBox::toggled,
            this, &PieChartCustomization::updateChartSettings);

    _animationsCheckBox = new QCheckBox(this);
    _animationsCheckBox->setCheckState(Qt::Checked);
    connect(_animationsCheckBox, &QCheckBox::toggled,
            this, &PieChartCustomization::updateChartSettings);

    _legendCheckBox = new QCheckBox(this);
    connect(_legendCheckBox, &QCheckBox::toggled,
            this, &PieChartCustomization::updateChartSettings);

    QFormLayout *chartSettingsLayout = new QFormLayout;
    chartSettingsLayout->addRow("Theme", _themeComboBox);
    chartSettingsLayout->addRow("Antialiasing", _aaCheckBox);
    chartSettingsLayout->addRow("Animations", _animationsCheckBox);
    chartSettingsLayout->addRow("Legend", _legendCheckBox);

    QGroupBox *chartSettings = new QGroupBox("Chart",this);
    chartSettings->setLayout(chartSettingsLayout);

    _series = new QPieSeries;
    *_series << new CustomSlice("Slice 1", 10.0);
    *_series << new CustomSlice("Slice 2", 20.0);
    *_series << new CustomSlice("Slice 3", 30.0);
    *_series << new CustomSlice("Slice 4", 40.0);
    *_series << new CustomSlice("Slice 5", 50.0);
    _series->setLabelsVisible();

    _hPosition = new QDoubleSpinBox(this);
    _hPosition->setMinimum(0.0);
    _hPosition->setMaximum(1.0);
    _hPosition->setSingleStep(0.1);
    _hPosition->setValue(_series->horizontalPosition());
    connect(_hPosition,SIGNAL(valueChanged(double)),
            this,SLOT(updateSerieSettings()));

    _vPosition = new QDoubleSpinBox(this);
    _vPosition->setMinimum(0.0);
    _vPosition->setMaximum(1.0);
    _vPosition->setSingleStep(0.1);
    _vPosition->setValue(_series->verticalPosition());
    connect(_vPosition,SIGNAL(valueChanged(double)),
            this,SLOT(updateSerieSettings()));

    _sizeFactor = new QDoubleSpinBox(this);
    _sizeFactor->setMinimum(0.0);
    _sizeFactor->setMaximum(1.0);
    _sizeFactor->setSingleStep(0.1);
    _sizeFactor->setValue(_series->pieSize());
    connect(_sizeFactor,SIGNAL(valueChanged(double)),
            this,SLOT(updateSerieSettings()));

    _startAngle = new QDoubleSpinBox(this);
    _startAngle->setMinimum(-720);
    _startAngle->setMaximum(720);
    _startAngle->setValue(_series->pieStartAngle());
    _startAngle->setSingleStep(1);
    connect(_startAngle,SIGNAL(valueChanged(double)),
            this,SLOT(updateSerieSettings()));

    _endAngle = new QDoubleSpinBox(this);
    _endAngle->setMinimum(-720);
    _endAngle->setMaximum(720);
    _endAngle->setValue(_series->pieEndAngle());
    _endAngle->setSingleStep(1);
    connect(_endAngle,SIGNAL(valueChanged(double)),
            this,SLOT(updateSerieSettings()));

    _holeSize = new QDoubleSpinBox(this);
    _holeSize->setMinimum(0.0);
    _holeSize->setMaximum(1.0);
    _holeSize->setSingleStep(0.1);
    _holeSize->setValue(_series->holeSize());
    connect(_holeSize,SIGNAL(valueChanged(double)),
            this,SLOT(updateSerieSettings()));

    QPushButton *appendSlice = new QPushButton("Append slice");
    connect(appendSlice, SIGNAL(clicked()), this, SLOT(appendSlice()));

    QPushButton *insertSlice = new QPushButton("Insert slice");
    connect(insertSlice, SIGNAL(clicked()), this, SLOT(insertSlice()));

    QPushButton *removeSlice = new QPushButton("Remove selected slice");
    connect(removeSlice, SIGNAL(clicked()), this, SLOT(removeSlice()));

    QFormLayout *seriesSettingsLayout = new QFormLayout;
    seriesSettingsLayout->addRow("Horizontal position", _hPosition);
    seriesSettingsLayout->addRow("Vertical position", _vPosition);
    seriesSettingsLayout->addRow("Size factor", _sizeFactor);
    seriesSettingsLayout->addRow("Start angle", _startAngle);
    seriesSettingsLayout->addRow("End angle", _endAngle);
    seriesSettingsLayout->addRow("Hole size", _holeSize);
    seriesSettingsLayout->addRow(appendSlice);
    seriesSettingsLayout->addRow(insertSlice);
    seriesSettingsLayout->addRow(removeSlice);
    QGroupBox *seriesSettings = new QGroupBox("Series",this);
    seriesSettings->setLayout(seriesSettingsLayout);

    _sliceName = new QLineEdit("<click a slice>",this);
    _sliceName->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(_sliceName, &QLineEdit::textChanged,
            this, &PieChartCustomization::updateSliceSettings);

    _sliceValue = new QDoubleSpinBox(this);
    _sliceValue->setMaximum(1000);
    connect(_sliceValue, SIGNAL(valueChanged(double)),
            this, SLOT(updateSliceSettings()));

    _sliceLabelVisible = new QCheckBox(this);
    connect(_sliceLabelVisible, &QCheckBox::toggled,
            this, &PieChartCustomization::updateSliceSettings);

    _sliceLabelArmFactor = new QDoubleSpinBox(this);
    _sliceLabelArmFactor->setSingleStep(0.01);
    connect(_sliceLabelArmFactor, SIGNAL(valueChanged(double)),
            this, SLOT(updateSliceSettings()));

    _sliceExploded = new QCheckBox(this);
    connect(_sliceExploded, &QCheckBox::toggled,
            this, &PieChartCustomization::updateSliceSettings);

    _sliceExplodedFactor = new QDoubleSpinBox(this);
    _sliceExplodedFactor->setSingleStep(0.01);
    connect(_sliceExplodedFactor, SIGNAL(valueChanged(double)),
            this, SLOT(updateSliceSettings()));

    _pen = new QPushButton(this);
    _penTool = new PenTool("Slice pen", this);
    connect(_pen, &QPushButton::clicked,
            _penTool, &PenTool::show);
    connect(_penTool, &PenTool::changed,
            this, &PieChartCustomization::updateSliceSettings);

    _brush = new QPushButton(this);
    _brushTool = new BrushTool("Slice brush", this);
    connect(_brush, &QPushButton::clicked,
            _brushTool, &BrushTool::show);
    connect(_brushTool, &BrushTool::changed,
            this, &PieChartCustomization::updateSliceSettings);

    _font = new QPushButton(this);
    connect(_font, &QPushButton::clicked,
            this, &PieChartCustomization::showFontDialog);

    _labelBrush = new QPushButton(this);
    _labelBrushTool = new BrushTool("Label brush", this);
    connect(_labelBrush, &QPushButton::clicked,
            _labelBrushTool, &BrushTool::show);
    connect(_labelBrushTool, &BrushTool::changed,
            this, &PieChartCustomization::updateSliceSettings);

    _labelPosition = new QComboBox(this);
    _labelPosition->addItem("Outside", QPieSlice::LabelOutside);
    _labelPosition->addItem("Inside horizontal", QPieSlice::LabelInsideHorizontal);
    _labelPosition->addItem("Inside tangential", QPieSlice::LabelInsideTangential);
    _labelPosition->addItem("Inside normal", QPieSlice::LabelInsideNormal);
    connect(_labelPosition, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateSliceSettings()));

    QFormLayout *sliceSettingsLayout = new QFormLayout;
    sliceSettingsLayout->addRow("Label", _sliceName);
    sliceSettingsLayout->addRow("Value", _sliceValue);
    sliceSettingsLayout->addRow("Pen", _pen);
    sliceSettingsLayout->addRow("Brush", _brush);
    sliceSettingsLayout->addRow("Label visible", _sliceLabelVisible);
    sliceSettingsLayout->addRow("Label font", _font);
    sliceSettingsLayout->addRow("Label brush", _labelBrush);
    sliceSettingsLayout->addRow("Label position", _labelPosition);
    sliceSettingsLayout->addRow("Label arm length", _sliceLabelArmFactor);
    sliceSettingsLayout->addRow("Exploded", _sliceExploded);
    sliceSettingsLayout->addRow("Explode distance", _sliceExplodedFactor);

    QGroupBox *sliceSettings = new QGroupBox("Selected slice",this);
    sliceSettings->setLayout(sliceSettingsLayout);

    QChart *chart = new QChart;
    chart->setTitle("Piechart customization");
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->addSeries(_series);
    connect(_series, &QPieSeries::clicked,
            this, &PieChartCustomization::handleSliceClicked);
    _chartView = new QChartView(chart);

    QVBoxLayout *settingsLayout = new QVBoxLayout();
    settingsLayout->addWidget(chartSettings);
    settingsLayout->addWidget(seriesSettings);
    settingsLayout->addWidget(sliceSettings);
    settingsLayout->addStretch();

    QGridLayout *baseLayout = new QGridLayout();
    baseLayout->addLayout(settingsLayout, 0, 0);
    baseLayout->addWidget(_chartView, 0, 1);
    setLayout(baseLayout);

    updateSerieSettings();
    updateChartSettings();
}


void PieChartCustomization::updateChartSettings()
{
    QChart *chart = 0;
    QChart::ChartTheme theme;
    int idx = _themeComboBox->currentIndex();
    theme = (QChart::ChartTheme) _themeComboBox->itemData(idx).toInt();

    chart = _chartView->chart();
    chart->setTheme(theme);
    _chartView->setRenderHint(QPainter::Antialiasing, _aaCheckBox->isChecked());

    if (_animationsCheckBox->checkState() == Qt::Checked)
        chart->setAnimationOptions(QChart::AllAnimations);
    else
        chart->setAnimationOptions(QChart::NoAnimation);

    if (_legendCheckBox->checkState() == Qt::Checked)
        chart->legend()->show();
    else
        chart->legend()->hide();
}

void PieChartCustomization::updateSerieSettings()
{
    _series->setHorizontalPosition(_hPosition->value());
    _series->setVerticalPosition(_vPosition->value());
    _series->setPieSize(_sizeFactor->value());
    _holeSize->setMaximum(_sizeFactor->value());
    _series->setPieStartAngle(_startAngle->value());
    _series->setPieEndAngle(_endAngle->value());
    _series->setHoleSize(_holeSize->value());
}

void PieChartCustomization::updateSliceSettings()
{
    if (!_slice)
        return;

    _slice->setLabel(_sliceName->text());

    _slice->setValue(_sliceValue->value());

    _slice->setPen(_penTool->pen());
    _slice->setBrush(_brushTool->brush());

    _slice->setLabelBrush(_labelBrushTool->brush());
    _slice->setLabelVisible(_sliceLabelVisible->isChecked());
    _slice->setLabelArmLengthFactor(_sliceLabelArmFactor->value());

    /** assumes that index is in sync with the enum */
    _slice->setLabelPosition((QPieSlice::LabelPosition)_labelPosition->currentIndex());
    _slice->setExploded(_sliceExploded->isChecked());
    _slice->setExplodeDistanceFactor(_sliceExplodedFactor->value());
}

void PieChartCustomization::handleSliceClicked(QPieSlice *slice)
{
    _slice = static_cast<CustomSlice *>(slice);

    _sliceName->blockSignals(true);
    _sliceName->setText(slice->label());
    _sliceName->blockSignals(false);

    _sliceValue->blockSignals(true);
    _sliceValue->setValue(slice->value());
    _sliceValue->blockSignals(false);

    _pen->setText(PenTool::name(_slice->pen()));
    _penTool->setPen(_slice->pen());

    _brush->setText(_slice->originalBrush().color().name());
    _brushTool->setBrush(_slice->originalBrush());

    _labelBrush->setText(BrushTool::name(_slice->labelBrush()));
    _labelBrushTool->setBrush(_slice->labelBrush());

    _font->setText(slice->labelFont().toString());

    _sliceLabelVisible->blockSignals(true);
    _sliceLabelVisible->setChecked(slice->isLabelVisible());
    _sliceLabelVisible->blockSignals(false);

    _sliceLabelArmFactor->blockSignals(true);
    _sliceLabelArmFactor->setValue(slice->labelArmLengthFactor());
    _sliceLabelArmFactor->blockSignals(false);

    _labelPosition->blockSignals(true);
    _labelPosition->setCurrentIndex(slice->labelPosition()); // assumes that index is in sync with the enum
    _labelPosition->blockSignals(false);

    _sliceExploded->blockSignals(true);
    _sliceExploded->setChecked(slice->isExploded());
    _sliceExploded->blockSignals(false);

    _sliceExplodedFactor->blockSignals(true);
    _sliceExplodedFactor->setValue(slice->explodeDistanceFactor());
    _sliceExplodedFactor->blockSignals(false);
}

void PieChartCustomization::showFontDialog()
{
    if (!_slice)
        return;

    QFontDialog dialog(_slice->labelFont());
    dialog.exec();

    _slice->setLabelFont(dialog.currentFont());
    _font->setText(dialog.currentFont().toString());
}

void PieChartCustomization::appendSlice()
{
    *_series << new CustomSlice("Slice " + QString::number(_series->count() + 1), 10.0);
}

void PieChartCustomization::insertSlice()
{
    if (!_slice)
        return;

    int i = _series->slices().indexOf(_slice);

    _series->insert(i, new CustomSlice("Slice " + QString::number(_series->count() + 1), 10.0));
}

void PieChartCustomization::removeSlice()
{
    if (!_slice)
        return;

    _sliceName->setText("<click a slice>");

    _series->remove(_slice);
    _slice = 0;
}
