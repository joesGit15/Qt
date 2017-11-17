#include "changecolor.h"

#include <QtCore/qtimer.h>
#include <QtCore/qvariant.h>
#include <QtCore/qdatetime.h>

#include <QtGui/qcolor.h>

ChangeColor::ChangeColor(QObject *target, QObject *parent)
    : QObject(parent)
{
    Q_ASSERT(0 != target);
    _target = target;

    srand(QDateTime::currentDateTime().toTime_t());

    QTimer * t = new QTimer(this);
    connect(t,&QTimer::timeout,this,&ChangeColor::StTimeout);
    t->start(1000);
}

void ChangeColor::StTimeout()
{
    QColor col = QColor::fromRgb(rand()%256,rand()%256,rand()%256);
    QVariant val;
    val.setValue(col);
    _target->setProperty("color",val);
}
