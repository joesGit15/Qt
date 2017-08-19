#include "colorlisteditor.h"
#include <QtGui/QColor>

ColorListEditor::ColorListEditor(QWidget *parent)
    :QComboBox(parent)
{
    populateList();
}

QColor ColorListEditor::color() const
{
    return qvariant_cast<QColor>(itemData(currentIndex(),Qt::DecorationRole));
}

void ColorListEditor::setColor(QColor col)
{
    setCurrentIndex(findData(col,int(Qt::DecorationRole)));
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
