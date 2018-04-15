#include "checkboxheaderview.h"

#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>

CheckBoxHeaderView::CheckBoxHeaderView(int checkedColumn,
                                       Qt::Orientation orientation,
                                       QWidget *parent)
    :QHeaderView(orientation,parent)
{
    _checkedColumn = checkedColumn;
}

void CheckBoxHeaderView::paintSection(QPainter *painter,
                                      const QRect &rect,
                                      int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter,rect,logicalIndex);
    painter->restore();

    if(logicalIndex == _checkedColumn){
        QStyleOptionButton option;
        int x,y,len,i;
        x = 5, y = 0, len = 24;
        for(i=0; i < logicalIndex; i++){
            x += sectionSize(i);
        }
        option.rect = QRect(x,y,len,len);
        if(_isChecked){
            option.state = QStyle::State_On;
        }else{
            option.state = QStyle::State_Off;
        }
        style()->drawControl(QStyle::CE_CheckBox,&option,painter);
    }
}

void CheckBoxHeaderView::mousePressEvent(QMouseEvent *e)
{
    bool &isChecked = _isChecked;
    int &checkedColumn = _checkedColumn;

    /** if perfect, you can judge checkbox rect */
    if(visualIndexAt(e->pos().x()) == checkedColumn){
        isChecked = !isChecked;

        updateSection(checkedColumn);
        emit SigCheckStatusChanged(isChecked);
    }

    QHeaderView::mousePressEvent(e);
}
