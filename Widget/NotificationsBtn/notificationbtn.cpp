#include "notificationbtn.h"

#include <QtGui/qpainter.h>
#include <QtGui/qbrush.h>
#include <QtGui/qpainterpath.h>
#include <QtGui/qevent.h>

NotificationBtn::NotificationBtn(QWidget *parent)
    :QAbstractButton(parent)
{
    setMinimumSize(200,60);
}

void NotificationBtn::paintEvent(QPaintEvent *e)
{
    const int PADDING = 10;

    int x,y,w,h,len;
    QPen pen;
    QFont ft;
    QBrush br;
    QPointF start,stop;
    QPainterPath path;
    QLinearGradient lineGrad;
    QRect roundRect,btnRect,textRect,bellRect;

    /** Button Background Rect */
    btnRect = this->rect();
    btnRect.adjust(0,PADDING,0,0);

    /** Button Bell Rect */
    x = PADDING;
    h = btnRect.height() - 2*PADDING;
    y = btnRect.top() + (btnRect.height() - h)/2;
    w = 30;
    bellRect = QRect(x,y,w,h);

    /** Button Round Nitification Rect */
    len = 32;
    x = this->rect().right() - PADDING - len;
    y = this->rect().top() + 5;
    w = h = len;
    roundRect = QRect(x,y,w,h);

    /** Button Text Rect */
    x = bellRect.right();
    y = btnRect.top();
    w = btnRect.width() - 2*PADDING - bellRect.width() - roundRect.width();
    h  = btnRect.height();
    textRect = QRect(x,y,w,h);

    /** Draw Button Background */
    start = btnRect.topLeft();
    start.setX(start.x() + btnRect.width()/2);
    stop  = btnRect.bottomLeft();
    stop.setX(stop.x() + btnRect.width()/2);

    lineGrad = QLinearGradient(start,stop);
    if(_hover){
        lineGrad.setColorAt(0,QColor("#5f666e"));
        lineGrad.setColorAt(0.6,QColor("#4a545d"));
    }if(isDown()){
        lineGrad.setColorAt(0,QColor("#4a545d"));
    }else{
        lineGrad.setColorAt(0,QColor("#5f666e"));
        lineGrad.setColorAt(1,QColor("#4a545d"));
    }
    br = QBrush(lineGrad);

    //btnPath.addRoundRect(btnRect,10,10);
    path.addRoundedRect(btnRect,3,3);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillPath(path,br);

    /** Draw Bell Image */
    QPixmap pix;
    if(_num > 0){
        pix.load(":/img/redbell.png");
    }else{
        pix.load(":/img/blackbell.png");
    }

    y = btnRect.top();
    y = y + (btnRect.height() - pix.height())/2;
    painter.drawPixmap(10,y,pix);

    /** Draw Button Text */
    pen.setColor(Qt::white);
    pen.setWidth(2);
    painter.save();
    painter.setPen(pen);
    ft = font();
    ft.setPixelSize(16);
    painter.setFont(ft);
    painter.drawText(textRect,Qt::AlignCenter,"Notifications");
    painter.restore();

    /** Draw Round Notification */
    if(_num > 0){
        start = roundRect.topLeft();
        start.setX(start.x() + roundRect.width()/2);
        stop  = roundRect.bottomLeft();
        stop.setX(stop.x() + roundRect.width()/2);

        lineGrad = QLinearGradient(start,stop);
        lineGrad.setColorAt(0,QColor("#ff6c86"));
        lineGrad.setColorAt(1,QColor("#d00c30"));
        br = QBrush(lineGrad);

        path = QPainterPath();
        path.addEllipse(roundRect);
        painter.fillPath(path,br);

        pen.setColor("#d00c30");
        pen.setWidth(1);
        painter.save();
        painter.setPen(pen);
        painter.drawPath(path);
        painter.restore();

        pen.setColor(Qt::white);
        pen.setWidth(1);
        painter.save();
        painter.setPen(pen);
        painter.drawText(roundRect,Qt::AlignCenter,QString::number(_num));
        painter.restore();
    }
}

void NotificationBtn::enterEvent(QEvent *event)
{
    (void)event;
    _hover = true;
}

void NotificationBtn::leaveEvent(QEvent *event)
{
    (void)event;
    _hover = false;
}

void NotificationBtn::keyPressEvent(QKeyEvent *e)
{
    int &num = _num;

    if(e->key() == Qt::Key_Plus){
        num++;
    }else if(e->key() == Qt::Key_Minus){
        num--;
        num = num < 0 ? 0 : num;
    }

    update();
}
