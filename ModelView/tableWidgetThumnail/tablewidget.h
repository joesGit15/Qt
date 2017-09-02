#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QtWidgets/QTableWidget>

class TableWidget : public QTableWidget
{
    Q_OBJECT

    enum TableWidgetColumns{
        Thumnail = 0,
        Text,
        Checked
    };

public:
    TableWidget(QWidget *parent = 0);

    void AddRow(const QString& path);
};

#endif // TABLEWIDGET_H
