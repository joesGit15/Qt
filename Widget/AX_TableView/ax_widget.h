#ifndef AX_WIDGET_H
#define AX_WIDGET_H

#include <QWidget>

class  QTableView;

/** AX_ means An Xin */
class AX_Widget : public QWidget
{
    Q_OBJECT

public:
    AX_Widget(QWidget *parent = 0);
    ~AX_Widget();

private slots:
    void addRow();

private:
    QTableView* _view = 0;
};

#endif // AX_WIDGET_H
