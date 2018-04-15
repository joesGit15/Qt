#pragma once

#include <QtWidgets/qheaderview.h>

class CheckBoxHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    CheckBoxHeaderView(int checkedColumn,
                       Qt::Orientation orientation,
                       QWidget *parent = 0);

signals:
    void SigCheckStatusChanged(bool);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent *e);

private:
    /** @brief: which column is has show checkbox widget*/
    int         _checkedColumn;

    /** @brief */
    bool        _isChecked;
};
