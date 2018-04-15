#include "colorlisteditor.h"
#include <QtGui/QColor>

ColorListEditor::ColorListEditor(QWidget *parent)
    :QComboBox(parent)
{
    populateList();
}

QColor ColorListEditor::color() const
{
    QVariant var = itemData(currentIndex(),Qt::DecorationRole);
    QColor clo = var.value<QColor>();
    return clo;
}

void ColorListEditor::setColor(QColor col)
{
    int idx = findData(col,Qt::DecorationRole);
    setCurrentIndex(idx);
}

void ColorListEditor::populateList()
{
    QStringList colorNames = QColor::colorNames();
    for(int i=0; i < colorNames.size(); i++){
        QColor clo(colorNames[i]);
        insertItem(i,colorNames[i]);
        setItemData(i,clo,Qt::DecorationRole);
    }
}
