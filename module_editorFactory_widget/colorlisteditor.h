#ifndef COLORLISTEDITOR_H
#define COLORLISTEDITOR_H
#include <QtWidgets/QComboBox>

class ColorListEditor : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor USER true)

public:
    ColorListEditor(QWidget* parent = 0);

    QColor color() const;
    void setColor(QColor col);

private:
    void populateList();
};

#endif // COLORLISTEDITOR_H
