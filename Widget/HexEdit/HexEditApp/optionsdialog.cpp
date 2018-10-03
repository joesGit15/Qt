
#include <QColorDialog>
#include <QFontDialog>

#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    readSettings();
    writeSettings();
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::show()
{
    readSettings();
    QWidget::show();
}

void OptionsDialog::accept()
{
    writeSettings();
    emit accepted();
    QDialog::hide();
}

void OptionsDialog::readSettings()
{
    bool bVal;
    QSettings settings;

    bVal = settings.value("AddressArea", true).toBool();
    ui->cbAddressArea->setChecked(bVal);

    bVal = settings.value("AsciiArea", true).toBool();
    ui->cbAsciiArea->setChecked(bVal);

    bVal = settings.value("Highlighting", true).toBool();
    ui->cbHighlighting->setChecked(bVal);

    bVal = settings.value("OverwriteMode", true).toBool();
    ui->cbOverwriteMode->setChecked(bVal);

    bVal = settings.value("ReadOnly").toBool();
    ui->cbReadOnly->setChecked(bVal);

    QColor color;

    color = QColor(0xff, 0xff, 0x99, 0xff);
    color = settings.value("HighlightingColor", color).value<QColor>();
    setColor(ui->lbHighlightingColor, color);

    color = this->palette().alternateBase().color();
    color = settings.value("AddressAreaColor", color).value<QColor>();
    setColor(ui->lbAddressAreaColor, color);

    color = this->palette().highlight().color();
    color = settings.value("SelectionColor", color).value<QColor>();
    setColor(ui->lbSelectionColor, color);

    QFont ft;

#ifdef Q_OS_WIN32
    ft = QFont("Courier", 10);
    ft = settings.value("WidgetFont", ft).value<QFont>();
    ui->leWidgetFont->setFont(ft);
#else
    ft = QFont("Monospace", 10);
    ft = settings.value("WidgetFont", ft).value<QFont>();
    ui->leWidgetFont->setFont(ft);
#endif

    int nVal;

    nVal = settings.value("AddressAreaWidth", 4).toInt();
    ui->sbAddressAreaWidth->setValue(nVal);

    nVal = settings.value("BytesPerLine", 16).toInt();
    ui->sbBytesPerLine->setValue(nVal);
}

void OptionsDialog::writeSettings()
{
    bool bVal;
    QSettings settings;

    bVal = ui->cbAddressArea->isChecked();
    settings.setValue("AddressArea", bVal);

    bVal = ui->cbAsciiArea->isChecked();
    settings.setValue("AsciiArea", bVal);

    bVal = ui->cbHighlighting->isChecked();
    settings.setValue("Highlighting", bVal);

    bVal = ui->cbOverwriteMode->isChecked();
    settings.setValue("OverwriteMode", bVal);

    bVal = ui->cbReadOnly->isChecked();
    settings.setValue("ReadOnly", bVal);

    QColor color;

    color = ui->lbHighlightingColor->palette().color(QPalette::Background);
    settings.setValue("HighlightingColor", color);

    color = ui->lbAddressAreaColor->palette().color(QPalette::Background);
    settings.setValue("AddressAreaColor", color);

    color =  ui->lbSelectionColor->palette().color(QPalette::Background);
    settings.setValue("SelectionColor", color);

    settings.setValue("WidgetFont",ui->leWidgetFont->font());

    settings.setValue("AddressAreaWidth", ui->sbAddressAreaWidth->value());

    settings.setValue("BytesPerLine", ui->sbBytesPerLine->value());
}

void OptionsDialog::setColor(QWidget *widget, QColor color)
{
    QPalette palette = widget->palette();
    palette.setColor(QPalette::Background, color);
    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
}

void OptionsDialog::on_pbHighlightingColor_clicked()
{
    QColor color;

    color = ui->lbHighlightingColor->palette().color(QPalette::Background);
    color = QColorDialog::getColor(color, this);
    if (color.isValid()) {
        setColor(ui->lbHighlightingColor, color);
    }
}

void OptionsDialog::on_pbAddressAreaColor_clicked()
{
    QColor color;
    color = ui->lbAddressAreaColor->palette().color(QPalette::Background);
    color = QColorDialog::getColor(color, this);
    if (color.isValid()) {
        setColor(ui->lbAddressAreaColor, color);
    }
}

void OptionsDialog::on_pbSelectionColor_clicked()
{
    QColor color;
    color = ui->lbSelectionColor->palette().color(QPalette::Background);
    color = QColorDialog::getColor(color, this);
    if (color.isValid()) {
        setColor(ui->lbSelectionColor, color);
    }
}

void OptionsDialog::on_pbWidgetFont_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->leWidgetFont->font(), this);
    if (ok) {
        ui->leWidgetFont->setFont(font);
    }
}
