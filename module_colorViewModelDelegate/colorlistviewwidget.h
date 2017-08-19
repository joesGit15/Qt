#ifndef COLORLISTVIEWWIDGET_H
#define COLORLISTVIEWWIDGET_H

#include <QWidget>

class ListModel;
QT_BEGIN_NAMESPACE
class QListView;
QT_END_NAMESPACE

class ColorListViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorListViewWidget(QWidget *parent = 0);

signals:

private slots:
    void StAddOneRandomItem();

private:
    QListView*        _ltView = 0;
    ListModel*        _model = 0;
};

#endif // COLORLISTVIEWWIDGET_H
