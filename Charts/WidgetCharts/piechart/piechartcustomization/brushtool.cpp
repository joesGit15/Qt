#include "brushtool.h"

#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qcolordialog.h>

BrushTool::BrushTool(QString title, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(title);
    setWindowFlags(Qt::Tool);

    _colorButton = new QPushButton(this);
    connect(_colorButton, &QPushButton::clicked,
            this, &BrushTool::showColorDialog);

    _styleCombo = new QComboBox(this);
    _styleCombo->addItem("Nobrush", (int) Qt::NoBrush);
    _styleCombo->addItem("Solidpattern", (int) Qt::SolidPattern);
    _styleCombo->addItem("Dense1pattern", (int) Qt::Dense1Pattern);
    _styleCombo->addItem("Dense2attern", (int) Qt::Dense2Pattern);
    _styleCombo->addItem("Dense3Pattern", (int) Qt::Dense3Pattern);
    _styleCombo->addItem("Dense4Pattern", (int) Qt::Dense4Pattern);
    _styleCombo->addItem("Dense5Pattern", (int) Qt::Dense5Pattern);
    _styleCombo->addItem("Dense6Pattern", (int) Qt::Dense6Pattern);
    _styleCombo->addItem("Dense7Pattern", (int) Qt::Dense7Pattern);
    _styleCombo->addItem("HorPattern", (int) Qt::HorPattern);
    _styleCombo->addItem("VerPattern", (int) Qt::VerPattern);
    _styleCombo->addItem("CrossPattern", (int) Qt::CrossPattern);
    _styleCombo->addItem("BDiagPattern", (int) Qt::BDiagPattern);
    _styleCombo->addItem("FDiagPattern", (int) Qt::FDiagPattern);
    _styleCombo->addItem("DiagCrossPattern", (int) Qt::DiagCrossPattern);
    connect(_styleCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateStyle()));

    QFormLayout *layout = new QFormLayout();
    layout->addRow("Color", _colorButton);
    layout->addRow("Style", _styleCombo);
    setLayout(layout);
}

void BrushTool::setBrush(QBrush brush)
{
    _brush = brush;
    _colorButton->setText(_brush.color().name());
    _styleCombo->setCurrentIndex(_brush.style());
}

QBrush BrushTool::brush() const
{
    return _brush;
}

QString BrushTool::name()
{
    return name(_brush);
}

QString BrushTool::name(const QBrush &brush)
{
    return brush.color().name();
}

void BrushTool::showColorDialog()
{
    QColorDialog dialog(_brush.color());
    dialog.exec();

    _brush.setColor(dialog.selectedColor());
    _colorButton->setText(_brush.color().name());
    emit changed();
}

void BrushTool::updateStyle()
{
    Qt::BrushStyle style;
    int idx = _styleCombo->currentIndex();
    style = (Qt::BrushStyle) _styleCombo->itemData(idx).toInt();
    if (_brush.style() != style) {
        _brush.setStyle(style);
        emit changed();
    }
}
