#ifndef PENTOOL_H
#define PENTOOL_H

#include <QtGui/qpen.h>
#include <QtWidgets/qwidget.h>

class QPushButton;
class QComboBox;
class QDoubleSpinBox;

class PenTool : public QWidget
{
    Q_OBJECT

public:
    explicit PenTool(QString title, QWidget *parent = 0);

    QPen pen() const;
    void setPen(const QPen &pen);

    QString name();
    static QString name(const QPen &pen);

signals:
    void changed();

public slots:
    void showColorDialog();
    void updateWidth(double width);
    void updateStyle(int style);
    void updateCapStyle(int index);
    void updateJoinStyle(int index);

private:
    QPen _pen;

    QPushButton     *_colorButton = 0;
    QDoubleSpinBox *_widthSpinBox = 0;

    QComboBox *_styleCombo     = 0;
    QComboBox *_capStyleCombo  = 0;
    QComboBox *_joinStyleCombo = 0;
};

#endif // PENTOOL_H
