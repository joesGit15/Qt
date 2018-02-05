#include "pentool.h"

#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qcolordialog.h>

PenTool::PenTool(QString title, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(title);
    setWindowFlags(Qt::Tool);

    _colorButton = new QPushButton(this);
    connect(_colorButton, &QPushButton::clicked,
            this, &PenTool::showColorDialog);

    _widthSpinBox = new QDoubleSpinBox(this);
    connect(_widthSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(updateWidth(double)));

    _styleCombo = new QComboBox(this);
    _styleCombo->addItem("NoPen");
    _styleCombo->addItem("SolidLine");
    _styleCombo->addItem("DashLine");
    _styleCombo->addItem("DotLine");
    _styleCombo->addItem("DashDotLine");
    _styleCombo->addItem("DashDotDotLine");
    connect(_styleCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateStyle(int)));

    _capStyleCombo = new QComboBox(this);
    _capStyleCombo->addItem("FlatCap", Qt::FlatCap);
    _capStyleCombo->addItem("SquareCap", Qt::SquareCap);
    _capStyleCombo->addItem("RoundCap", Qt::RoundCap);
    connect(_capStyleCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateCapStyle(int)));

    _joinStyleCombo = new QComboBox(this);
    _joinStyleCombo->addItem("MiterJoin", Qt::MiterJoin);
    _joinStyleCombo->addItem("BevelJoin", Qt::BevelJoin);
    _joinStyleCombo->addItem("RoundJoin", Qt::RoundJoin);
    _joinStyleCombo->addItem("SvgMiterJoin", Qt::SvgMiterJoin);
    connect(_joinStyleCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateJoinStyle(int)));

    QFormLayout *layout = new QFormLayout;
    layout->addRow("Color", _colorButton);
    layout->addRow("Width", _widthSpinBox);
    layout->addRow("Style", _styleCombo);
    layout->addRow("Cap style", _capStyleCombo);
    layout->addRow("Join style", _joinStyleCombo);
    setLayout(layout);
}

void PenTool::setPen(const QPen &pen)
{
    _pen = pen;
    _colorButton->setText(_pen.color().name());
    _widthSpinBox->setValue(_pen.widthF());
    _styleCombo->setCurrentIndex(_pen.style());
    _capStyleCombo->setCurrentIndex(_capStyleCombo->findData(_pen.capStyle()));
    _joinStyleCombo->setCurrentIndex(_joinStyleCombo->findData(_pen.joinStyle()));
}

QPen PenTool::pen() const
{
    return _pen;
}

QString PenTool::name()
{
    return name(_pen);
}

QString PenTool::name(const QPen &pen)
{
    return pen.color().name() + ":" + QString::number(pen.widthF());
}

void PenTool::showColorDialog()
{
    QColorDialog dialog(_pen.color());
    dialog.exec();
    _pen.setColor(dialog.selectedColor());
    _colorButton->setText(_pen.color().name());
    emit changed();
}

void PenTool::updateWidth(double width)
{
    if (!qFuzzyCompare((qreal) width, _pen.widthF())) {
        _pen.setWidthF(width);
        emit changed();
    }
}

void PenTool::updateStyle(int style)
{
    if (_pen.style() != style) {
        _pen.setStyle((Qt::PenStyle) style);
        emit changed();
    }
}

void PenTool::updateCapStyle(int index)
{
    Qt::PenCapStyle capStyle;
    capStyle = (Qt::PenCapStyle) _capStyleCombo->itemData(index).toInt();
    if (_pen.capStyle() != capStyle) {
        _pen.setCapStyle(capStyle);
        emit changed();
    }
}

void PenTool::updateJoinStyle(int index)
{
    Qt::PenJoinStyle joinStyle;
    joinStyle = (Qt::PenJoinStyle) _joinStyleCombo->itemData(index).toInt();
    if (_pen.joinStyle() != joinStyle) {
        _pen.setJoinStyle(joinStyle);
        emit changed();
    }
}
