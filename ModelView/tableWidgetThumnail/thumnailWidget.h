#ifndef THUMNAILWIDGET_H
#define THUMNAILWIDGET_H

#include <QWidget>

class TableWidget;
QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class ThumnailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThumnailWidget(QWidget *parent = 0);

private slots:
    void StOpenImages();

private:
    TableWidget* _tableWget = 0;
};

#endif // THUMNAILWIDGET_H
