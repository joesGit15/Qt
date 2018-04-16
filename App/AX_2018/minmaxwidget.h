#ifndef MINMAXWIDGET_H
#define MINMAXWIDGET_H

#include <QWidget>

class MinMaxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MinMaxWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MINMAXWIDGET_H
