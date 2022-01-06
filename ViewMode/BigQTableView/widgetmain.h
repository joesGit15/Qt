#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>

class WidgetMain : public QWidget
{
    Q_OBJECT

public:
    WidgetMain(QWidget *parent = 0);
    ~WidgetMain();

private slots:
    void stAddBtnClicked();
};

#endif // WIDGETMAIN_H
