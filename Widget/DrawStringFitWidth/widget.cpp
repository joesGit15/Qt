#include "widget.h"

#include <QtGui/qpainter.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(100,200);

    QPalette palet = palette();
    palet.setColor(QPalette::Background,QColor("#2a3137"));
    setPalette(palet);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    int dt = rect().height()/3;
    QRect textRect;
    QString str("ABCDEFGH");
    QPainter painter(this);
    painter.setPen(Qt::blue);

    textRect = rect();
    textRect.adjust(0,0,0,-2*dt);
    painter.drawText(textRect,Qt::AlignCenter,str);

    textRect = rect();
    textRect.adjust(0,dt,0,-dt);

    QFont ft = font();
    QFontMetrics fm(ft);
    int tw = fm.width(str);
    int diff = textRect.width() - tw;
    qreal space = ft.letterSpacing();
    qreal delta = diff/(str.length() - 1);
    ft.setLetterSpacing(QFont::AbsoluteSpacing,space + delta);

    painter.save();
    painter.setFont(ft);
    painter.drawText(textRect,str);
    painter.restore();
}
