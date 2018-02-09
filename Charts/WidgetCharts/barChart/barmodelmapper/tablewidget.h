#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QtWidgets/QWidget>

#include "customtablemodel.h"

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = 0);

private:
    CustomTableModel *_model;
};

#endif // TABLEWIDGET_H
