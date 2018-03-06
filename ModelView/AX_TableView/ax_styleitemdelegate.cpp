#include "ax_styleitemdelegate.h"

#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>

#define BTN_CHECKBOX 0
#define BTN_RADIO_1  1
#define BTN_RADIO_2  2

enum AX_BtnType{
    Btn_CheckBox = 0,
    Btn_Radio_0,
    Btn_Radio_1
};

static QRect getItemBtnRect(const QRect &optionRect,AX_BtnType type = Btn_CheckBox)
{
    QRect rect = optionRect;
    rect.adjust(0,0,0,-rect.height()/2);
    rect.adjust(10,5,-10,-5);

    int dtX = int(rect.width()/3+0.5);
    if(Btn_CheckBox == type){
        rect.adjust(0,0,-2*dtX,0);
    }else if(Btn_Radio_0 == type){
        rect.adjust(dtX,0,-dtX,0);
    }else if(Btn_Radio_1 == type){
        rect.adjust(2*dtX,0,0,0);
    }else{
        rect.adjust(0,0,-2*dtX,0);
    }

    return rect;
}

enum AX_BtnItemType{
    Btn_Icon = 0,
    Btn_Text
};

static QRect getBtnItemRect(const QRect &btnRect,AX_BtnItemType type = Btn_Icon)
{
    QRect rect = btnRect;

    int dtX = int(rect.width()/3+0.5);
    if(Btn_Icon == type){
        rect.adjust(0,0,-2*dtX,0);
    }else if(Btn_Text == type){
        rect.adjust(dtX,0,0,0);
    }else{
        rect.adjust(0,0,-2*dtX,0);
    }

    return rect;
}

static QRect getItemBarRect(const QRect &optionRect)
{
    QRect rect = optionRect;
    rect.adjust(0,rect.height()/2,0,0);
    rect.adjust(10,5,-10,-5);
    return rect;
}

static void updateBtnValue(const QPoint &pos,const QRect &optionRect,
                           const QModelIndex &index,QAbstractItemModel *model)
{
    QRect rect,btnRect;
    btnRect = getItemBtnRect(optionRect,Btn_CheckBox);
    rect = getBtnItemRect(btnRect,Btn_Icon);
    if(rect.contains(pos)){
        QVariant var = index.data(Qt::UserRole);
        CellDt dt = var.value<CellDt>();
        dt.checked = !dt.checked;
        var.setValue(dt);
        model->setData(index,var,Qt::UserRole);
        return;
    }

    btnRect = getItemBtnRect(optionRect,Btn_Radio_0);
    rect = getBtnItemRect(btnRect,Btn_Icon);
    if(rect.contains(pos)){
        QVariant var = index.data(Qt::UserRole);
        CellDt dt = var.value<CellDt>();
        if(dt.radio){
            dt.radio = false;
        }
        var.setValue(dt);
        model->setData(index,var,Qt::UserRole);
        return;
    }

    btnRect = getItemBtnRect(optionRect,Btn_Radio_1);
    rect = getBtnItemRect(btnRect,Btn_Icon);
    if(rect.contains(pos)){
        QVariant var = index.data(Qt::UserRole);
        CellDt dt = var.value<CellDt>();
        if(!dt.radio){
            dt.radio = true;
        }
        var.setValue(dt);
        model->setData(index,var,Qt::UserRole);
        return;
    }
}

static void updateBarValue(const QPoint &pos,const QRect &optionRect,
                           const QModelIndex &index,QAbstractItemModel *model)
{
    QRect rect = getItemBarRect(optionRect);
    if(rect.contains(pos)){
        QVariant var = index.data(Qt::UserRole);
        int viewVal = pos.x() - rect.x();
        if(viewVal > rect.width()){
            viewVal = rect.width();
        }

        int val = int(viewVal/(float)rect.width() * 100 + 0.5);
        if(val > 100){
            val = 100;
        }

        CellDt dt = var.value<CellDt>();
        dt.val = val;
        var.setValue(dt);
        model->setData(index,var,Qt::UserRole);
    }
}


AX_StyleitemDelegate::AX_StyleitemDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

void AX_StyleitemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant var = index.data(Qt::UserRole);
    CellDt dt = var.value<CellDt>();
    int val = dt.val;

    painter->save();

    QTextOption textOpt;
    painter->setPen(Qt::black);
    textOpt.setAlignment(Qt::AlignCenter);

    QPixmap pix;
    QRect rect,btnRect;
    btnRect = getItemBtnRect(option.rect,Btn_CheckBox);
    rect = getBtnItemRect(btnRect,Btn_Icon);
    if(dt.checked){
        pix.load(":/img/checkbox_uncheck.png");
    }else{
        pix.load(":/img/checkbox_check.png");
    }
    painter->drawPixmap(rect,pix);
    rect = getBtnItemRect(btnRect,Btn_Text);
    painter->drawText(rect,tr("label"),textOpt);

    btnRect = getItemBtnRect(option.rect,Btn_Radio_0);
    rect = getBtnItemRect(btnRect,Btn_Icon);
    if(dt.radio){
        pix.load(":/img/radio_uncheck.png");
    }else{
        pix.load(":/img/radio_check.png");
    }
    painter->drawPixmap(rect,pix);
    rect = getBtnItemRect(btnRect,Btn_Text);
    painter->drawText(rect,tr("label"),textOpt);

    btnRect = getItemBtnRect(option.rect,Btn_Radio_1);
    rect = getBtnItemRect(btnRect,Btn_Icon);
    if(!dt.radio){
        pix.load(":/img/radio_uncheck.png");
    }else{
        pix.load(":/img/radio_check.png");
    }
    painter->drawPixmap(rect,pix);
    rect = getBtnItemRect(btnRect,Btn_Text);
    painter->drawText(rect,tr("label"),textOpt);

    /**  */
    rect = getItemBarRect(option.rect);
    painter->setPen(Qt::blue);
    painter->drawRect(rect);

    int process = int(rect.width() * val/100.0 + 0.5);
    rect.adjust(0,0,-(rect.width() - process),0);
    painter->fillRect(rect,Qt::blue);

    painter->restore();
}

bool AX_StyleitemDelegate::editorEvent(QEvent *event,
                                       QAbstractItemModel *model,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index)
{
    QMouseEvent* mouseEvent = 0;

    if(QEvent::MouseButtonPress == event->type()){
        mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint pos = mouseEvent->pos();
        updateBtnValue(pos,option.rect,index,model);
    }

    if(QEvent::MouseButtonRelease == event->type()){
    }

    if(QEvent::MouseMove == event->type()){
        mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint pos = mouseEvent->pos();
        updateBarValue(pos,option.rect,index,model);
    }

    return true;
}

/**  */

AX_FirstitemDelegate::AX_FirstitemDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

static QRect getFirstColumnTextRect(const QRect &optionRect)
{
    QRect rect = optionRect;
    rect.adjust(0,0,0,-rect.height()/2);
    return rect;
}

void AX_FirstitemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    QVariant var = index.data(Qt::UserRole);
    CellDt dt = var.value<CellDt>();
    int val = dt.val;

    painter->save();

    QRect rect;
    QTextOption textOpt;
    painter->setPen(Qt::black);
    textOpt.setAlignment(Qt::AlignCenter);
    rect = getFirstColumnTextRect(option.rect);
    painter->drawText(rect,tr("label text"),textOpt);

    rect = getItemBarRect(option.rect);
    painter->setPen(Qt::green);
    painter->drawRect(rect);

    int process = int(rect.width() * val/100.0 + 0.5);
    rect.adjust(0,0,-(rect.width() - process),0);
    painter->fillRect(rect,Qt::green);

    painter->restore();
}

bool AX_FirstitemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index)
{
    QMouseEvent* mouseEvent = 0;

    if(QEvent::MouseButtonPress == event->type()){
    }

    if(QEvent::MouseButtonRelease == event->type()){
    }

    if(QEvent::MouseMove == event->type()){
        mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint pos = mouseEvent->pos();
        updateBarValue(pos,option.rect,index,model);
    }

    return true;
}
