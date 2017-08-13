#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QListView;
class ListModel;
class QTabWidget;
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void showEvent(QShowEvent *) override;

private slots:
    void StAddOneRandomItem();
    void StDelOneItem();

private:
    QListView*        _ltView = 0;
    ListModel*        _model = 0;
    QTabWidget*       _tabWidget = 0;
};

#endif // WIDGET_H
