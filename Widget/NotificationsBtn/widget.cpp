#include "widget.h"
#include "notificationbtn.h"

#include <QtWidgets/qboxlayout.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    NotificationBtn* btn;

    QVBoxLayout* vlyt = new QVBoxLayout;
    vlyt->addStretch(1);

    btn = new NotificationBtn(this);
    btn->setText(tr("Notifications"));
    vlyt->addWidget(btn,0,Qt::AlignCenter);

    btn = new NotificationBtn(this);
    btn->setText(tr("Notifications"));
    vlyt->addWidget(btn,0,Qt::AlignCenter);

    vlyt->addStretch(1);
    setLayout(vlyt);

    QPalette palet = palette();
    palet.setColor(QPalette::Background,QColor("#2a3137"));
    setPalette(palet);
}

Widget::~Widget()
{

}
