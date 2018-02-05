#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include <QtWidgets/qwidget.h>
#include <QtGui/qbrush.h>

class QPushButton;
class QComboBox;

class BrushTool : public QWidget
{
    Q_OBJECT

public:
    explicit BrushTool(QString title, QWidget *parent = 0);

    QBrush brush() const;
    void setBrush(QBrush brush);

    QString name();
    static QString name(const QBrush &brush);

signals:
    void changed();

public slots:
    void showColorDialog();
    void updateStyle();

private:
    QBrush _brush;

    QComboBox   *_styleCombo = 0;
    QPushButton *_colorButton= 0;
};

#endif // BRUSHTOOL_H
