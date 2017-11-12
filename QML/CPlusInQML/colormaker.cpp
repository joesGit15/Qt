#include "colormaker.h"

#include <QtGui/qevent.h>
#include <QtCore/qdatetime.h>

ColorMaker::ColorMaker(QObject *parent)
    : QObject(parent)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
}

void ColorMaker::setColor(const QColor &color)
{
    _color = color;
    emit colorChanged(color);
}

QColor ColorMaker::timeColor() const
{
    QTime t = QTime::currentTime();
    int r = t.hour();
    int g = t.minute()*2;
    int b = t.second()*4;
    return QColor::fromRgb(r,g,b);
}

void ColorMaker::start()
{
    if(0 == _colorTimer){
        _colorTimer = startTimer(1000);
    }
}

void ColorMaker::stop()
{
    if(0 < _colorTimer){
        killTimer(_colorTimer);
        _colorTimer = 0;
    }
}

void ColorMaker::timerEvent(QTimerEvent *event)
{
    if(_colorTimer == event->timerId()){
        switch (_algorithm) {
        case RandomRGB:
            _color.setRgb(qrand()%255,qrand()%255,qrand()%255);
            break;
        case RandomRed:
            _color.setRed(qrand()%255);
            break;
        case RandomGreen:
            _color.setGreen(qrand()%255);
            break;
        case RandomBlue:
            _color.setBlue(qrand()%255);
            break;
        case LinearIncrease: {
            int r = _color.red()   + 10;
            int g = _color.green() + 10;
            int b = _color.blue()  + 10;
            _color.setRgb(r%255,g%255,b%255);
            break;
            }
        }

        emit colorChanged(_color);
        emit currentTime(QDateTime::currentDateTime()
                         .toString("yyyy-MM-dd hh:mm:ss"));
    }else{
        QObject::timerEvent(event);
    }
}
