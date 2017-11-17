#ifndef CHANGECOLOR_H
#define CHANGECOLOR_H

#include <QtCore/qobject.h>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class ChangeColor : public QObject
{
    Q_OBJECT
public:
    explicit ChangeColor(QObject *target,QObject *parent = 0);

private:
    void StTimeout();

private:
    QObject*    _target = 0;
};

#endif // CHANGECOLOR_H
