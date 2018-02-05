#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets/QWidget>

class PenTool;
class BrushTool;
class CustomSlice;

class QLineEdit;
class QPushButton;
class QCheckBox;
class QComboBox;
class QDoubleSpinBox;

namespace QtCharts {
    class QChartView;
    class QPieSeries;
    class QPieSlice;
}
using namespace QtCharts;

class PieChartCustomization : public QWidget
{
    Q_OBJECT

public:
    explicit PieChartCustomization(QWidget *parent = 0);

public slots:
    void updateChartSettings();
    void updateSerieSettings();
    void updateSliceSettings();
    void handleSliceClicked(QPieSlice *slice);
    void showFontDialog();
    void appendSlice();
    void insertSlice();
    void removeSlice();

private:
    CustomSlice *_slice = 0;

    QComboBox *_themeComboBox;
    QCheckBox *_aaCheckBox;
    QCheckBox *_animationsCheckBox;
    QCheckBox *_legendCheckBox;

    QChartView *_chartView;
    QPieSeries *_series;

    QDoubleSpinBox *_hPosition;
    QDoubleSpinBox *_vPosition;
    QDoubleSpinBox *_sizeFactor;
    QDoubleSpinBox *_startAngle;
    QDoubleSpinBox *_endAngle;
    QDoubleSpinBox *_holeSize;

    QLineEdit *_sliceName;
    QDoubleSpinBox *_sliceValue;
    QCheckBox *_sliceLabelVisible;
    QDoubleSpinBox *_sliceLabelArmFactor;
    QCheckBox *_sliceExploded;
    QDoubleSpinBox *_sliceExplodedFactor;
    QPushButton *_brush;
    BrushTool *_brushTool;
    QPushButton *_pen;
    PenTool *_penTool;
    QPushButton *_font;
    QPushButton *_labelBrush;
    QComboBox *_labelPosition;
    BrushTool *_labelBrushTool;
};

#endif // MAINWIDGET_H
