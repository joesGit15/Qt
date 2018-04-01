#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QTabWidget;
class CustomTabStyle;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void StTabShapeChanged(int index);
    void StTabPositionChanged(int index);

private:
    QTabWidget* _tab = 0;
    CustomTabStyle* _style = 0;
};

#endif // WIDGET_H
